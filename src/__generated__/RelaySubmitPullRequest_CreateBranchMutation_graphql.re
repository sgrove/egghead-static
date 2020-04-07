/* @generated */

module Unions = {};

module Types = {
  type ref_ = {
    name: string,
    id: string,
  };
  type createBranch_oneGraph = {ref_};
  type gitHub = {createBranch_oneGraph};
};

open Types;

type response = {gitHub: option(gitHub)};
type variables = {
  repoOwner: string,
  repoName: string,
  branchName: string,
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"gitHub":{"n":""}}} |}
  ];
  let wrapResponseConverterMap = ();
  let convertWrapResponse = v =>
    v
    ->ReasonRelay._convertObj(
        wrapResponseConverter,
        wrapResponseConverterMap,
        Js.null,
      );

  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"gitHub":{"n":""}}} |}
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

type operationType = ReasonRelay.mutationNode;

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
  },
  {
    "kind": "LocalArgument",
    "name": "branchName",
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
        "name": "createBranch_oneGraph",
        "storageKey": null,
        "args": [
          {
            "kind": "ObjectValue",
            "name": "input",
            "fields": [
              {
                "kind": "Variable",
                "name": "branchName",
                "variableName": "branchName"
              },
              {
                "kind": "Variable",
                "name": "repoName",
                "variableName": "repoName"
              },
              {
                "kind": "Variable",
                "name": "repoOwner",
                "variableName": "repoOwner"
              }
            ]
          }
        ],
        "concreteType": "GitHubCreateBranch_oneGraphResponsePayload",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": "ref_",
            "name": "ref",
            "storageKey": null,
            "args": null,
            "concreteType": "GitHubRef",
            "plural": false,
            "selections": [
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "name",
                "args": null,
                "storageKey": null
              },
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
    ]
  }
];
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "RelaySubmitPullRequest_CreateBranchMutation",
    "type": "Mutation",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "operation": {
    "kind": "Operation",
    "name": "RelaySubmitPullRequest_CreateBranchMutation",
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "params": {
    "operationKind": "mutation",
    "name": "RelaySubmitPullRequest_CreateBranchMutation",
    "id": null,
    "text": "mutation RelaySubmitPullRequest_CreateBranchMutation(\n  $repoOwner: String!\n  $repoName: String!\n  $branchName: String!\n) {\n  gitHub {\n    createBranch_oneGraph(input: {branchName: $branchName, repoName: $repoName, repoOwner: $repoOwner}) {\n      ref_: ref {\n        name\n        id\n      }\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
