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
  type fragment_comments_edges_node = {
    id: string,
    getFragmentRefs:
      unit =>
      {
        .
        "__$fragment_ref__PullRequestChatHistory_CommentFragment": PullRequestChatHistory_CommentFragment_graphql.t,
      },
  };
  type fragment_comments_edges = {
    node: option(fragment_comments_edges_node),
  };
  type fragment_comments = {
    edges: option(array(option(fragment_comments_edges))),
  };

  type fragment = {
    id: string,
    title: string,
    body: string,
    state: [ | `CLOSED | `MERGED | `OPEN | `FutureAddedValue(string)],
    number: int,
    url: string,
    comments: fragment_comments,
  };
};

module Internal = {
  type fragmentRaw;
  let fragmentConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"state":{"e":"enum_GitHubPullRequestState"},"comments_edges":{"n":"","na":""},"comments_edges_node":{"n":"","f":""}}} |json}
  ];
  let fragmentConverterMap = {
    "enum_GitHubPullRequestState": unwrap_enum_GitHubPullRequestState,
  };
  let convertFragment = v =>
    v
    ->ReasonRelay._convertObj(
        fragmentConverter,
        fragmentConverterMap,
        Js.undefined,
      );
};

type t;
type fragmentRef;
type fragmentRefSelector('a) =
  {.. "__$fragment_ref__PullRequestChatHistory_PullRequestFragment": t} as 'a;
external getFragmentRef: fragmentRefSelector('a) => fragmentRef = "%identity";

module Utils = {
  open Types;
  let getConnectionNodes_comments:
    fragment_comments => array(fragment_comments_edges_node) =
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

type operationType = ReasonRelay.fragmentNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "id",
  "args": null,
  "storageKey": null
};
return {
  "kind": "Fragment",
  "name": "PullRequestChatHistory_PullRequestFragment",
  "type": "GitHubPullRequest",
  "metadata": {
    "connection": [
      {
        "count": null,
        "cursor": null,
        "direction": "backward",
        "path": [
          "comments"
        ]
      }
    ]
  },
  "argumentDefinitions": [],
  "selections": [
    (v0/*: any*/),
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
      "alias": "comments",
      "name": "__PullRequestChatHistory_PullRequestFragment_comments_connection",
      "storageKey": null,
      "args": null,
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
                (v0/*: any*/),
                {
                  "kind": "ScalarField",
                  "alias": null,
                  "name": "__typename",
                  "args": null,
                  "storageKey": null
                },
                {
                  "kind": "FragmentSpread",
                  "name": "PullRequestChatHistory_CommentFragment",
                  "args": null
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
      ]
    }
  ]
};
})() |json}
];
