/* @generated */

module Types = {
  type response_gitHub_repository_object__GitHubBlob = {
    text: option(string),
    sha: string,
  };
  type response_gitHub_repository_object_ = [
    | `GitHubBlob(response_gitHub_repository_object__GitHubBlob)
    | `UnselectedUnionMember(string)
  ];
  type response_gitHub_repository = {
    object_:
      option(
        [
          | `GitHubBlob(response_gitHub_repository_object__GitHubBlob)
          | `UnselectedUnionMember(string)
        ],
      ),
  };
  type response_gitHub = {repository: option(response_gitHub_repository)};

  type response = {gitHub: option(response_gitHub)};
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
};

let unwrap_response_gitHub_repository_object_:
  {. "__typename": string} =>
  [
    | `GitHubBlob(Types.response_gitHub_repository_object__GitHubBlob)
    | `UnselectedUnionMember(string)
  ] =
  u =>
    switch (u##__typename) {
    | "GitHubBlob" => `GitHubBlob(u->Obj.magic)
    | v => `UnselectedUnionMember(v)
    };

let wrap_response_gitHub_repository_object_:
  [
    | `GitHubBlob(Types.response_gitHub_repository_object__GitHubBlob)
    | `UnselectedUnionMember(string)
  ] =>
  {. "__typename": string} =
  fun
  | `GitHubBlob(v) => v->Obj.magic
  | `UnselectedUnionMember(v) => {"__typename": v};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"gitHub":{"n":""},"gitHub_repository":{"n":""},"gitHub_repository_object_":{"n":"","u":"response_gitHub_repository_object_"},"gitHub_repository_object__githubblob_text":{"n":""}}} |json}
  ];
  let responseConverterMap = {
    "response_gitHub_repository_object_": unwrap_response_gitHub_repository_object_,
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

type preloadToken;

module Utils = {
  open Types;
  let makeVariables = (~repoName, ~repoOwner, ~branchAndFilePath): variables => {
    repoName,
    repoOwner,
    branchAndFilePath,
  };
};

type operationType = ReasonRelay.queryNode;

let node: operationType = [%raw
  {json| (function(){
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
      "alias": "sha",
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
    "name": "RemoteFile_GetFileShaQuery",
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
    "name": "RemoteFile_GetFileShaQuery",
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
    "name": "RemoteFile_GetFileShaQuery",
    "id": null,
    "text": "query RemoteFile_GetFileShaQuery(\n  $repoName: String!\n  $repoOwner: String!\n  $branchAndFilePath: String!\n) {\n  gitHub {\n    repository(name: $repoName, owner: $repoOwner) {\n      object_: object(expression: $branchAndFilePath) {\n        __typename\n        ... on GitHubBlob {\n          sha: oid\n          text\n        }\n        id\n      }\n      id\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |json}
];
