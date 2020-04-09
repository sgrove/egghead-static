/* @generated */

type enum_GitHubPullRequestState = [
  | `CLOSED
  | `MERGED
  | `OPEN
  | `FutureAddedValue(string)
];

let unwrap_enum_GitHubPullRequestState: string => enum_GitHubPullRequestState =
  fun
  | "CLOSED" => `CLOSED
  | "MERGED" => `MERGED
  | "OPEN" => `OPEN
  | v => `FutureAddedValue(v);

let wrap_enum_GitHubPullRequestState: enum_GitHubPullRequestState => string =
  fun
  | `CLOSED => "CLOSED"
  | `MERGED => "MERGED"
  | `OPEN => "OPEN"
  | `FutureAddedValue(v) => v;

module Types = {
  type response_gitHub_search_edges_node_GitHubPullRequest = {
    number: int,
    state: [ | `CLOSED | `MERGED | `OPEN | `FutureAddedValue(string)],
    body: string,
    title: string,
    id: string,
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
    {| {"__root":{"gitHub":{"n":""},"gitHub_search_edges":{"n":"","na":""},"gitHub_search_edges_node":{"n":"","u":"response_gitHub_search_edges_node"},"gitHub_search_edges_node_githubpullrequest_state":{"e":"enum_GitHubPullRequestState"}}} |}
  ];
  let responseConverterMap = {
    "response_gitHub_search_edges_node": unwrap_response_gitHub_search_edges_node,
    "enum_GitHubPullRequestState": unwrap_enum_GitHubPullRequestState,
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
v3 = [
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
          {
            "kind": "ScalarField",
            "alias": null,
            "name": "__typename",
            "args": null,
            "storageKey": null
          },
          {
            "kind": "InlineFragment",
            "type": "GitHubPullRequest",
            "selections": [
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
                "name": "title",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "body",
                "args": null,
                "storageKey": null
              },
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
              }
            ]
          }
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
],
v4 = [
  {
    "kind": "Variable",
    "name": "last",
    "variableName": "last"
  },
  (v1/*: any*/),
  (v2/*: any*/)
];
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "RelayCourseTree_SearchForPullRequestsQuery",
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
            "name": "__RelayCourseTree_SearchForPullRequestsQuery_gitHub_search_connection",
            "storageKey": null,
            "args": [
              (v1/*: any*/),
              (v2/*: any*/)
            ],
            "concreteType": "GitHubSearchResultItemConnection",
            "plural": false,
            "selections": (v3/*: any*/)
          }
        ]
      }
    ]
  },
  "operation": {
    "kind": "Operation",
    "name": "RelayCourseTree_SearchForPullRequestsQuery",
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
            "args": (v4/*: any*/),
            "concreteType": "GitHubSearchResultItemConnection",
            "plural": false,
            "selections": (v3/*: any*/)
          },
          {
            "kind": "LinkedHandle",
            "alias": null,
            "name": "search",
            "args": (v4/*: any*/),
            "handle": "connection",
            "key": "RelayCourseTree_SearchForPullRequestsQuery_gitHub_search",
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
    "name": "RelayCourseTree_SearchForPullRequestsQuery",
    "id": null,
    "text": "query RelayCourseTree_SearchForPullRequestsQuery(\n  $query: String!\n  $last: Int!\n) {\n  gitHub {\n    search(query: $query, type: ISSUE, last: $last) {\n      edges {\n        node {\n          __typename\n          ... on GitHubPullRequest {\n            id\n            title\n            body\n            state\n            number\n          }\n        }\n        cursor\n      }\n      pageInfo {\n        hasPreviousPage\n        startCursor\n      }\n    }\n  }\n}\n",
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
