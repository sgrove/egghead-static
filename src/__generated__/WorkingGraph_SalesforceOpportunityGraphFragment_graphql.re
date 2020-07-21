/* @generated */

module Types = {
  type fragment_t = {
    id: string,
    isClosed: bool,
    isWon: bool,
    name: string,
    stageName: string,
    amount: option(float),
    probability: option(float),
  };
  type fragment = array(fragment_t);
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
  array(
    {.. "__$fragment_ref__WorkingGraph_SalesforceOpportunityGraphFragment": t} as 'a,
  );
external getFragmentRef: fragmentRefSelector('a) => fragmentRef = "%identity";

module Utils = {};

type operationType = ReasonRelay.fragmentNode;

let node: operationType = [%raw
  {json| {
  "kind": "Fragment",
  "name": "WorkingGraph_SalesforceOpportunityGraphFragment",
  "type": "SalesforceOpportunity",
  "metadata": {
    "plural": true
  },
  "argumentDefinitions": [],
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
      "name": "probability",
      "args": null,
      "storageKey": null
    }
  ]
} |json}
];
