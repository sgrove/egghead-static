// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as ReasonRelay from "reason-relay/src/ReasonRelay.bs.js";

function unwrap(wrapped) {
  var match = wrapped.__typename;
  if (match === "GitHubBlob") {
    return /* `GitHubBlob */[
            -678893856,
            wrapped
          ];
  } else {
    return /* `FutureAddedValue */[
            -31101740,
            wrapped
          ];
  }
}

var Union_response_gitHub_repository_object_ = {
  unwrap: unwrap
};

var Unions = {
  Union_response_gitHub_repository_object_: Union_response_gitHub_repository_object_
};

var Types = { };

function makeRefetchVariables(repoName, repoOwner, branchAndFilePath, param) {
  return {
          repoName: repoName,
          repoOwner: repoOwner,
          branchAndFilePath: branchAndFilePath
        };
}

var responseConverter = ({"__root":{"gitHub":{"n":""},"gitHub_repository":{"n":""},"gitHub_repository_object_":{"n":"","u":"response_gitHub_repository_object_"},"gitHub_repository_object__githubblob_text":{"n":""}}});

var responseConverterMap = {
  response_gitHub_repository_object_: unwrap
};

function convertResponse(v) {
  return ReasonRelay._convertObj(v, responseConverter, responseConverterMap, undefined);
}

var variablesConverter = ({});

function convertVariables(v) {
  return ReasonRelay._convertObj(v, variablesConverter, /* () */0, undefined);
}

var Internal = {
  responseConverter: responseConverter,
  responseConverterMap: responseConverterMap,
  convertResponse: convertResponse,
  variablesConverter: variablesConverter,
  variablesConverterMap: /* () */0,
  convertVariables: convertVariables
};

var Utils = { };

var node = ((function(){
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
  },
  {
    "kind": "LocalArgument",
    "name": "branchAndFilePath",
    "type": "String!",
    "defaultValue": null
  }
],
v1 = [
  {
    "kind": "Variable",
    "name": "name",
    "variableName": "repoName"
  },
  {
    "kind": "Variable",
    "name": "owner",
    "variableName": "repoOwner"
  }
],
v2 = [
  {
    "kind": "Variable",
    "name": "expression",
    "variableName": "branchAndFilePath"
  }
],
v3 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "__typename",
  "args": null,
  "storageKey": null
},
v4 = {
  "kind": "InlineFragment",
  "type": "GitHubBlob",
  "selections": [
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "oid",
      "args": null,
      "storageKey": null
    },
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "text",
      "args": null,
      "storageKey": null
    }
  ]
},
v5 = {
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
    "name": "EggheadLessonTranscript_GetFileShaQuery",
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
            "name": "repository",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubRepository",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": "object_",
                "name": "object",
                "storageKey": null,
                "args": (v2/*: any*/),
                "concreteType": null,
                "plural": false,
                "selections": [
                  (v3/*: any*/),
                  (v4/*: any*/)
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
    "name": "EggheadLessonTranscript_GetFileShaQuery",
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
            "name": "repository",
            "storageKey": null,
            "args": (v1/*: any*/),
            "concreteType": "GitHubRepository",
            "plural": false,
            "selections": [
              {
                "kind": "LinkedField",
                "alias": "object_",
                "name": "object",
                "storageKey": null,
                "args": (v2/*: any*/),
                "concreteType": null,
                "plural": false,
                "selections": [
                  (v3/*: any*/),
                  (v5/*: any*/),
                  (v4/*: any*/)
                ]
              },
              (v5/*: any*/)
            ]
          }
        ]
      }
    ]
  },
  "params": {
    "operationKind": "query",
    "name": "EggheadLessonTranscript_GetFileShaQuery",
    "id": null,
    "text": "query EggheadLessonTranscript_GetFileShaQuery(\n  $repoName: String!\n  $repoOwner: String!\n  $branchAndFilePath: String!\n) {\n  gitHub {\n    repository(name: $repoName, owner: $repoOwner) {\n      object_: object(expression: $branchAndFilePath) {\n        __typename\n        ... on GitHubBlob {\n          oid\n          text\n        }\n        id\n      }\n      id\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})());

export {
  Unions ,
  Types ,
  makeRefetchVariables ,
  Internal ,
  Utils ,
  node ,
  
}
/* responseConverter Not a pure module */
