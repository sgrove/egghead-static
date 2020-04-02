/* @generated */

module Unions = {};

module Types = {
  type user = {
    getFragmentRefs:
      unit =>
      {
        .
        "__$fragment_ref__RelayComponentTest_GitHubUser": RelayComponentTest_GitHubUser_graphql.t,
      },
  };
  type licenses = {
    body: string,
    name: string,
  };
  type gitHub = {
    licenses: array(option(licenses)),
    user: option(user),
  };
};

open Types;

type response = {gitHub: option(gitHub)};
type refetchVariables = {login: option(string)};
let makeRefetchVariables = (~login=?, ()): refetchVariables => {
  login: login,
};
type variables = {login: string};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {| {"__root":{"gitHub":{"n":""},"gitHub_licenses":{"na":""},"gitHub_user":{"n":"","f":""}}} |}
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

type operationType = ReasonRelay.queryNode;

let node: operationType = [%bs.raw
  {| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "login",
    "type": "String!",
    "defaultValue": null
  }
],
v1 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "body",
  "args": null,
  "storageKey": null
},
v2 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "name",
  "args": null,
  "storageKey": null
},
v3 = [
  {
    "kind": "Variable",
    "name": "login",
    "variableName": "login"
  }
],
v4 = {
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
    "name": "RelayComponentTest_GitHubUserQuery",
    "type": "Query",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "gitHub",
        "storageKey": null,
        "args": null,
        "concreteType": "GitHubQuery",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "licenses",
            "storageKey": null,
            "args": null,
            "concreteType": "GitHubLicense",
            "plural": true,
            "selections": [
              (v1/*: any*/),
              (v2/*: any*/)
            ]
          },
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "user",
            "storageKey": null,
            "args": (v3/*: any*/),
            "concreteType": "GitHubUser",
            "plural": false,
            "selections": [
              {
                "kind": "FragmentSpread",
                "name": "RelayComponentTest_GitHubUser",
                "args": null
              }
            ]
          }
        ]
      }
    ]
  },
  "operation": {
    "kind": "Operation",
    "name": "RelayComponentTest_GitHubUserQuery",
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "gitHub",
        "storageKey": null,
        "args": null,
        "concreteType": "GitHubQuery",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "licenses",
            "storageKey": null,
            "args": null,
            "concreteType": "GitHubLicense",
            "plural": true,
            "selections": [
              (v1/*: any*/),
              (v2/*: any*/),
              (v4/*: any*/)
            ]
          },
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "user",
            "storageKey": null,
            "args": (v3/*: any*/),
            "concreteType": "GitHubUser",
            "plural": false,
            "selections": [
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "bio",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "avatarUrl",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "isHireable",
                "args": null,
                "storageKey": null
              },
              (v2/*: any*/),
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "login",
                "args": null,
                "storageKey": null
              },
              (v4/*: any*/)
            ]
          }
        ]
      }
    ]
  },
  "params": {
    "operationKind": "query",
    "name": "RelayComponentTest_GitHubUserQuery",
    "id": null,
    "text": "query RelayComponentTest_GitHubUserQuery(\n  $login: String!\n) {\n  gitHub {\n    licenses {\n      body\n      name\n      id\n    }\n    user(login: $login) {\n      ...RelayComponentTest_GitHubUser\n      id\n    }\n  }\n}\n\nfragment RelayComponentTest_GitHubUser on GitHubUser {\n  bio\n  avatarUrl\n  isHireable\n  name\n  login\n}\n",
    "metadata": {}
  }
};
})() |}
];
