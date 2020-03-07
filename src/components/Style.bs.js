// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as List from "bs-platform/lib/es6/list.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Belt_List from "bs-platform/lib/es6/belt_List.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";

function Style$MessageCompose(Props) {
  var onSubmit = Props.onSubmit;
  var match = React.useState((function () {
          return "";
        }));
  var setText = match[1];
  var text = match[0];
  return React.createElement("div", {
              className: "chat-message clearfix"
            }, React.createElement("textarea", {
                  id: "message-to-send",
                  name: "message-to-send",
                  placeholder: "Type your message",
                  rows: 2,
                  value: text,
                  onKeyDown: (function ($$event) {
                      var metaKey = $$event.metaKey;
                      var ctrlKey = $$event.ctrlKey;
                      var enterKey = $$event.which === 13;
                      if ((metaKey || ctrlKey) && enterKey) {
                        return Curry._1(onSubmit, text);
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
                        return Curry._1(onSubmit, text);
                      }
                    })
                }, "Send"));
}

var MessageCompose = {
  make: Style$MessageCompose
};

function Style$ChatHistory(Props) {
  var comments = Props.comments;
  var myUsername = Props.myUsername;
  var prTitle = Props.prTitle;
  var onSubmit = Props.onSubmit;
  var onRefresh = Props.onRefresh;
  var commentsEl = Belt_List.toArray(Belt_List.map(comments, (function (comment) {
              var authorLogin = Belt_Option.mapWithDefault(comment.author, "Unknown", (function (param) {
                      return param[1].login;
                    }));
              var messageIsMe = authorLogin === myUsername;
              var authorEl = React.createElement("span", {
                    className: "message-data-name"
                  }, authorLogin);
              var timeEl = React.createElement("span", {
                    className: "message-data-time"
                  }, comment.createdAt);
              return React.createElement("li", {
                          className: "clearfix"
                        }, React.createElement("div", {
                              className: "message-data" + (
                                messageIsMe ? "" : " align-right"
                              )
                            }, messageIsMe ? React.createElement(React.Fragment, undefined, authorEl, timeEl) : React.createElement(React.Fragment, undefined, timeEl, authorEl)), React.createElement("div", {
                              className: "message " + (
                                messageIsMe ? " my-message" : " other-message align-right"
                              )
                            }, comment.body));
            })));
  return React.createElement("div", {
              className: "chat"
            }, React.createElement("div", {
                  className: "chat-header clearfix"
                }, React.createElement("div", {
                      className: "chat-about"
                    }, React.createElement("div", {
                          className: "chat-with"
                        }, "Chat about " + (String(prTitle) + ""), React.createElement("span", {
                              className: "chat-num-messages"
                            }, String(List.length(comments)) + " comments"), React.createElement("button", {
                              onClick: (function (param) {
                                  return Curry._1(onRefresh, /* () */0);
                                })
                            }, "Refresh")))), React.createElement("div", {
                  className: "chat-history"
                }, React.createElement("ul", undefined, commentsEl)), React.createElement(Style$MessageCompose, {
                  onSubmit: onSubmit
                }));
}

var ChatHistory = {
  make: Style$ChatHistory
};

function Style$PullRequestHistory(Props) {
  return React.createElement("div", {
              className: "people-list",
              id: "people-list"
            }, React.createElement("div", {
                  className: "search"
                }, React.createElement("input", {
                      placeholder: "search",
                      type: "text"
                    }), React.createElement("i", {
                      className: "fa fa-search"
                    })), React.createElement("ul", {
                  className: "list"
                }, React.createElement("li", {
                      className: "clearfix"
                    }, React.createElement("img", {
                          alt: "avatar",
                          src: "https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_01.jpg"
                        }), React.createElement("div", {
                          className: "about"
                        }, React.createElement("div", {
                              className: "name"
                            }, "Vincent Porter"), React.createElement("div", {
                              className: "status"
                            }, React.createElement("i", {
                                  className: "fa fa-circle online"
                                }), " online\n            "))), React.createElement("li", {
                      className: "clearfix"
                    }, React.createElement("img", {
                          alt: "avatar",
                          src: "https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_02.jpg"
                        }), React.createElement("div", {
                          className: "about"
                        }, React.createElement("div", {
                              className: "name"
                            }, "Aiden Chavez"), React.createElement("div", {
                              className: "status"
                            }, React.createElement("i", {
                                  className: "fa fa-circle offline"
                                }), " left 7 mins ago\n            "))), React.createElement("li", {
                      className: "clearfix"
                    }, React.createElement("img", {
                          alt: "avatar",
                          src: "https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_03.jpg"
                        }), React.createElement("div", {
                          className: "about"
                        }, React.createElement("div", {
                              className: "name"
                            }, "Mike Thomas"), React.createElement("div", {
                              className: "status"
                            }, React.createElement("i", {
                                  className: "fa fa-circle online"
                                }), " online\n            "))), React.createElement("li", {
                      className: "clearfix"
                    }, React.createElement("img", {
                          alt: "avatar",
                          src: "https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_04.jpg"
                        }), React.createElement("div", {
                          className: "about"
                        }, React.createElement("div", {
                              className: "name"
                            }, "Erica Hughes"), React.createElement("div", {
                              className: "status"
                            }, React.createElement("i", {
                                  className: "fa fa-circle online"
                                }), " online\n            "))), React.createElement("li", {
                      className: "clearfix"
                    }, React.createElement("img", {
                          alt: "avatar",
                          src: "https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_05.jpg"
                        }), React.createElement("div", {
                          className: "about"
                        }, React.createElement("div", {
                              className: "name"
                            }, "Ginger Johnston"), React.createElement("div", {
                              className: "status"
                            }, React.createElement("i", {
                                  className: "fa fa-circle online"
                                }), " online\n            "))), React.createElement("li", {
                      className: "clearfix"
                    }, React.createElement("img", {
                          alt: "avatar",
                          src: "https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_06.jpg"
                        }), React.createElement("div", {
                          className: "about"
                        }, React.createElement("div", {
                              className: "name"
                            }, "Tracy Carpenter"), React.createElement("div", {
                              className: "status"
                            }, React.createElement("i", {
                                  className: "fa fa-circle offline"
                                }), " left 30 mins ago\n            "))), React.createElement("li", {
                      className: "clearfix"
                    }, React.createElement("img", {
                          alt: "avatar",
                          src: "https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_07.jpg"
                        }), React.createElement("div", {
                          className: "about"
                        }, React.createElement("div", {
                              className: "name"
                            }, "Christian Kelly"), React.createElement("div", {
                              className: "status"
                            }, React.createElement("i", {
                                  className: "fa fa-circle offline"
                                }), " left 10 hours ago\n            ")))));
}

var PullRequestHistory = {
  make: Style$PullRequestHistory
};

export {
  MessageCompose ,
  ChatHistory ,
  PullRequestHistory ,
  
}
/* react Not a pure module */
