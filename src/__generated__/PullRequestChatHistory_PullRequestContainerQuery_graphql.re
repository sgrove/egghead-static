/* @generated */

module Types = {
  type response_gitHub_node_GitHubPullRequest = {
    getFragmentRefs:
      unit =>
      {
        .
        "__$fragment_ref__PullRequestChatHistory_PullRequestFragment": PullRequestChatHistory_PullRequestFragment_graphql.t,
      },
  };
  type response_gitHub_node = [
    | `GitHubPullRequest(response_gitHub_node_GitHubPullRequest)
    | `UnselectedUnionMember(string)
  ];
  type response_gitHub = {
    node:
      option(
        [
          | `GitHubPullRequest(response_gitHub_node_GitHubPullRequest)
          | `UnselectedUnionMember(string)
        ],
      ),
  };

  type response = {gitHub: option(response_gitHub)};
  type refetchVariables = {pullRequestId: option(string)};
  let makeRefetchVariables = (~pullRequestId=?, ()): refetchVariables => {
    pullRequestId: pullRequestId,
  };
  type variables = {pullRequestId: string};
};

let unwrap_response_gitHub_node:
  {. "__typename": string} =>
  [
    | `GitHubPullRequest(Types.response_gitHub_node_GitHubPullRequest)
    | `UnselectedUnionMember(string)
  ] =
  u =>
    switch (u##__typename) {
    | "GitHubPullRequest" => `GitHubPullRequest(u->Obj.magic)
    | v => `UnselectedUnionMember(v)
    };

let wrap_response_gitHub_node:
  [
    | `GitHubPullRequest(Types.response_gitHub_node_GitHubPullRequest)
    | `UnselectedUnionMember(string)
  ] =>
  {. "__typename": string} =
  fun
  | `GitHubPullRequest(v) => v->Obj.magic
  | `UnselectedUnionMember(v) => {"__typename": v};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"gitHub":{"n":""},"gitHub_node":{"n":"","u":"response_gitHub_node"},"gitHub_node_githubpullrequest":{"f":""}}} |json}
  ];
  let responseConverterMap = {
    "response_gitHub_node": unwrap_response_gitHub_node,
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
  let makeVariables = (~pullRequestId): variables => {
    pullRequestId: pullRequestId,
  };
};

type operationType = ReasonRelay.queryNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "pullRequestId",
    "type": "ID!",
    "defaultValue": null
  }
],
v1 = [
  {
    "kind": "Variable",
    "name": "id",
    "variableName": "pullRequestId"
  }
],
v2 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "__typename",
  "args": null,
  "storageKey": null
},
v3 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "id",
  "args": null,
  "storageKey": null
},
v4 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "body",
  "args": null,
  "storageKey": null
},
v5 = [
  {
    "kind": "Literal",
    "name": "last",
    "value": 100
  }
];
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "PullRequestChatHistory_PullRequestContainerQuery",
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
            "name": "node",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": null,
            "plural": false,
            "selections": [
              (v2/*: any*/),
              {
                "kind": "InlineFragment",
                "type": "GitHubPullRequest",
                "selections": [
                  {
                    "kind": "FragmentSpread",
                    "name": "PullRequestChatHistory_PullRequestFragment",
                    "args": null
                  }
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
    "name": "PullRequestChatHistory_PullRequestContainerQuery",
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
            "name": "node",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": null,
            "plural": false,
            "selections": [
              (v2/*: any*/),
              (v3/*: any*/),
              {
                "kind": "InlineFragment",
                "type": "GitHubPullRequest",
                "selections": [
                  {
                    "kind": "ScalarField",
                    "alias": null,
                    "name": "title",
                    "args": null,
                    "storageKey": null
                  },
                  (v4/*: any*/),
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
                    "name": "number",
                    "args": null,
                    "storageKey": null
                  },
                  {
                    "kind": "ScalarField",
                    "alias": null,
                    "name": "url",
                    "args": null,
                    "storageKey": null
                  },
                  {
                    "kind": "LinkedField",
                    "alias": null,
                    "name": "comments",
                    "storageKey": "comments(last:100)",
                    "args": (v5/*: any*/),
                    "concreteType": "GitHubIssueCommentConnection",
                    "plural": false,
                    "selections": [
                      {
                        "kind": "LinkedField",
                        "alias": null,
                        "name": "edges",
                        "storageKey": null,
                        "args": null,
                        "concreteType": "GitHubIssueCommentEdge",
                        "plural": true,
                        "selections": [
                          {
                            "kind": "LinkedField",
                            "alias": null,
                            "name": "node",
                            "storageKey": null,
                            "args": null,
                            "concreteType": "GitHubIssueComment",
                            "plural": false,
                            "selections": [
                              (v3/*: any*/),
                              {
                                "kind": "LinkedField",
                                "alias": null,
                                "name": "author",
                                "storageKey": null,
                                "args": null,
                                "concreteType": null,
                                "plural": false,
                                "selections": [
                                  (v2/*: any*/),
                                  {
                                    "kind": "ScalarField",
                                    "alias": null,
                                    "name": "login",
                                    "args": null,
                                    "storageKey": null
                                  },
                                  {
                                    "kind": "ScalarField",
                                    "alias": null,
                                    "name": "avatarUrl",
                                    "args": null,
                                    "storageKey": null
                                  }
                                ]
                              },
                              {
                                "kind": "ScalarField",
                                "alias": null,
                                "name": "createdAt",
                                "args": null,
                                "storageKey": null
                              },
                              (v4/*: any*/),
                              (v2/*: any*/)
                            ]
                          },
                          {
                            "kind": "ScalarField",
                            "alias": null,
                            "name": "cursor",
                            "args": null,
                            "storageKey": null
                          }
                        ]
                      },
                      {
                        "kind": "LinkedField",
                        "alias": null,
                        "name": "pageInfo",
                        "storageKey": null,
                        "args": null,
                        "concreteType": "GitHubPageInfo",
                        "plural": false,
                        "selections": [
                          {
                            "kind": "ScalarField",
                            "alias": null,
                            "name": "hasPreviousPage",
                            "args": null,
                            "storageKey": null
                          },
                          {
                            "kind": "ScalarField",
                            "alias": null,
                            "name": "startCursor",
                            "args": null,
                            "storageKey": null
                          }
                        ]
                      }
                    ]
                  },
                  {
                    "kind": "LinkedHandle",
                    "alias": null,
                    "name": "comments",
                    "args": (v5/*: any*/),
                    "handle": "connection",
                    "key": "PullRequestChatHistory_PullRequestFragment_comments",
                    "filters": null
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
    "operationKind": "query",
    "name": "PullRequestChatHistory_PullRequestContainerQuery",
    "id": null,
    "text": "query PullRequestChatHistory_PullRequestContainerQuery(\n  $pullRequestId: ID!\n) {\n  gitHub {\n    node(id: $pullRequestId) {\n      __typename\n      ... on GitHubPullRequest {\n        ...PullRequestChatHistory_PullRequestFragment\n      }\n      id\n    }\n  }\n}\n\nfragment PullRequestChatHistory_CommentFragment on GitHubComment {\n  id\n  author {\n    __typename\n    login\n    avatarUrl\n  }\n  createdAt\n  body\n}\n\nfragment PullRequestChatHistory_PullRequestFragment on GitHubPullRequest {\n  id\n  title\n  body\n  state\n  number\n  url\n  comments(last: 100) {\n    edges {\n      node {\n        id\n        ...PullRequestChatHistory_CommentFragment\n        __typename\n      }\n      cursor\n    }\n    pageInfo {\n      hasPreviousPage\n      startCursor\n    }\n  }\n}\n",
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
