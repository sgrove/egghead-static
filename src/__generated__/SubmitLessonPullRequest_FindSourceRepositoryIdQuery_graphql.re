/* @generated */

module Types = {
  type response_gitHub_repository = {id: string};
  type response_gitHub = {repository: option(response_gitHub_repository)};

  type response = {gitHub: option(response_gitHub)};
  type refetchVariables = {
    repoOwner: option(string),
    repoName: option(string),
  };
  let makeRefetchVariables = (~repoOwner=?, ~repoName=?, ()): refetchVariables => {
    repoOwner,
    repoName,
  };
  type variables = {
    repoOwner: string,
    repoName: string,
  };
};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"gitHub":{"n":""},"gitHub_repository":{"n":""}}} |json}
  ];
  let responseConverterMap = ();
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

type preloadToken;

module Utils = {
  open Types;
  let makeVariables = (~repoOwner, ~repoName): variables => {
    repoOwner,
    repoName,
  };
};

type operationType = ReasonRelay.queryNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "repoOwner",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "repoName",
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
    "concreteType": "GitHubQuery",
    "plural": false,
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "repository",
        "storageKey": null,
        "args": [
          {
            "kind": "Variable",
            "name": "name",
            "variableName": "repoName"
          },
          {
            "kind": "Variable",
            "name": "owner",
            "variableName": "repoOwner"
          }
        ],
        "concreteType": "GitHubRepository",
        "plural": false,
        "selections": [
          {
            "kind": "ScalarField",
            "alias": null,
            "name": "id",
            "args": null,
            "storageKey": null
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
    "name": "SubmitLessonPullRequest_FindSourceRepositoryIdQuery",
    "type": "Query",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "operation": {
    "kind": "Operation",
    "name": "SubmitLessonPullRequest_FindSourceRepositoryIdQuery",
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "params": {
    "operationKind": "query",
    "name": "SubmitLessonPullRequest_FindSourceRepositoryIdQuery",
    "id": null,
    "text": "query SubmitLessonPullRequest_FindSourceRepositoryIdQuery(\n  $repoOwner: String!\n  $repoName: String!\n) {\n  gitHub {\n    repository(owner: $repoOwner, name: $repoName) {\n      id\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |json}
];

include ReasonRelay.MakePreloadQuery({
  type variables = Types.variables;
  type queryPreloadToken = preloadToken;
  let query = node;
  let convertVariables = Internal.convertVariables;
});
