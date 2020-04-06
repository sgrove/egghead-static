/* @generated */

module Unions = {
  module Union_response_gitHub_search_edges_node: {
    type wrapped;
    type response_gitHub_search_edges_node_gitHubPullRequest = {
      getFragmentRefs:
        unit =>
        {
          .
          "__$fragment_ref__RelayPRChatHistory_PullRequestFragment": RelayPRChatHistory_PullRequestFragment_graphql.t,
        },
    };
    type gitHubPullRequest = response_gitHub_search_edges_node_gitHubPullRequest;
    type t = [
      | `GitHubPullRequest(gitHubPullRequest)
      | `UnselectedUnionMember(string)
    ];
    let unwrap: wrapped => t;
  } = {
    type wrapped;
    type response_gitHub_search_edges_node_gitHubPullRequest = {
      getFragmentRefs:
        unit =>
        {
          .
          "__$fragment_ref__RelayPRChatHistory_PullRequestFragment": RelayPRChatHistory_PullRequestFragment_graphql.t,
        },
    };
    type gitHubPullRequest = response_gitHub_search_edges_node_gitHubPullRequest;
    external __unwrap_union: wrapped => {. "__typename": string} =
      "%identity";
    type t = [
      | `GitHubPullRequest(gitHubPullRequest)
      | `UnselectedUnionMember(string)
    ];
    external __unwrap_gitHubPullRequest: wrapped => gitHubPullRequest =
      "%identity";
    external __toJson: wrapped => Js.Json.t = "%identity";
    let unwrap = wrapped => {
      let unwrappedUnion = wrapped |> __unwrap_union;
      switch (unwrappedUnion##__typename) {
      | "GitHubPullRequest" =>
        `GitHubPullRequest(wrapped |> __unwrap_gitHubPullRequest)
      | typename => `UnselectedUnionMember(typename)
      };
    };
  };

  type union_response_gitHub_search_edges_node = [
    | `GitHubPullRequest(
        Union_response_gitHub_search_edges_node.gitHubPullRequest,
      )
    | `UnselectedUnionMember(string)
  ];
};

open Unions;

module Types = {
  type edges = {node: option(union_response_gitHub_search_edges_node)};
  type search = {edges: option(array(option(edges)))};
  type gitHub = {search};
};

open Types;

type response = {gitHub: option(gitHub)};
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

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"gitHub":{"n":""},"gitHub_search_edges":{"n":"","na":""},"gitHub_search_edges_node":{"n":"","u":"response_gitHub_search_edges_node"},"gitHub_search_edges_node_githubpullrequest":{"f":""}}} |}
  ];
  let responseConverterMap = {
    "response_gitHub_search_edges_node": Union_response_gitHub_search_edges_node.unwrap,
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

module Utils = {
  let getConnectionNodes_search:
    search => array(union_response_gitHub_search_edges_node) =
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
};

type operationType = ReasonRelay.queryNode;

let node: operationType = [%bs.raw
  {| (function(){
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
  "name": "cursor",
  "args": null,
  "storageKey": null
},
v5 = {
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
v6 = [
  {
    "kind": "Variable",
    "name": "last",
    "variableName": "last"
  },
  (v1/*: any*/),
  (v2/*: any*/)
],
v7 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "id",
  "args": null,
  "storageKey": null
},
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
    "name": "RelayPRChatHistory_CommentQuery",
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
            "name": "__RelayPRChatHistory_CommentQuery_gitHub_search_connection",
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
                          {
                            "kind": "FragmentSpread",
                            "name": "RelayPRChatHistory_PullRequestFragment",
                            "args": null
                          }
                        ]
                      }
                    ]
                  },
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
  "operation": {
    "kind": "Operation",
    "name": "RelayPRChatHistory_CommentQuery",
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
            "args": (v6/*: any*/),
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
                          (v7/*: any*/),
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
                                      (v7/*: any*/),
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
                                  (v4/*: any*/)
                                ]
                              },
                              (v5/*: any*/)
                            ]
                          },
                          {
                            "kind": "LinkedHandle",
                            "alias": null,
                            "name": "comments",
                            "args": (v9/*: any*/),
                            "handle": "connection",
                            "key": "RelayPRChatHistory_PullRequestFragment_comments",
                            "filters": null
                          }
                        ]
                      }
                    ]
                  },
                  (v4/*: any*/)
                ]
              },
              (v5/*: any*/)
            ]
          },
          {
            "kind": "LinkedHandle",
            "alias": null,
            "name": "search",
            "args": (v6/*: any*/),
            "handle": "connection",
            "key": "RelayPRChatHistory_CommentQuery_gitHub_search",
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
    "name": "RelayPRChatHistory_CommentQuery",
    "id": null,
    "text": "query RelayPRChatHistory_CommentQuery(\n  $query: String!\n  $last: Int!\n) {\n  gitHub {\n    search(query: $query, type: ISSUE, last: $last) {\n      edges {\n        node {\n          __typename\n          ... on GitHubPullRequest {\n            ...RelayPRChatHistory_PullRequestFragment\n          }\n        }\n        cursor\n      }\n      pageInfo {\n        hasPreviousPage\n        startCursor\n      }\n    }\n  }\n}\n\nfragment RelayPRChatHistory_CommentFragment on GitHubComment {\n  id\n  author {\n    __typename\n    login\n    avatarUrl\n  }\n  createdAt\n  body\n}\n\nfragment RelayPRChatHistory_PullRequestFragment on GitHubPullRequest {\n  id\n  title\n  body\n  state\n  number\n  comments(last: 100) {\n    edges {\n      node {\n        ...RelayPRChatHistory_CommentFragment\n        id\n        __typename\n      }\n      cursor\n    }\n    pageInfo {\n      hasPreviousPage\n      startCursor\n    }\n  }\n}\n",
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
})() |}
];
