/* @generated */

module Unions = {};

module Types = {
  type commit = {message: string};
  type createOrUpdateFileContent_oneGraph = {commit};
  type gitHub = {createOrUpdateFileContent_oneGraph};
};

open Types;

type response = {gitHub: option(gitHub)};
type variables = {
  repoOwner: string,
  repoName: string,
  branchName: string,
  path: string,
  message: string,
  content: string,
  sha: string,
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
  },
  {
    "kind": "LocalArgument",
    "name": "path",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "message",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "content",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "sha",
    "type": "String!",
    "defaultValue": null
  }
],
v1 = [
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
        "name": "existingFileSha",
        "variableName": "sha"
      },
      {
        "kind": "Variable",
        "name": "message",
        "variableName": "message"
      },
      {
        "kind": "Variable",
        "name": "path",
        "variableName": "path"
      },
      {
        "kind": "Variable",
        "name": "plainContent",
        "variableName": "content"
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
v2 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "message",
  "args": null,
  "storageKey": null
};
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "RelaySubmitPullRequest_UpdateFileMutation",
    "type": "Mutation",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
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
            "name": "createOrUpdateFileContent_oneGraph",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubCreateOrUpdateFileContent_oneGraphResponsePayload",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "commit",
                "storageKey": null,
                "args": null,
                "concreteType": "GitHubCommit",
                "plural": false,
                "selections": [
                  (v2/*: any*/)
                ]
              }
            ]
          }
        ]
      }
    ]
  },
  "operation": {
    "kind": "Operation",
    "name": "RelaySubmitPullRequest_UpdateFileMutation",
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
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
            "name": "createOrUpdateFileContent_oneGraph",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubCreateOrUpdateFileContent_oneGraphResponsePayload",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "commit",
                "storageKey": null,
                "args": null,
                "concreteType": "GitHubCommit",
                "plural": false,
                "selections": [
                  (v2/*: any*/),
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
    ]
  },
  "params": {
    "operationKind": "mutation",
    "name": "RelaySubmitPullRequest_UpdateFileMutation",
    "id": null,
    "text": "mutation RelaySubmitPullRequest_UpdateFileMutation(\n  $repoOwner: String!\n  $repoName: String!\n  $branchName: String!\n  $path: String!\n  $message: String!\n  $content: String!\n  $sha: String!\n) {\n  gitHub {\n    createOrUpdateFileContent_oneGraph(input: {message: $message, path: $path, repoName: $repoName, repoOwner: $repoOwner, branchName: $branchName, plainContent: $content, existingFileSha: $sha}) {\n      commit {\n        message\n        id\n      }\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
