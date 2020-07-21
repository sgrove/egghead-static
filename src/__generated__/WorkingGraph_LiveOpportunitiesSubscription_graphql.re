/* @generated */

module Types = {
  type response_salesforce_opportunityUpdated_opportunity = {
    isClosed: bool,
    isWon: bool,
    name: string,
    stageName: string,
    amount: option(float),
    id: string,
    probability: option(float),
  };
  type response_salesforce_opportunityUpdated = {
    opportunity: response_salesforce_opportunityUpdated_opportunity,
  };
  type response_salesforce = {
    opportunityUpdated: response_salesforce_opportunityUpdated,
  };

  type response = {salesforce: response_salesforce};
  type variables = unit;
};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"salesforce_opportunityUpdated_opportunity_amount":{"n":""},"salesforce_opportunityUpdated_opportunity_probability":{"n":""}}} |json}
  ];
  let responseConverterMap = ();
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

module Utils = {};

type operationType = ReasonRelay.subscriptionNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "kind": "LinkedField",
    "alias": null,
    "name": "salesforce",
    "storageKey": null,
    "args": null,
    "concreteType": "SalesforceSubscriptionRoot",
    "plural": false,
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "opportunityUpdated",
        "storageKey": null,
        "args": null,
        "concreteType": "SalesforceOpportunityUpdatedSubscriptionPayload",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "opportunity",
            "storageKey": null,
            "args": null,
            "concreteType": "SalesforceOpportunity",
            "plural": false,
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
          }
        ]
      }
    ]
  }
];
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "WorkingGraph_LiveOpportunitiesSubscription",
    "type": "Subscription",
    "metadata": null,
    "argumentDefinitions": [],
    "selections": (v0/*: any*/)
  },
  "operation": {
    "kind": "Operation",
    "name": "WorkingGraph_LiveOpportunitiesSubscription",
    "argumentDefinitions": [],
    "selections": (v0/*: any*/)
  },
  "params": {
    "operationKind": "subscription",
    "name": "WorkingGraph_LiveOpportunitiesSubscription",
    "id": null,
    "text": "subscription WorkingGraph_LiveOpportunitiesSubscription {\n  salesforce {\n    opportunityUpdated {\n      opportunity {\n        isClosed\n        isWon\n        name\n        stageName\n        amount\n        id\n        probability\n      }\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |json}
];
