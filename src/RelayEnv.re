let isSsr: bool = [%bs.raw {|typeof window === "undefined"|}];

let appId = "f1b8d65a-c97c-43c3-ac72-9a289de3c257";

let oneGraphUrl = {j|https://serve.onegraph.com/graphql?app_id=$appId|j};

/* Determine if we're rendering in a non-browser environment (e.g. node) */
let isSsr: bool = [%bs.raw {|typeof window === "undefined"|}];

let oneGraphUrl = {j|https://serve.onegraph.com/graphql?app_id=$appId|j};

let authConfig = OneGraphAuth.createOptions(~appId, ());

let auth = isSsr ? None : Some(OneGraphAuth.create(authConfig));

/* This is just a custom exception to indicate that something went wrong. */
exception Graphql_error(string);

/**
   * A standard fetch that sends our operation and variables to the
   * GraphQL server, and then decodes and returns the response.
   */
let fetchQuery: ReasonRelay.Network.fetchFunctionPromise =
  (operation, variables, _cacheConfig) => {
    let authHeader =
      auth->Belt.Option.flatMap(auth => OneGraphAuth.authHeaders(auth));

    Fetch.(
      fetchWithInit(
        oneGraphUrl,
        RequestInit.make(
          ~method_=Post,
          ~body=
            Js.Dict.fromList([
              ("query", Js.Json.string(operation.text)),
              ("variables", variables),
            ])
            |> Js.Json.object_
            |> Js.Json.stringify
            |> BodyInit.make,
          ~headers=
            HeadersInit.make({
              "content-type": "application/json",
              "accept": "application/json",
              "Authorization": authHeader->Belt.Option.getWithDefault(""),
            }),
          (),
        ),
      )
      |> Js.Promise.then_(resp =>
           if (Response.ok(resp)) {
             Response.json(resp);
           } else {
             Js.Promise.reject(
               Graphql_error(
                 "Request failed: " ++ Response.statusText(resp),
               ),
             );
           }
         )
    );
  };

module OneGraphSubscriptionClient = {
  type t;

  type subscriptionClientOptions = {oneGraphAuth: OneGraphAuth.t};

  [@bs.module "onegraph-subscription-client"] [@bs.new "SubscriptionClient"]
  external make: (string, subscriptionClientOptions) => t =
    "SubscriptionClient";

  type observable;
  [@bs.send] external request: (t, Js.t('a)) => observable = "request";
  [@bs.send] external subscribe: (observable, Js.t('a)) => unit = "subscribe";
};

let oneGraphSubscriptionClient =
  auth->Belt.Option.map(oneGraphAuth =>
    OneGraphSubscriptionClient.make(appId, {oneGraphAuth: oneGraphAuth})
  );

/* Subscriptions to OneGraph can also work server-side with some addition packages, but we just disable them in SSR for now. */
let subscriptionFunction: option(ReasonRelay.Network.subscribeFn) =
  oneGraphSubscriptionClient->Belt.Option.map(
    (
      oneGraphSubscriptionClient,
      operation: ReasonRelay.Network.operation,
      variables: Js.Json.t,
      _cacheConfig: ReasonRelay.cacheConfig,
    ) => {
    let subscribeObservable =
      oneGraphSubscriptionClient->OneGraphSubscriptionClient.request({
        "query": operation.text,
        "variables": variables,
        "operationName": operation.name,
      });

    let observable =
      ReasonRelay.Observable.make(sink => {
        subscribeObservable
        ->OneGraphSubscriptionClient.subscribe({
            "next": data => {
              sink.next(data);
            },
            "error": sink.error,
            "complete": sink.completed,
          })
        ->ignore
      });

    observable;
  });

let network =
  ReasonRelay.Network.makePromiseBased(
    ~fetchFunction=fetchQuery,
    ~subscriptionFunction?,
    (),
  );

let environment =
  ReasonRelay.Environment.make(
    ~network,
    ~store=
      ReasonRelay.Store.make(
        ~source=ReasonRelay.RecordSource.make(),
        ~gcReleaseBufferSize=100,
        (),
      ),
    (),
  );
