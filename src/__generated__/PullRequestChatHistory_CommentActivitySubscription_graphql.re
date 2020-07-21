/* @generated */

type enum_GitHubIssueCommentEventSubscriptionActionEnum = [
  | `CREATED
  | `DELETED
  | `EDITED
  | `FutureAddedValue(string)
];

let unwrap_enum_GitHubIssueCommentEventSubscriptionActionEnum:
  string => enum_GitHubIssueCommentEventSubscriptionActionEnum =
  fun
  | "CREATED" => `CREATED
  | "DELETED" => `DELETED
  | "EDITED" => `EDITED
  | v => `FutureAddedValue(v);

let wrap_enum_GitHubIssueCommentEventSubscriptionActionEnum:
  enum_GitHubIssueCommentEventSubscriptionActionEnum => string =
  fun
  | `CREATED => "CREATED"
  | `DELETED => "DELETED"
  | `EDITED => "EDITED"
  | `FutureAddedValue(v) => v;

module Types = {
  type response_github_issueCommentEvent_comment = {
    id: string,
    getFragmentRefs:
      unit =>
      {
        .
        "__$fragment_ref__PullRequestChatHistory_CommentFragment": PullRequestChatHistory_CommentFragment_graphql.t,
      },
  };
  type response_github_issueCommentEvent = {
    action:
      option([ | `CREATED | `DELETED | `EDITED | `FutureAddedValue(string)]),
    comment: option(response_github_issueCommentEvent_comment),
  };
  type response_github = {
    issueCommentEvent: response_github_issueCommentEvent,
  };

  type response = {github: response_github};
  type variables = {
    repoName: string,
    repoOwner: string,
  };
};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"github_issueCommentEvent_action":{"n":"","e":"enum_GitHubIssueCommentEventSubscriptionActionEnum"},"github_issueCommentEvent_comment":{"n":"","f":""}}} |json}
  ];
  let responseConverterMap = {
    "enum_GitHubIssueCommentEventSubscriptionActionEnum": unwrap_enum_GitHubIssueCommentEventSubscriptionActionEnum,
  };
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
  let makeVariables = (~repoName, ~repoOwner): variables => {
    repoName,
    repoOwner,
  };
};

type operationType = ReasonRelay.subscriptionNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "repoName",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "repoOwner",
    "type": "String!",
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
        "name": "repoName",
        "variableName": "repoName"
      },
      {
        "kind": "Variable",
        "name": "repoOwner",
        "variableName": "repoOwner"
      }
    ]
  }
],
v2 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "action",
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
    "name": "PullRequestChatHistory_CommentActivitySubscription",
    "type": "Subscription",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "github",
        "storageKey": null,
        "args": null,
        "concreteType": "GithubSubscriptionRoot",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "issueCommentEvent",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubIssueCommentEventSubscriptionPayload",
            "plural": false,
            "selections": [
              (v2/*: any*/),
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "comment",
                "storageKey": null,
                "args": null,
                "concreteType": "GitHubIssueComment",
                "plural": false,
                "selections": [
                  (v3/*: any*/),
                  {
                    "kind": "FragmentSpread",
                    "name": "PullRequestChatHistory_CommentFragment",
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
    "name": "PullRequestChatHistory_CommentActivitySubscription",
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "github",
        "storageKey": null,
        "args": null,
        "concreteType": "GithubSubscriptionRoot",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "issueCommentEvent",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubIssueCommentEventSubscriptionPayload",
            "plural": false,
            "selections": [
              (v2/*: any*/),
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "comment",
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
  },
  "params": {
    "operationKind": "subscription",
    "name": "PullRequestChatHistory_CommentActivitySubscription",
    "id": null,
    "text": "subscription PullRequestChatHistory_CommentActivitySubscription(\n  $repoName: String!\n  $repoOwner: String!\n) {\n  github {\n    issueCommentEvent(input: {repoOwner: $repoOwner, repoName: $repoName}) {\n      action\n      comment {\n        id\n        ...PullRequestChatHistory_CommentFragment\n      }\n    }\n  }\n}\n\nfragment PullRequestChatHistory_CommentFragment on GitHubComment {\n  id\n  author {\n    __typename\n    login\n    avatarUrl\n  }\n  createdAt\n  body\n}\n",
    "metadata": {}
  }
};
})() |json}
];
