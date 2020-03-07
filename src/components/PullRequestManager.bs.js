// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as List from "bs-platform/lib/es6/list.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as $$Promise from "reason-promise/src/js/promise.js";
import * as Belt_List from "bs-platform/lib/es6/belt_List.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as GraphQL$EggheadStatic from "./GraphQL.bs.js";
import * as Caml_builtin_exceptions from "bs-platform/lib/es6/caml_builtin_exceptions.js";

function prTitle(pr) {
  return "#" + (String(pr.number) + (": " + pr.title));
}

var timeSince = ((date) => {

  var seconds = Math.floor((new Date() - date) / 1000);

  var interval = Math.floor(seconds / 31536000);

  if (interval > 1) {
    return interval + " years";
  }
  interval = Math.floor(seconds / 2592000);
  if (interval > 1) {
    return interval + " months";
  }
  interval = Math.floor(seconds / 86400);
  if (interval > 1) {
    return interval + " days";
  }
  interval = Math.floor(seconds / 3600);
  if (interval > 1) {
    return interval + " hours";
  }
  interval = Math.floor(seconds / 60);
  if (interval > 1) {
    return interval + " minutes";
  }
  return Math.floor(seconds) + " seconds";
});

function submitPrComment(client, message, pullRequestId) {
  return GraphQL$EggheadStatic.chain(/* :: */[
              (function (param) {
                  return GraphQL$EggheadStatic.mutation(client, GraphQL$EggheadStatic.AddPullRequestCommentMutation.make(message, pullRequestId, /* () */0), "Error adding comment to PR");
                }),
              /* [] */0
            ]);
}

function PullRequestManager$MessageCompose(Props) {
  var onSubmit = Props.onSubmit;
  var match = React.useState((function () {
          return false;
        }));
  var setDisabled = match[1];
  var match$1 = React.useState((function () {
          return "";
        }));
  var setText = match$1[1];
  var text = match$1[0];
  var doSubmit = function (param) {
    Curry._1(setDisabled, (function (param) {
            return true;
          }));
    $$Promise.map(Curry._1(onSubmit, text), (function (param) {
            Curry._1(setDisabled, (function (param) {
                    return false;
                  }));
            Curry._1(setText, (function (param) {
                    return "";
                  }));
            return $$Promise.resolved;
          }));
    return /* () */0;
  };
  return React.createElement("div", {
              className: "chat-message clearfix"
            }, React.createElement("textarea", {
                  id: "message-to-send",
                  disabled: match[0],
                  name: "message-to-send",
                  placeholder: "Type your message",
                  rows: 2,
                  value: text,
                  onKeyDown: (function ($$event) {
                      var metaKey = $$event.metaKey;
                      var ctrlKey = $$event.ctrlKey;
                      var enterKey = $$event.which === 13;
                      if ((metaKey || ctrlKey) && enterKey) {
                        return doSubmit(/* () */0);
                      } else {
                        return /* () */0;
                      }
                    }),
                  onChange: (function ($$event) {
                      return Curry._1(setText, $$event.target.value);
                    })
                }), React.createElement("button", {
                  onClick: (function (param) {
                      if (text.trim() === "") {
                        return /* () */0;
                      } else {
                        return doSubmit(/* () */0);
                      }
                    })
                }, "Send"));
}

var MessageCompose = {
  make: PullRequestManager$MessageCompose
};

function PullRequestManager$ChatHistory(Props) {
  var comments = Props.comments;
  var myUsername = Props.myUsername;
  var pr = Props.pr;
  var onSubmit = Props.onSubmit;
  var onRefresh = Props.onRefresh;
  var commentsEl = Belt_List.toArray(Belt_List.map(comments, (function (comment) {
              var author = Belt_Option.map(comment.author, (function (param) {
                      return param[1];
                    }));
              var authorLogin = Belt_Option.mapWithDefault(author, "Unknown", (function (author) {
                      return author.login;
                    }));
              var avatarUrl = Belt_Option.mapWithDefault(author, "", (function (author) {
                      return author.avatarUrl;
                    }));
              var messageIsMe = authorLogin === myUsername;
              var authorEl = React.createElement("span", {
                    className: "message-data-name"
                  }, authorLogin);
              var timeEl = React.createElement("span", {
                    className: "message-data-time"
                  }, timeSince(new Date(comment.createdAt)) + " ago");
              var avatarEl = React.createElement("img", {
                    className: "chat-avatar " + (
                      messageIsMe ? "float-left" : "float-right"
                    ),
                    alt: "avatar",
                    src: avatarUrl
                  });
              console.log("Comment id: ", comment.id);
              return React.createElement("li", {
                          key: comment.id,
                          className: "clearfix"
                        }, React.createElement("div", {
                              className: "message-data clearfix" + (
                                messageIsMe ? "" : " align-right"
                              )
                            }, messageIsMe ? React.createElement(React.Fragment, undefined, avatarEl, authorEl, timeEl) : React.createElement(React.Fragment, undefined, timeEl, authorEl, avatarEl)), React.createElement("div", {
                              className: "message " + (
                                messageIsMe ? " my-message" : " other-message align-right"
                              )
                            }, comment.body));
            })));
  var prTitle$1 = prTitle(pr);
  var commentCount = List.length(comments);
  var commentCountString = String(commentCount) + (" " + (
      commentCount === 1 ? "comment" : "comments"
    ));
  return React.createElement("div", {
              className: "chat"
            }, React.createElement("div", {
                  className: "chat-header clearfix"
                }, React.createElement("div", {
                      className: "chat-about"
                    }, React.createElement("div", {
                          className: "chat-with"
                        }, "Chat about " + (String(prTitle$1) + ""), React.createElement("div", {
                              className: "chat-num-messages"
                            }, commentCountString, React.createElement("button", {
                                  onClick: (function (param) {
                                      return Curry._1(onRefresh, /* () */0);
                                    })
                                }, "Refresh"))))), React.createElement("div", {
                  className: "chat-history"
                }, React.createElement("ul", undefined, commentsEl)), React.createElement(PullRequestManager$MessageCompose, {
                  onSubmit: onSubmit
                }));
}

var ChatHistory = {
  make: PullRequestManager$ChatHistory
};

function stringOfIssueState(param) {
  if (param !== 880069578) {
    if (param >= 982149804) {
      return "merged";
    } else {
      return "closed";
    }
  } else {
    return "open";
  }
}

function PullRequestManager$PullRequestHistory(Props) {
  var pullRequests = Props.pullRequests;
  var onSelectPullRequest = Props.onSelectPullRequest;
  var onHide = Props.onHide;
  var match = React.useState((function () {
          return ;
        }));
  var setSearch = match[1];
  var search = match[0];
  var pullRequestsEl = Belt_List.toArray(Belt_List.keepMap(pullRequests, (function (pr) {
              var isMatch;
              if (search !== undefined) {
                var searchRe = new RegExp(search);
                var isBodyMatch = Belt_Option.isSome(Caml_option.null_to_opt(pr.body.match(searchRe)));
                var isTitleMatch = Belt_Option.isSome(Caml_option.null_to_opt(pr.title.match(searchRe)));
                var isStateMatch = Belt_Option.isSome(Caml_option.null_to_opt(stringOfIssueState(pr.state).match(searchRe)));
                var isNumberMatch = Belt_Option.isSome(Caml_option.null_to_opt(String(pr.number).match(searchRe)));
                isMatch = isBodyMatch || isTitleMatch || isStateMatch || isNumberMatch;
              } else {
                isMatch = true;
              }
              if (isMatch) {
                return Caml_option.some(React.createElement("li", {
                                key: pr.title,
                                className: "clearfix",
                                style: {
                                  cursor: "pointer"
                                },
                                onClick: (function (param) {
                                    return Curry._1(onSelectPullRequest, pr);
                                  })
                              }, React.createElement("div", {
                                    className: "about"
                                  }, React.createElement("div", {
                                        className: "name"
                                      }, prTitle(pr)), React.createElement("div", {
                                        className: "status"
                                      }, React.createElement("i", {
                                            className: "fa fa-circle online"
                                          }), stringOfIssueState(pr.state)))));
              }
              
            })));
  return React.createElement("div", {
              className: "people-list",
              id: "people-list"
            }, React.createElement("div", {
                  className: "search",
                  style: {
                    color: "white"
                  },
                  onClick: (function (param) {
                      return Curry._1(onHide, /* () */0);
                    })
                }, "Hide Chat >>"), React.createElement("div", {
                  className: "search"
                }, React.createElement("input", {
                      placeholder: "search",
                      type: "text",
                      onChange: (function ($$event) {
                          var other = $$event.target.value;
                          var value = other === "" ? undefined : other;
                          return Curry._1(setSearch, (function (param) {
                                        return value;
                                      }));
                        })
                    }), React.createElement("i", {
                      className: "fa fa-search"
                    })), React.createElement("ul", {
                  className: "list"
                }, pullRequestsEl));
}

var PullRequestHistory = {
  make: PullRequestManager$PullRequestHistory
};

function PullRequestManager(Props) {
  var client = Props.client;
  var pullRequests = Props.pullRequests;
  var myUsername = Props.myUsername;
  var refresh = Props.refresh;
  var onHide = Props.onHide;
  var match = React.useState((function () {
          var match = Belt_List.getBy(pullRequests, (function (pr) {
                  return Belt_Option.mapWithDefault(pr.comments.nodes, false, (function (nodes) {
                                return nodes.length !== 0;
                              }));
                }));
          if (match !== undefined) {
            return Caml_option.valFromOption(match);
          } else {
            throw [
                  Caml_builtin_exceptions.failure,
                  "No commented PR found"
                ];
          }
        }));
  var setSelectedPullRequest = match[1];
  var selectedPullRequest = match[0];
  var comments = GraphQL$EggheadStatic.unwrapGHConn(Caml_option.some(selectedPullRequest.comments));
  return React.createElement("div", {
              className: "chat-widget-container clearfix"
            }, React.createElement(PullRequestManager$PullRequestHistory, {
                  pullRequests: pullRequests,
                  onSelectPullRequest: (function (pullRequest) {
                      return Curry._1(setSelectedPullRequest, (function (param) {
                                    return pullRequest;
                                  }));
                    }),
                  onHide: onHide
                }), React.createElement(PullRequestManager$ChatHistory, {
                  comments: comments,
                  myUsername: myUsername,
                  pr: selectedPullRequest,
                  onSubmit: (function (message) {
                      var message$1 = message;
                      var pullRequestId = selectedPullRequest.id;
                      return $$Promise.map(submitPrComment(client, message$1, pullRequestId), (function (param) {
                                    return Curry._1(refresh, { });
                                  }));
                    }),
                  onRefresh: (function (param) {
                      return Curry._1(refresh, { });
                    })
                }));
}

var make = PullRequestManager;

export {
  prTitle ,
  timeSince ,
  submitPrComment ,
  MessageCompose ,
  ChatHistory ,
  stringOfIssueState ,
  PullRequestHistory ,
  make ,
  
}
/* react Not a pure module */
