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
  type fragment = {
    body: string,
    id: string,
    number: int,
    permalink: string,
    state: [ | `CLOSED | `MERGED | `OPEN | `FutureAddedValue(string)],
    title: string,
    url: string,
  };
};

module Internal = {
  type fragmentRaw;
  let fragmentConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"state":{"e":"enum_GitHubPullRequestState"}}} |json}
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
  {.. "__$fragment_ref__CourseTree_GitHubPullRequest": t} as 'a;
external getFragmentRef: fragmentRefSelector('a) => fragmentRef = "%identity";

module Utils = {};

type operationType = ReasonRelay.fragmentNode;

let node: operationType = [%raw
  {json| {
  "kind": "Fragment",
  "name": "CourseTree_GitHubPullRequest",
  "type": "GitHubPullRequest",
  "metadata": null,
  "argumentDefinitions": [],
  "selections": [
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
      "name": "permalink",
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
      "name": "title",
      "args": null,
      "storageKey": null
    },
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "url",
      "args": null,
      "storageKey": null
    }
  ]
} |json}
];
