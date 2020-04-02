/* @generated */

module Unions = {
  module Union_response_gitHub_repository_object_: {
    type wrapped;
    type response_gitHub_repository_object__gitHubBlob = {
      text: option(string),
      oid: string,
    };
    type gitHubBlob = response_gitHub_repository_object__gitHubBlob;
    type t = [ | `GitHubBlob(gitHubBlob) | `FutureAddedValue(Js.Json.t)];
    let unwrap: wrapped => t;
  } = {
    type wrapped;
    type response_gitHub_repository_object__gitHubBlob = {
      text: option(string),
      oid: string,
    };
    type gitHubBlob = response_gitHub_repository_object__gitHubBlob;
    external __unwrap_union: wrapped => {. "__typename": string} =
      "%identity";
    type t = [ | `GitHubBlob(gitHubBlob) | `FutureAddedValue(Js.Json.t)];
    external __unwrap_gitHubBlob: wrapped => gitHubBlob = "%identity";
    external __toJson: wrapped => Js.Json.t = "%identity";
    let unwrap = wrapped => {
      let unwrappedUnion = wrapped |> __unwrap_union;
      switch (unwrappedUnion##__typename) {
      | "GitHubBlob" => `GitHubBlob(wrapped |> __unwrap_gitHubBlob)
      | _ => `FutureAddedValue(wrapped |> __toJson)
      };
    };
  };

  type union_response_gitHub_repository_object_ = [
    | `GitHubBlob(Union_response_gitHub_repository_object_.gitHubBlob)
    | `FutureAddedValue(Js.Json.t)
  ];
};

open Unions;

module Types = {
  type repository = {
    object_: option(union_response_gitHub_repository_object_),
  };
  type gitHub = {repository: option(repository)};
};

open Types;

type response = {gitHub: option(gitHub)};
type refetchVariables = {
  repoName: option(string),
  repoOwner: option(string),
  branchAndFilePath: option(string),
};
let makeRefetchVariables =
    (~repoName=?, ~repoOwner=?, ~branchAndFilePath=?, ()): refetchVariables => {
  repoName,
  repoOwner,
  branchAndFilePath,
};
type variables = {
  repoName: string,
  repoOwner: string,
  branchAndFilePath: string,
};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"gitHub":{"n":""},"gitHub_repository":{"n":""},"gitHub_repository_object_":{"n":"","u":"response_gitHub_repository_object_"},"gitHub_repository_object__githubblob_text":{"n":""}}} |}
  ];
  let responseConverterMap = {
    "response_gitHub_repository_object_": Union_response_gitHub_repository_object_.unwrap,
  };
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
    "name": "repoName",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "repoOwner",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "branchAndFilePath",
    "type": "String!",
    "defaultValue": null
  }
],
v1 = [
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
v2 = [
  {
    "kind": "Variable",
    "name": "expression",
    "variableName": "branchAndFilePath"
  }
],
v3 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "__typename",
  "args": null,
  "storageKey": null
},
v4 = {
  "kind": "InlineFragment",
  "type": "GitHubBlob",
  "selections": [
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "oid",
      "args": null,
      "storageKey": null
    },
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "text",
      "args": null,
      "storageKey": null
    }
  ]
},
v5 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "id",
  "args": null,
  "storageKey": null
};
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "EggheadLessonTranscript_GetFileShaQuery",
    "type": "Query",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
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
            "args": (v1/*: any*/),
            "concreteType": "GitHubRepository",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": "object_",
                "name": "object",
                "storageKey": null,
                "args": (v2/*: any*/),
                "concreteType": null,
                "plural": false,
                "selections": [
                  (v3/*: any*/),
                  (v4/*: any*/)
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
    "name": "EggheadLessonTranscript_GetFileShaQuery",
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
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
            "args": (v1/*: any*/),
            "concreteType": "GitHubRepository",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": "object_",
                "name": "object",
                "storageKey": null,
                "args": (v2/*: any*/),
                "concreteType": null,
                "plural": false,
                "selections": [
                  (v3/*: any*/),
                  (v5/*: any*/),
                  (v4/*: any*/)
                ]
              },
              (v5/*: any*/)
            ]
          }
        ]
      }
    ]
  },
  "params": {
    "operationKind": "query",
    "name": "EggheadLessonTranscript_GetFileShaQuery",
    "id": null,
    "text": "query EggheadLessonTranscript_GetFileShaQuery(\n  $repoName: String!\n  $repoOwner: String!\n  $branchAndFilePath: String!\n) {\n  gitHub {\n    repository(name: $repoName, owner: $repoOwner) {\n      object_: object(expression: $branchAndFilePath) {\n        __typename\n        ... on GitHubBlob {\n          oid\n          text\n        }\n        id\n      }\n      id\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
