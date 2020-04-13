/* @generated */

type enum_GitHubPullRequestState = [
  | `CLOSED
  | `MERGED
  | `OPEN
  | `FutureAddedValue(string)
];

let unwrap_enum_GitHubPullRequestState: string => enum_GitHubPullRequestState =
  fun
  | "CLOSED" => `CLOSED
  | "MERGED" => `MERGED
  | "OPEN" => `OPEN
  | v => `FutureAddedValue(v);

let wrap_enum_GitHubPullRequestState: enum_GitHubPullRequestState => string =
  fun
  | `CLOSED => "CLOSED"
  | `MERGED => "MERGED"
  | `OPEN => "OPEN"
  | `FutureAddedValue(v) => v;

module Types = {
  type response_gitHub_createPullRequest_pullRequest = {
    body: string,
    id: string,
    number: int,
    permalink: string,
    state: [ | `CLOSED | `MERGED | `OPEN | `FutureAddedValue(string)],
    title: string,
    url: string,
  };
  type response_gitHub_createPullRequest = {
    pullRequest: option(response_gitHub_createPullRequest_pullRequest),
  };
  type response_gitHub = {
    createPullRequest: option(response_gitHub_createPullRequest),
  };

  type response = {gitHub: option(response_gitHub)};
  type variables = {
    repoId: string,
    title: string,
    headRefName: string,
    baseRefName: string,
    body: string,
  };
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"gitHub":{"n":""},"gitHub_createPullRequest":{"n":""},"gitHub_createPullRequest_pullRequest":{"n":""},"gitHub_createPullRequest_pullRequest_state":{"e":"enum_GitHubPullRequestState"}}} |json}
  ];
  let wrapResponseConverterMap = {
    "enum_GitHubPullRequestState": wrap_enum_GitHubPullRequestState,
  };
  let convertWrapResponse = v =>
    v
    ->ReasonRelay._convertObj(
        wrapResponseConverter,
        wrapResponseConverterMap,
        Js.null,
      );

  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"gitHub":{"n":""},"gitHub_createPullRequest":{"n":""},"gitHub_createPullRequest_pullRequest":{"n":""},"gitHub_createPullRequest_pullRequest_state":{"e":"enum_GitHubPullRequestState"}}} |json}
  ];
  let responseConverterMap = {
    "enum_GitHubPullRequestState": unwrap_enum_GitHubPullRequestState,
  };
  let convertResponse = v =>
    v
    ->ReasonRelay._convertObj(
        responseConverter,
        responseConverterMap,
        Js.undefined,
      );

  let variablesConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {} |json}
  ];
  let variablesConverterMap = ();
  let convertVariables = v =>
    v
    ->ReasonRelay._convertObj(
        variablesConverter,
        variablesConverterMap,
        Js.undefined,
      );
};

module Utils = {
  open Types;
  let makeVariables =
      (~repoId, ~title, ~headRefName, ~baseRefName, ~body): variables => {
    repoId,
    title,
    headRefName,
    baseRefName,
    body,
  };

  let make_response_gitHub_createPullRequest_pullRequest =
      (~body, ~id, ~number, ~permalink, ~state, ~title, ~url)
      : response_gitHub_createPullRequest_pullRequest => {
    body,
    id,
    number,
    permalink,
    state,
    title,
    url,
  };

  let make_response_gitHub_createPullRequest =
      (~pullRequest=?, ()): response_gitHub_createPullRequest => {
    pullRequest: pullRequest,
  };

  let make_response_gitHub = (~createPullRequest=?, ()): response_gitHub => {
    createPullRequest: createPullRequest,
  };

  let makeOptimisticResponse = (~gitHub=?, ()): response => {gitHub: gitHub};
};

type operationType = ReasonRelay.mutationNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "repoId",
    "type": "ID!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "title",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "headRefName",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "baseRefName",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "body",
    "type": "String!",
    "defaultValue": null
  }
],
v1 = [
  {
    "kind": "LinkedField",
    "alias": null,
    "name": "gitHub",
    "storageKey": null,
    "args": null,
    "concreteType": "GitHubMutation",
    "plural": false,
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "createPullRequest",
        "storageKey": null,
        "args": [
          {
            "kind": "ObjectValue",
            "name": "input",
            "fields": [
              {
                "kind": "Variable",
                "name": "baseRefName",
                "variableName": "baseRefName"
              },
              {
                "kind": "Variable",
                "name": "body",
                "variableName": "body"
              },
              {
                "kind": "Variable",
                "name": "headRefName",
                "variableName": "headRefName"
              },
              {
                "kind": "Literal",
                "name": "maintainerCanModify",
                "value": true
              },
              {
                "kind": "Variable",
                "name": "repositoryId",
                "variableName": "repoId"
              },
              {
                "kind": "Variable",
                "name": "title",
                "variableName": "title"
              }
            ]
          }
        ],
        "concreteType": "GitHubCreatePullRequestPayload",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "pullRequest",
            "storageKey": null,
            "args": null,
            "concreteType": "GitHubPullRequest",
            "plural": false,
            "selections": [
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "body",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "id",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "number",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "permalink",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "state",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "title",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "url",
                "args": null,
                "storageKey": null
              }
            ]
          }
        ]
      }
    ]
  }
];
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "SubmitLessonPullRequest_CreatePullRequestMutation",
    "type": "Mutation",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "operation": {
    "kind": "Operation",
    "name": "SubmitLessonPullRequest_CreatePullRequestMutation",
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "params": {
    "operationKind": "mutation",
    "name": "SubmitLessonPullRequest_CreatePullRequestMutation",
    "id": null,
    "text": "mutation SubmitLessonPullRequest_CreatePullRequestMutation(\n  $repoId: ID!\n  $title: String!\n  $headRefName: String!\n  $baseRefName: String!\n  $body: String!\n) {\n  gitHub {\n    createPullRequest(input: {title: $title, headRefName: $headRefName, baseRefName: $baseRefName, repositoryId: $repoId, maintainerCanModify: true, body: $body}) {\n      pullRequest {\n        body\n        id\n        number\n        permalink\n        state\n        title\n        url\n      }\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |json}
];
