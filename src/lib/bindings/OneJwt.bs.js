// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");

function payload(jwt) {
  var pieces = jwt.split(".");
  var payload$1 = Caml_array.caml_array_get(pieces, 1);
  return JSON.parse(atob(payload$1));
}

function findGitHubLogin($$default, jwt) {
  var __x = jwt.user;
  var __x$1 = Belt_Option.flatMap(__x === undefined ? undefined : Caml_option.some(__x), (function (user) {
          return Caml_option.undefined_to_opt(user.gitHubLogin);
        }));
  return Belt_Option.getWithDefault(__x$1, $$default);
}

exports.payload = payload;
exports.findGitHubLogin = findGitHubLogin;
/* No side effect */