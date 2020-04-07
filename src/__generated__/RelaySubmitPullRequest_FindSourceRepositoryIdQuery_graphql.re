/* @generated */

module Unions = {};

module Types = {
  type repository = {id: string};
  type gitHub = {repository: option(repository)};
};

open Types;

type response = {gitHub: option(gitHub)};
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

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"gitHub":{"n":""},"gitHub_repository":{"n":""}}} |}
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
    {| {} |}
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

module Utils = {};

type operationType = ReasonRelay.queryNode;

let node: operationType = [%bs.raw
  {| (function(){
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
    "name": "RelaySubmitPullRequest_FindSourceRepositoryIdQuery",
    "type": "Query",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "operation": {
    "kind": "Operation",
    "name": "RelaySubmitPullRequest_FindSourceRepositoryIdQuery",
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "params": {
    "operationKind": "query",
    "name": "RelaySubmitPullRequest_FindSourceRepositoryIdQuery",
    "id": null,
    "text": "query RelaySubmitPullRequest_FindSourceRepositoryIdQuery(\n  $repoOwner: String!\n  $repoName: String!\n) {\n  gitHub {\n    repository(owner: $repoOwner, name: $repoName) {\n      id\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
