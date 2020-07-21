/* @generated */

module Types = {
  type response_salesforce_opportunityUpdated_opportunity = {
    amount: option(float),
    id: string,
    isClosed: bool,
    isWon: bool,
    name: string,
    probability: option(float),
    stageName: string,
    getFragmentRefs:
      unit =>
      {
        .
        "__$fragment_ref__SFDCQuickly_SalesforceOpportunityGraphFragment": SFDCQuickly_SalesforceOpportunityGraphFragment_graphql.t,
      },
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
    {json| {"__root":{"salesforce_opportunityUpdated_opportunity_amount":{"n":""},"salesforce_opportunityUpdated_opportunity_probability":{"n":""},"salesforce_opportunityUpdated_opportunity":{"f":""}}} |json}
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
var v0 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "amount",
  "args": null,
  "storageKey": null
},
v1 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "id",
  "args": null,
  "storageKey": null
},
v2 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "isClosed",
  "args": null,
  "storageKey": null
},
v3 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "isWon",
  "args": null,
  "storageKey": null
},
v4 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "name",
  "args": null,
  "storageKey": null
},
v5 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "probability",
  "args": null,
  "storageKey": null
},
v6 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "stageName",
  "args": null,
  "storageKey": null
};
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "SFDCQuickly_LiveOpptysSubscription",
    "type": "Subscription",
    "metadata": null,
    "argumentDefinitions": [],
    "selections": [
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
                  (v0/*: any*/),
                  (v1/*: any*/),
                  (v2/*: any*/),
                  (v3/*: any*/),
                  (v4/*: any*/),
                  (v5/*: any*/),
                  (v6/*: any*/),
                  {
                    "kind": "FragmentSpread",
                    "name": "SFDCQuickly_SalesforceOpportunityGraphFragment",
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
    "name": "SFDCQuickly_LiveOpptysSubscription",
    "argumentDefinitions": [],
    "selections": [
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
                  (v0/*: any*/),
                  (v1/*: any*/),
                  (v2/*: any*/),
                  (v3/*: any*/),
                  (v4/*: any*/),
                  (v5/*: any*/),
                  (v6/*: any*/)
                ]
              }
            ]
          }
        ]
      }
    ]
  },
  "params": {
    "operationKind": "subscription",
    "name": "SFDCQuickly_LiveOpptysSubscription",
    "id": null,
    "text": "subscription SFDCQuickly_LiveOpptysSubscription {\n  salesforce {\n    opportunityUpdated {\n      opportunity {\n        amount\n        id\n        isClosed\n        isWon\n        name\n        probability\n        stageName\n        ...SFDCQuickly_SalesforceOpportunityGraphFragment\n      }\n    }\n  }\n}\n\nfragment SFDCQuickly_SalesforceOpportunityGraphFragment on SalesforceOpportunity {\n  amount\n  id\n  isClosed\n  isWon\n  name\n  probability\n  stageName\n}\n",
    "metadata": {}
  }
};
})() |json}
];
