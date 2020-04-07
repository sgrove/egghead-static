/* @generated */

module Unions = {};

module Types = {
  type pullRequest = {
    url: string,
    id: string,
    number: int,
    title: string,
    permalink: string,
  };
  type createPullRequest = {pullRequest: option(pullRequest)};
  type gitHub = {createPullRequest: option(createPullRequest)};
};

open Types;

type response = {gitHub: option(gitHub)};
type variables = {
  repoId: string,
  title: string,
  headRefName: string,
  baseRefName: string,
  body: string,
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"gitHub":{"n":""},"gitHub_createPullRequest":{"n":""},"gitHub_createPullRequest_pullRequest":{"n":""}}} |}
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
    {| {"__root":{"gitHub":{"n":""},"gitHub_createPullRequest":{"n":""},"gitHub_createPullRequest_pullRequest":{"n":""}}} |}
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
                "name": "url",
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
                "name": "title",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "permalink",
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
    "name": "RelaySubmitPullRequest_CreatePullRequestMutation",
    "type": "Mutation",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "operation": {
    "kind": "Operation",
    "name": "RelaySubmitPullRequest_CreatePullRequestMutation",
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "params": {
    "operationKind": "mutation",
    "name": "RelaySubmitPullRequest_CreatePullRequestMutation",
    "id": null,
    "text": "mutation RelaySubmitPullRequest_CreatePullRequestMutation(\n  $repoId: ID!\n  $title: String!\n  $headRefName: String!\n  $baseRefName: String!\n  $body: String!\n) {\n  gitHub {\n    createPullRequest(input: {title: $title, headRefName: $headRefName, baseRefName: $baseRefName, repositoryId: $repoId, maintainerCanModify: true, body: $body}) {\n      pullRequest {\n        url\n        id\n        number\n        title\n        permalink\n      }\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
