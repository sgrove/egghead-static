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

module Unions = {};

module Types = {
  type author = {
    __typename: string,
    login: string,
    avatarUrl: string,
  };
  type node = {
    id: string,
    author: option(author),
    createdAt: string,
    body: string,
  };
  type edges = {node: option(node)};
  type comments = {edges: option(array(option(edges)))};
};

open Types;

type fragment = {
  id: string,
  title: string,
  body: string,
  state: enum_GitHubPullRequestState,
  number: int,
  comments,
};

module Internal = {
  type fragmentRaw;
  let fragmentConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"state":{"e":"enum_GitHubPullRequestState"},"comments_edges":{"n":"","na":""},"comments_edges_node":{"n":""},"comments_edges_node_author":{"n":""}}} |}
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
  {.. "__$fragment_ref__RelayCourseTree_PullRequestFragment": t} as 'a;
external getFragmentRef: fragmentRefSelector('a) => fragmentRef = "%identity";

module Utils = {};

type operationType = ReasonRelay.fragmentNode;

let node: operationType = [%bs.raw
  {| (function(){
var v0 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "id",
  "args": null,
  "storageKey": null
},
v1 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "body",
  "args": null,
  "storageKey": null
};
return {
  "kind": "Fragment",
  "name": "RelayCourseTree_PullRequestFragment",
  "type": "GitHubPullRequest",
  "metadata": null,
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
    (v1/*: any*/),
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
      "args": [
        {
          "kind": "Literal",
          "name": "last",
          "value": 100
        }
      ],
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
                  "kind": "LinkedField",
                  "alias": null,
                  "name": "author",
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
                (v1/*: any*/)
              ]
            }
          ]
        }
      ]
    }
  ]
};
})() |}
];
