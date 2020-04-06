/* @generated */

module Unions = {
  module Union_response_gitHub_node: {
    type wrapped;
    type response_gitHub_node_gitHubPullRequest = {
      getFragmentRefs:
        unit =>
        {
          .
          "__$fragment_ref__RelayPRChatHistory_PullRequestFragment": RelayPRChatHistory_PullRequestFragment_graphql.t,
        },
    };
    type gitHubPullRequest = response_gitHub_node_gitHubPullRequest;
    type t = [
      | `GitHubPullRequest(gitHubPullRequest)
      | `UnselectedUnionMember(string)
    ];
    let unwrap: wrapped => t;
  } = {
    type wrapped;
    type response_gitHub_node_gitHubPullRequest = {
      getFragmentRefs:
        unit =>
        {
          .
          "__$fragment_ref__RelayPRChatHistory_PullRequestFragment": RelayPRChatHistory_PullRequestFragment_graphql.t,
        },
    };
    type gitHubPullRequest = response_gitHub_node_gitHubPullRequest;
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

  type union_response_gitHub_node = [
    | `GitHubPullRequest(Union_response_gitHub_node.gitHubPullRequest)
    | `UnselectedUnionMember(string)
  ];
};

open Unions;

module Types = {
  type gitHub = {node: option(union_response_gitHub_node)};
};

open Types;

type response = {gitHub: option(gitHub)};
type refetchVariables = {pullRequestId: option(string)};
let makeRefetchVariables = (~pullRequestId=?, ()): refetchVariables => {
  pullRequestId: pullRequestId,
};
type variables = {pullRequestId: string};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"gitHub":{"n":""},"gitHub_node":{"n":"","u":"response_gitHub_node"},"gitHub_node_githubpullrequest":{"f":""}}} |}
  ];
  let responseConverterMap = {
    "response_gitHub_node": Union_response_gitHub_node.unwrap,
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
    "name": "RelayPRChatHistory_PullRequestContainerQuery",
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
                    "name": "RelayPRChatHistory_PullRequestFragment",
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
    "name": "RelayPRChatHistory_PullRequestContainerQuery",
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
                    "key": "RelayPRChatHistory_PullRequestFragment_comments",
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
    "name": "RelayPRChatHistory_PullRequestContainerQuery",
    "id": null,
    "text": "query RelayPRChatHistory_PullRequestContainerQuery(\n  $pullRequestId: ID!\n) {\n  gitHub {\n    node(id: $pullRequestId) {\n      __typename\n      ... on GitHubPullRequest {\n        ...RelayPRChatHistory_PullRequestFragment\n      }\n      id\n    }\n  }\n}\n\nfragment RelayPRChatHistory_CommentFragment on GitHubComment {\n  id\n  author {\n    __typename\n    login\n    avatarUrl\n  }\n  createdAt\n  body\n}\n\nfragment RelayPRChatHistory_PullRequestFragment on GitHubPullRequest {\n  id\n  title\n  body\n  state\n  number\n  comments(last: 100) {\n    edges {\n      node {\n        ...RelayPRChatHistory_CommentFragment\n        id\n        __typename\n      }\n      cursor\n    }\n    pageInfo {\n      hasPreviousPage\n      startCursor\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
