let isSsr: bool = [%bs.raw {|typeof window === "undefined"|}];

let appId = "f1b8d65a-c97c-43c3-ac72-9a289de3c257";

let oneGraphUrl = {j|https://serve.onegraph.com/graphql?app_id=$appId|j};

let authConfig =
  OneGraphAuth.createOptions(
    ~appId,
    ~oneGraphOrigin="https://serve.onegraph.com",
    (),
  );

let auth = isSsr ? None : Some(OneGraphAuth.create(authConfig));

/* RelayEnv.re */
/* This is just a custom exception to indicate that something went wrong. */
exception GraphqlError(string);

/**
 * A standard fetch that sends our operation and variables to the
 * GraphQL server, and then decodes and returns the response.
 */
let fetchQuery: ReasonRelay.Network.fetchFunctionPromise =
  (operation, variables, _cacheConfig) => {
    let authHeader =
      Config.auth->Belt.Option.flatMap(auth =>
        OneGraphAuth.authHeaders(auth)
      );

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
               GraphqlError("Request failed: " ++ Response.statusText(resp)),
             );
           }
         )
    );
  };

let network =
  ReasonRelay.Network.makePromiseBased(~fetchFunction=fetchQuery, ());

let environment =
  ReasonRelay.Environment.make(
    ~network,
    ~store=
      ReasonRelay.Store.make(~source=ReasonRelay.RecordSource.make(), ()),
    (),
  );
