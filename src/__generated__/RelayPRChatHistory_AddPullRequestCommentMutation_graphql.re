/* @generated */

module Unions = {};

module Types = {
  type node = {
    id: string,
    getFragmentRefs:
      unit =>
      {
        .
        "__$fragment_ref__RelayPRChatHistory_CommentFragment": RelayPRChatHistory_CommentFragment_graphql.t,
      },
  };
  type commentEdge = {node: option(node)};
  type addComment = {
    clientMutationId: option(string),
    commentEdge: option(commentEdge),
  };
  type gitHub = {addComment: option(addComment)};
};

open Types;

type response = {gitHub: option(gitHub)};
type variables = {
  body: string,
  commentableId: string,
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"gitHub":{"n":""},"gitHub_addComment":{"n":""},"gitHub_addComment_clientMutationId":{"n":""},"gitHub_addComment_commentEdge":{"n":""},"gitHub_addComment_commentEdge_node":{"n":"","f":""}}} |}
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
    {| {"__root":{"gitHub":{"n":""},"gitHub_addComment":{"n":""},"gitHub_addComment_clientMutationId":{"n":""},"gitHub_addComment_commentEdge":{"n":""},"gitHub_addComment_commentEdge_node":{"n":"","f":""}}} |}
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

module Utils = {};

type operationType = ReasonRelay.mutationNode;

let node: operationType = [%bs.raw
  {| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "body",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "commentableId",
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
        "name": "body",
        "variableName": "body"
      },
      {
        "kind": "Variable",
        "name": "subjectId",
        "variableName": "commentableId"
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
  "name": "id",
  "args": null,
  "storageKey": null
};
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "RelayPRChatHistory_AddPullRequestCommentMutation",
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
            "name": "addComment",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubAddCommentPayload",
            "plural": false,
            "selections": [
              (v2/*: any*/),
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "commentEdge",
                "storageKey": null,
                "args": null,
                "concreteType": "GitHubIssueCommentEdge",
                "plural": false,
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
                      (v3/*: any*/),
                      {
                        "kind": "FragmentSpread",
                        "name": "RelayPRChatHistory_CommentFragment",
                        "args": null
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
    "name": "RelayPRChatHistory_AddPullRequestCommentMutation",
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
            "name": "addComment",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubAddCommentPayload",
            "plural": false,
            "selections": [
              (v2/*: any*/),
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "commentEdge",
                "storageKey": null,
                "args": null,
                "concreteType": "GitHubIssueCommentEdge",
                "plural": false,
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
                      (v3/*: any*/),
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
                      {
                        "kind": "ScalarField",
                        "alias": null,
                        "name": "body",
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
  },
  "params": {
    "operationKind": "mutation",
    "name": "RelayPRChatHistory_AddPullRequestCommentMutation",
    "id": null,
    "text": "mutation RelayPRChatHistory_AddPullRequestCommentMutation(\n  $body: String!\n  $commentableId: ID!\n) {\n  gitHub {\n    addComment(input: {body: $body, subjectId: $commentableId}) {\n      clientMutationId\n      commentEdge {\n        node {\n          id\n          ...RelayPRChatHistory_CommentFragment\n        }\n      }\n    }\n  }\n}\n\nfragment RelayPRChatHistory_CommentFragment on GitHubComment {\n  id\n  author {\n    __typename\n    login\n    avatarUrl\n  }\n  createdAt\n  body\n}\n",
    "metadata": {}
  }
};
})() |}
];
