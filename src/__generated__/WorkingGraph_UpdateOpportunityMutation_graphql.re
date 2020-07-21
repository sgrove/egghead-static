/* @generated */

module Types = {
  type response_salesforce_updateOpportunity_opportunity = ReasonRelay.allFieldsMasked;
  type response_salesforce_updateOpportunity = {
    opportunity: response_salesforce_updateOpportunity_opportunity,
  };
  type response_salesforce = {
    updateOpportunity: response_salesforce_updateOpportunity,
  };

  type response = {salesforce: response_salesforce};
  type variables = {
    id: string,
    stageName: string,
    amount: float,
  };
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"salesforce_updateOpportunity_opportunity":{"f":""}}} |json}
  ];
  let wrapResponseConverterMap = ();
  let convertWrapResponse = v =>
    v
    ->ReasonRelay._convertObj(
        wrapResponseConverter,
        wrapResponseConverterMap,
        Js.null,
      );

  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"salesforce_updateOpportunity_opportunity":{"f":""}}} |json}
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

module Utils = {
  open Types;
  let makeVariables = (~id, ~stageName, ~amount): variables => {
    id,
    stageName,
    amount,
  };

  let make_response_salesforce_updateOpportunity_opportunity = () =>
    [@ocaml.warning "-27"] {};

  let make_response_salesforce_updateOpportunity =
      (~opportunity): response_salesforce_updateOpportunity => {
    opportunity: opportunity,
  };

  let make_response_salesforce = (~updateOpportunity): response_salesforce => {
    updateOpportunity: updateOpportunity,
  };

  let makeOptimisticResponse = (~salesforce): response => {
    salesforce: salesforce,
  };
};

type operationType = ReasonRelay.mutationNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "id",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "stageName",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "amount",
    "type": "Float!",
    "defaultValue": null
  }
],
v1 = [
  {
    "kind": "ObjectValue",
    "name": "input",
    "fields": [
      {
        "kind": "Variable",
        "name": "id",
        "variableName": "id"
      },
      {
        "kind": "ObjectValue",
        "name": "patch",
        "fields": [
          {
            "kind": "Variable",
            "name": "amount",
            "variableName": "amount"
          },
          {
            "kind": "Variable",
            "name": "stageName",
            "variableName": "stageName"
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
    "name": "WorkingGraph_UpdateOpportunityMutation",
    "type": "Mutation",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "salesforce",
        "storageKey": null,
        "args": null,
        "concreteType": "SalesforceMutation",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "updateOpportunity",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "SalesforceUpdateOpportunityPayload",
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
                    "kind": "FragmentSpread",
                    "name": "WorkingGraph_SalesforceOpportunityFragment",
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
    "name": "WorkingGraph_UpdateOpportunityMutation",
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "salesforce",
        "storageKey": null,
        "args": null,
        "concreteType": "SalesforceMutation",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "updateOpportunity",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "SalesforceUpdateOpportunityPayload",
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
    ]
  },
  "params": {
    "operationKind": "mutation",
    "name": "WorkingGraph_UpdateOpportunityMutation",
    "id": null,
    "text": "mutation WorkingGraph_UpdateOpportunityMutation(\n  $id: String!\n  $stageName: String!\n  $amount: Float!\n) {\n  salesforce {\n    updateOpportunity(input: {patch: {stageName: $stageName, amount: $amount}, id: $id}) {\n      opportunity {\n        ...WorkingGraph_SalesforceOpportunityFragment\n      }\n    }\n  }\n}\n\nfragment WorkingGraph_SalesforceOpportunityFragment on SalesforceOpportunity {\n  isClosed\n  isWon\n  name\n  stageName\n  amount\n  id\n  probability\n}\n",
    "metadata": {}
  }
};
})() |json}
];
