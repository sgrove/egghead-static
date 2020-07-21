/* @generated */

module Types = {
  type response_salesforce_opportunities_edges_node = {
    id: string,
    getFragmentRefs:
      unit =>
      {
        .
        "__$fragment_ref__WorkingGraph_SalesforceOpportunityGraphFragment": WorkingGraph_SalesforceOpportunityGraphFragment_graphql.t,
        "__$fragment_ref__WorkingGraph_SalesforceOpportunityFragment": WorkingGraph_SalesforceOpportunityFragment_graphql.t,
      },
  };
  type response_salesforce_opportunities_edges = {
    node: response_salesforce_opportunities_edges_node,
  };
  type response_salesforce_opportunities = {
    edges: array(response_salesforce_opportunities_edges),
  };
  type response_salesforce = {
    opportunities: option(response_salesforce_opportunities),
  };

  type response = {salesforce: response_salesforce};
  type variables = unit;
};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"salesforce_opportunities":{"n":""},"salesforce_opportunities_edges_node":{"f":""}}} |json}
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

type preloadToken;

module Utils = {
  open Types;
  let getConnectionNodes_opportunities:
    option(response_salesforce_opportunities) =>
    array(response_salesforce_opportunities_edges_node) =
    connection =>
      switch (connection) {
      | None => [||]
      | Some(connection) =>
        connection.edges->Belt.Array.keepMap(edge => Some(edge.node))
      };
};

type operationType = ReasonRelay.queryNode;

let node: operationType = [%raw
  {json| (function(){
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
  "name": "__typename",
  "args": null,
  "storageKey": null
},
v2 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "cursor",
  "args": null,
  "storageKey": null
},
v3 = {
  "kind": "LinkedField",
  "alias": null,
  "name": "pageInfo",
  "storageKey": null,
  "args": null,
  "concreteType": "PageInfo",
  "plural": false,
  "selections": [
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "endCursor",
      "args": null,
      "storageKey": null
    },
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "hasNextPage",
      "args": null,
      "storageKey": null
    }
  ]
},
v4 = [
  {
    "kind": "Literal",
    "name": "first",
    "value": 50
  }
];
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "WorkingGraph_OpportunityQuery",
    "type": "Query",
    "metadata": null,
    "argumentDefinitions": [],
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "salesforce",
        "storageKey": null,
        "args": null,
        "concreteType": "SalesforceQuery",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": "opportunities",
            "name": "__WorkingGraph_OpportunityQuery_opportunities_connection",
            "storageKey": null,
            "args": null,
            "concreteType": "SalesforceOpportunitysConnection",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "edges",
                "storageKey": null,
                "args": null,
                "concreteType": "SalesforceOpportunityEdge",
                "plural": true,
                "selections": [
                  {
                    "kind": "LinkedField",
                    "alias": null,
                    "name": "node",
                    "storageKey": null,
                    "args": null,
                    "concreteType": "SalesforceOpportunity",
                    "plural": false,
                    "selections": [
                      (v0/*: any*/),
                      (v1/*: any*/),
                      {
                        "kind": "FragmentSpread",
                        "name": "WorkingGraph_SalesforceOpportunityGraphFragment",
                        "args": null
                      },
                      {
                        "kind": "FragmentSpread",
                        "name": "WorkingGraph_SalesforceOpportunityFragment",
                        "args": null
                      }
                    ]
                  },
                  (v2/*: any*/)
                ]
              },
              (v3/*: any*/)
            ]
          }
        ]
      }
    ]
  },
  "operation": {
    "kind": "Operation",
    "name": "WorkingGraph_OpportunityQuery",
    "argumentDefinitions": [],
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "salesforce",
        "storageKey": null,
        "args": null,
        "concreteType": "SalesforceQuery",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "opportunities",
            "storageKey": "opportunities(first:50)",
            "args": (v4/*: any*/),
            "concreteType": "SalesforceOpportunitysConnection",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "edges",
                "storageKey": null,
                "args": null,
                "concreteType": "SalesforceOpportunityEdge",
                "plural": true,
                "selections": [
                  {
                    "kind": "LinkedField",
                    "alias": null,
                    "name": "node",
                    "storageKey": null,
                    "args": null,
                    "concreteType": "SalesforceOpportunity",
                    "plural": false,
                    "selections": [
                      (v0/*: any*/),
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
                      },
                      (v1/*: any*/)
                    ]
                  },
                  (v2/*: any*/)
                ]
              },
              (v3/*: any*/)
            ]
          },
          {
            "kind": "LinkedHandle",
            "alias": null,
            "name": "opportunities",
            "args": (v4/*: any*/),
            "handle": "connection",
            "key": "WorkingGraph_OpportunityQuery_opportunities",
            "filters": null
          }
        ]
      }
    ]
  },
  "params": {
    "operationKind": "query",
    "name": "WorkingGraph_OpportunityQuery",
    "id": null,
    "text": "query WorkingGraph_OpportunityQuery {\n  salesforce {\n    opportunities(first: 50) {\n      edges {\n        node {\n          id\n          ...WorkingGraph_SalesforceOpportunityGraphFragment\n          ...WorkingGraph_SalesforceOpportunityFragment\n          __typename\n        }\n        cursor\n      }\n      pageInfo {\n        endCursor\n        hasNextPage\n      }\n    }\n  }\n}\n\nfragment WorkingGraph_SalesforceOpportunityFragment on SalesforceOpportunity {\n  isClosed\n  isWon\n  name\n  stageName\n  amount\n  id\n  probability\n}\n\nfragment WorkingGraph_SalesforceOpportunityGraphFragment on SalesforceOpportunity {\n  id\n  isClosed\n  isWon\n  name\n  stageName\n  amount\n  probability\n}\n",
    "metadata": {
      "connection": [
        {
          "count": null,
          "cursor": null,
          "direction": "forward",
          "path": [
            "salesforce",
            "opportunities"
          ]
        }
      ]
    }
  }
};
})() |json}
];

include ReasonRelay.MakePreloadQuery({
  type variables = Types.variables;
  type queryPreloadToken = preloadToken;
  let query = node;
  let convertVariables = Internal.convertVariables;
});
