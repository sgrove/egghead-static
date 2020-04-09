/* @generated */

module Types = {
  type response_gitHub_addLabelsToLabelable_labelable_labels_nodes = {
    name: string,
  };
  type response_gitHub_addLabelsToLabelable_labelable_labels = {
    nodes:
      option(
        array(
          option(response_gitHub_addLabelsToLabelable_labelable_labels_nodes),
        ),
      ),
  };
  type response_gitHub_addLabelsToLabelable_labelable = {
    __typename: string,
    labels: option(response_gitHub_addLabelsToLabelable_labelable_labels),
  };
  type response_gitHub_addLabelsToLabelable = {
    clientMutationId: option(string),
    labelable: option(response_gitHub_addLabelsToLabelable_labelable),
  };
  type response_gitHub = {
    addLabelsToLabelable: option(response_gitHub_addLabelsToLabelable),
  };

  type response = {gitHub: option(response_gitHub)};
  type variables = {
    labelIds: array(string),
    labelableId: string,
  };
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"gitHub":{"n":""},"gitHub_addLabelsToLabelable":{"n":""},"gitHub_addLabelsToLabelable_clientMutationId":{"n":""},"gitHub_addLabelsToLabelable_labelable":{"n":""},"gitHub_addLabelsToLabelable_labelable_labels":{"n":""},"gitHub_addLabelsToLabelable_labelable_labels_nodes":{"n":"","na":""}}} |}
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
    {| {"__root":{"gitHub":{"n":""},"gitHub_addLabelsToLabelable":{"n":""},"gitHub_addLabelsToLabelable_clientMutationId":{"n":""},"gitHub_addLabelsToLabelable_labelable":{"n":""},"gitHub_addLabelsToLabelable_labelable_labels":{"n":""},"gitHub_addLabelsToLabelable_labelable_labels_nodes":{"n":"","na":""}}} |}
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

module Utils = {
  open Types;
  let makeVariables = (~labelIds, ~labelableId): variables => {
    labelIds,
    labelableId,
  };

  let make_response_gitHub_addLabelsToLabelable_labelable_labels_nodes =
      (~name): response_gitHub_addLabelsToLabelable_labelable_labels_nodes => {
    name: name,
  };

  let make_response_gitHub_addLabelsToLabelable_labelable_labels =
      (~nodes=?, ()): response_gitHub_addLabelsToLabelable_labelable_labels => {
    nodes: nodes,
  };

  let make_response_gitHub_addLabelsToLabelable_labelable =
      (~__typename, ~labels=?, ())
      : response_gitHub_addLabelsToLabelable_labelable => {
    __typename,
    labels,
  };

  let make_response_gitHub_addLabelsToLabelable =
      (~clientMutationId=?, ~labelable=?, ())
      : response_gitHub_addLabelsToLabelable => {
    clientMutationId,
    labelable,
  };

  let make_response_gitHub = (~addLabelsToLabelable=?, ()): response_gitHub => {
    addLabelsToLabelable: addLabelsToLabelable,
  };

  let makeOptimisticResponse = (~gitHub=?, ()): response => {gitHub: gitHub};
};

type operationType = ReasonRelay.mutationNode;

let node: operationType = [%bs.raw
  {| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "labelIds",
    "type": "[ID!]!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "labelableId",
    "type": "ID!",
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
        "name": "labelIds",
        "variableName": "labelIds"
      },
      {
        "kind": "Variable",
        "name": "labelableId",
        "variableName": "labelableId"
      }
    ]
  }
],
v2 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "clientMutationId",
  "args": null,
  "storageKey": null
},
v3 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "__typename",
  "args": null,
  "storageKey": null
},
v4 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "name",
  "args": null,
  "storageKey": null
};
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "RelaySubmitLessonPullRequest_AddLabelToPullRequestMutation",
    "type": "Mutation",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "gitHub",
        "storageKey": null,
        "args": null,
        "concreteType": "GitHubMutation",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "addLabelsToLabelable",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubAddLabelsToLabelablePayload",
            "plural": false,
            "selections": [
              (v2/*: any*/),
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "labelable",
                "storageKey": null,
                "args": null,
                "concreteType": null,
                "plural": false,
                "selections": [
                  (v3/*: any*/),
                  {
                    "kind": "LinkedField",
                    "alias": null,
                    "name": "labels",
                    "storageKey": null,
                    "args": null,
                    "concreteType": "GitHubLabelConnection",
                    "plural": false,
                    "selections": [
                      {
                        "kind": "LinkedField",
                        "alias": null,
                        "name": "nodes",
                        "storageKey": null,
                        "args": null,
                        "concreteType": "GitHubLabel",
                        "plural": true,
                        "selections": [
                          (v4/*: any*/)
                        ]
                      }
                    ]
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
    "name": "RelaySubmitLessonPullRequest_AddLabelToPullRequestMutation",
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "gitHub",
        "storageKey": null,
        "args": null,
        "concreteType": "GitHubMutation",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "addLabelsToLabelable",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubAddLabelsToLabelablePayload",
            "plural": false,
            "selections": [
              (v2/*: any*/),
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "labelable",
                "storageKey": null,
                "args": null,
                "concreteType": null,
                "plural": false,
                "selections": [
                  (v3/*: any*/),
                  {
                    "kind": "LinkedField",
                    "alias": null,
                    "name": "labels",
                    "storageKey": null,
                    "args": null,
                    "concreteType": "GitHubLabelConnection",
                    "plural": false,
                    "selections": [
                      {
                        "kind": "LinkedField",
                        "alias": null,
                        "name": "nodes",
                        "storageKey": null,
                        "args": null,
                        "concreteType": "GitHubLabel",
                        "plural": true,
                        "selections": [
                          (v4/*: any*/),
                          {
                            "kind": "ScalarField",
                            "alias": null,
                            "name": "id",
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
          }
        ]
      }
    ]
  },
  "params": {
    "operationKind": "mutation",
    "name": "RelaySubmitLessonPullRequest_AddLabelToPullRequestMutation",
    "id": null,
    "text": "mutation RelaySubmitLessonPullRequest_AddLabelToPullRequestMutation(\n  $labelIds: [ID!]!\n  $labelableId: ID!\n) {\n  gitHub {\n    addLabelsToLabelable(input: {labelIds: $labelIds, labelableId: $labelableId}) {\n      clientMutationId\n      labelable {\n        __typename\n        labels {\n          nodes {\n            name\n            id\n          }\n        }\n      }\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
