/* @generated */

module Types = {
  type response_gitHub_createFork_oneGraph_repository = {
    nameWithOwner: string,
  };
  type response_gitHub_createFork_oneGraph = {
    repository: response_gitHub_createFork_oneGraph_repository,
  };
  type response_gitHub = {
    createFork_oneGraph: response_gitHub_createFork_oneGraph,
  };

  type response = {gitHub: option(response_gitHub)};
  type variables = {
    repoOwner: string,
    repoName: string,
  };
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"gitHub":{"n":""}}} |}
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
    {| {"__root":{"gitHub":{"n":""}}} |}
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
  let makeVariables = (~repoOwner, ~repoName): variables => {
    repoOwner,
    repoName,
  };

  let make_response_gitHub_createFork_oneGraph_repository =
      (~nameWithOwner): response_gitHub_createFork_oneGraph_repository => {
    nameWithOwner: nameWithOwner,
  };

  let make_response_gitHub_createFork_oneGraph =
      (~repository): response_gitHub_createFork_oneGraph => {
    repository: repository,
  };

  let make_response_gitHub = (~createFork_oneGraph): response_gitHub => {
    createFork_oneGraph: createFork_oneGraph,
  };

  let makeOptimisticResponse = (~gitHub=?, ()): response => {gitHub: gitHub};
};

type operationType = ReasonRelay.mutationNode;

let node: operationType = [%bs.raw
  {| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "repoOwner",
    "type": "String!",
    "defaultValue": null
  },
  {
    "kind": "LocalArgument",
    "name": "repoName",
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
  "name": "nameWithOwner",
  "args": null,
  "storageKey": null
};
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "RelaySubmitLessonPullRequest_ForkGitHubRepoMutation",
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
            "name": "createFork_oneGraph",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubCreateFork_oneGraphResponsePayload",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "repository",
                "storageKey": null,
                "args": null,
                "concreteType": "GitHubRepository",
                "plural": false,
                "selections": [
                  (v2/*: any*/)
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
    "name": "RelaySubmitLessonPullRequest_ForkGitHubRepoMutation",
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
            "name": "createFork_oneGraph",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubCreateFork_oneGraphResponsePayload",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": null,
                "name": "repository",
                "storageKey": null,
                "args": null,
                "concreteType": "GitHubRepository",
                "plural": false,
                "selections": [
                  (v2/*: any*/),
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
  },
  "params": {
    "operationKind": "mutation",
    "name": "RelaySubmitLessonPullRequest_ForkGitHubRepoMutation",
    "id": null,
    "text": "mutation RelaySubmitLessonPullRequest_ForkGitHubRepoMutation(\n  $repoOwner: String!\n  $repoName: String!\n) {\n  gitHub {\n    createFork_oneGraph(input: {repoOwner: $repoOwner, repoName: $repoName}) {\n      repository {\n        nameWithOwner\n        id\n      }\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
