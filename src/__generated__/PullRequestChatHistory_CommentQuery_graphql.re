/* @generated */

module Types = {
  type response_gitHub_search_edges_node_GitHubPullRequest = {
    id: string,
    getFragmentRefs:
      unit =>
      {
        .
        "__$fragment_ref__PullRequestChatHistory_PullRequestFragment": PullRequestChatHistory_PullRequestFragment_graphql.t,
      },
  };
  type response_gitHub_search_edges_node = [
    | `GitHubPullRequest(response_gitHub_search_edges_node_GitHubPullRequest)
    | `UnselectedUnionMember(string)
  ];
  type response_gitHub_search_edges = {
    node:
      option(
        [
          | `GitHubPullRequest(
              response_gitHub_search_edges_node_GitHubPullRequest,
            )
          | `UnselectedUnionMember(string)
        ],
      ),
  };
  type response_gitHub_search = {
    edges: option(array(option(response_gitHub_search_edges))),
  };
  type response_gitHub = {search: response_gitHub_search};

  type response = {gitHub: option(response_gitHub)};
  type refetchVariables = {
    query: option(string),
    last: option(int),
  };
  let makeRefetchVariables = (~query=?, ~last=?, ()): refetchVariables => {
    query,
    last,
  };
  type variables = {
    query: string,
    last: int,
  };
};

let unwrap_response_gitHub_search_edges_node:
  {. "__typename": string} =>
  [
    | `GitHubPullRequest(
        Types.response_gitHub_search_edges_node_GitHubPullRequest,
      )
    | `UnselectedUnionMember(string)
  ] =
  u =>
    switch (u##__typename) {
    | "GitHubPullRequest" => `GitHubPullRequest(u->Obj.magic)
    | v => `UnselectedUnionMember(v)
    };

let wrap_response_gitHub_search_edges_node:
  [
    | `GitHubPullRequest(
        Types.response_gitHub_search_edges_node_GitHubPullRequest,
      )
    | `UnselectedUnionMember(string)
  ] =>
  {. "__typename": string} =
  fun
  | `GitHubPullRequest(v) => v->Obj.magic
  | `UnselectedUnionMember(v) => {"__typename": v};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"gitHub":{"n":""},"gitHub_search_edges":{"n":"","na":""},"gitHub_search_edges_node":{"n":"","u":"response_gitHub_search_edges_node"},"gitHub_search_edges_node_githubpullrequest":{"f":""}}} |json}
  ];
  let responseConverterMap = {
    "response_gitHub_search_edges_node": unwrap_response_gitHub_search_edges_node,
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
  let getConnectionNodes_search:
    response_gitHub_search => array(response_gitHub_search_edges_node) =
    connection =>
      switch (connection.edges) {
      | None => [||]
      | Some(edges) =>
        edges
        ->Belt.Array.keepMap(edge =>
            switch (edge) {
            | None => None
            | Some(edge) =>
              switch (edge.node) {
              | None => None
              | Some(node) => Some(node)
              }
            }
          )
      };

  let makeVariables = (~query, ~last): variables => {query, last};
};

type operationType = ReasonRelay.queryNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "query",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "last",
    "type": "Int!",
    "defaultValue": null
  }
],
v1 = {
  "kind": "Variable",
  "name": "query",
  "variableName": "query"
},
v2 = {
  "kind": "Literal",
  "name": "type",
  "value": "ISSUE"
},
v3 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "__typename",
  "args": null,
  "storageKey": null
},
v4 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "id",
  "args": null,
  "storageKey": null
},
v5 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "cursor",
  "args": null,
  "storageKey": null
},
v6 = {
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
},
v7 = [
  {
    "kind": "Variable",
    "name": "last",
    "variableName": "last"
  },
  (v1/*: any*/),
  (v2/*: any*/)
],
v8 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "body",
  "args": null,
  "storageKey": null
},
v9 = [
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
    "name": "PullRequestChatHistory_CommentQuery",
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
            "alias": "search",
            "name": "__PullRequestChatHistory_CommentQuery_gitHub_search_connection",
            "storageKey": null,
            "args": [
              (v1/*: any*/),
              (v2/*: any*/)
            ],
            "concreteType": "GitHubSearchResultItemConnection",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "edges",
                "storageKey": null,
                "args": null,
                "concreteType": "GitHubSearchResultItemEdge",
                "plural": true,
                "selections": [
                  {
                    "kind": "LinkedField",
                    "alias": null,
                    "name": "node",
                    "storageKey": null,
                    "args": null,
                    "concreteType": null,
                    "plural": false,
                    "selections": [
                      (v3/*: any*/),
                      {
                        "kind": "InlineFragment",
                        "type": "GitHubPullRequest",
                        "selections": [
                          (v4/*: any*/),
                          {
                            "kind": "FragmentSpread",
                            "name": "PullRequestChatHistory_PullRequestFragment",
                            "args": null
                          }
                        ]
                      }
                    ]
                  },
                  (v5/*: any*/)
                ]
              },
              (v6/*: any*/)
            ]
          }
        ]
      }
    ]
  },
  "operation": {
    "kind": "Operation",
    "name": "PullRequestChatHistory_CommentQuery",
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
            "name": "search",
            "storageKey": null,
            "args": (v7/*: any*/),
            "concreteType": "GitHubSearchResultItemConnection",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "edges",
                "storageKey": null,
                "args": null,
                "concreteType": "GitHubSearchResultItemEdge",
                "plural": true,
                "selections": [
                  {
                    "kind": "LinkedField",
                    "alias": null,
                    "name": "node",
                    "storageKey": null,
                    "args": null,
                    "concreteType": null,
                    "plural": false,
                    "selections": [
                      (v3/*: any*/),
                      {
                        "kind": "InlineFragment",
                        "type": "GitHubPullRequest",
                        "selections": [
                          (v4/*: any*/),
                          {
                            "kind": "ScalarField",
                            "alias": null,
                            "name": "title",
                            "args": null,
                            "storageKey": null
                          },
                          (v8/*: any*/),
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
                            "args": (v9/*: any*/),
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
                                      (v4/*: any*/),
                                      {
                                        "kind": "LinkedField",
                                        "alias": null,
                                        "name": "author",
                                        "storageKey": null,
                                        "args": null,
                                        "concreteType": null,
                                        "plural": false,
                                        "selections": [
                                          (v3/*: any*/),
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
                                      (v8/*: any*/),
                                      (v3/*: any*/)
                                    ]
                                  },
                                  (v5/*: any*/)
                                ]
                              },
                              (v6/*: any*/)
                            ]
                          },
                          {
                            "kind": "LinkedHandle",
                            "alias": null,
                            "name": "comments",
                            "args": (v9/*: any*/),
                            "handle": "connection",
                            "key": "PullRequestChatHistory_PullRequestFragment_comments",
                            "filters": null
                          }
                        ]
                      }
                    ]
                  },
                  (v5/*: any*/)
                ]
              },
              (v6/*: any*/)
            ]
          },
          {
            "kind": "LinkedHandle",
            "alias": null,
            "name": "search",
            "args": (v7/*: any*/),
            "handle": "connection",
            "key": "PullRequestChatHistory_CommentQuery_gitHub_search",
            "filters": [
              "query",
              "type"
            ]
          }
        ]
      }
    ]
  },
  "params": {
    "operationKind": "query",
    "name": "PullRequestChatHistory_CommentQuery",
    "id": null,
    "text": "query PullRequestChatHistory_CommentQuery(\n  $query: String!\n  $last: Int!\n) {\n  gitHub {\n    search(query: $query, type: ISSUE, last: $last) {\n      edges {\n        node {\n          __typename\n          ... on GitHubPullRequest {\n            id\n            ...PullRequestChatHistory_PullRequestFragment\n          }\n        }\n        cursor\n      }\n      pageInfo {\n        hasPreviousPage\n        startCursor\n      }\n    }\n  }\n}\n\nfragment PullRequestChatHistory_CommentFragment on GitHubComment {\n  id\n  author {\n    __typename\n    login\n    avatarUrl\n  }\n  createdAt\n  body\n}\n\nfragment PullRequestChatHistory_PullRequestFragment on GitHubPullRequest {\n  id\n  title\n  body\n  state\n  number\n  url\n  comments(last: 100) {\n    edges {\n      node {\n        id\n        ...PullRequestChatHistory_CommentFragment\n        __typename\n      }\n      cursor\n    }\n    pageInfo {\n      hasPreviousPage\n      startCursor\n    }\n  }\n}\n",
    "metadata": {
      "connection": [
        {
          "count": "last",
          "cursor": null,
          "direction": "backward",
          "path": [
            "gitHub",
            "search"
          ]
        }
      ]
    }
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
