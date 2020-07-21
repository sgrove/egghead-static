/* @generated */

module Types = {
  type fragment = {
    isClosed: bool,
    isWon: bool,
    name: string,
    stageName: string,
    amount: option(float),
    id: string,
    probability: option(float),
  };
};

module Internal = {
  type fragmentRaw;
  let fragmentConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"amount":{"n":""},"probability":{"n":""}}} |json}
  ];
  let fragmentConverterMap = ();
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
  {.. "__$fragment_ref__WorkingGraph_SalesforceOpportunityFragment": t} as 'a;
external getFragmentRef: fragmentRefSelector('a) => fragmentRef = "%identity";

module Utils = {};

type operationType = ReasonRelay.fragmentNode;

let node: operationType = [%raw
  {json| {
  "kind": "Fragment",
  "name": "WorkingGraph_SalesforceOpportunityFragment",
  "type": "SalesforceOpportunity",
  "metadata": null,
  "argumentDefinitions": [],
  "selections": [
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "isClosed",
      "args": null,
      "storageKey": null
    },
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "isWon",
      "args": null,
      "storageKey": null
    },
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "name",
      "args": null,
      "storageKey": null
    },
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "stageName",
      "args": null,
      "storageKey": null
    },
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "amount",
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
      "name": "probability",
      "args": null,
      "storageKey": null
    }
  ]
} |json}
];
