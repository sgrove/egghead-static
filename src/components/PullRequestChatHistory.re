[@bs.val]
external addDocumentEventListener: (string, 'event) => unit =
  "document.addEventListener";

[@bs.val]
external removeDocumentEventListener: (string, 'event) => unit =
  "document.removeEventListener";

type quote = {
  /* A serialized selection for later rendering */
  range: Rangy.Serialized.range,
  text: string,
};

type commentMetadata = {
  /* What's the globally unique thing we're commenting on?
     We can use this to have threaded comments */
  commentableId: string,
  /* The comment might be quoting from the commentable piece*/
  quote: option(quote),
};

let parseCommentMetadata = meta => {
  let commentableId = Js.Null_undefined.toOption(meta##commentableId);
  let quote = Js.Null_undefined.toOption(meta##quote);

  switch (commentableId, quote) {
  | (Some(commentableId), quote) => Some({commentableId, quote})
  | _ => None
  };
};

module CommentFragment = [%relay.fragment
  {|
fragment PullRequestChatHistory_CommentFragment on GitHubComment {
  id
  author {
    __typename
    login
    avatarUrl
  }
  createdAt
  body
}
|}
];

module AddPullRequestCommentMutation = [%relay.mutation
  {|mutation PullRequestChatHistory_AddPullRequestCommentMutation(
  $body: String!
  $commentableId: ID!
) {
  gitHub {
    addComment(
      input: { body: $body, subjectId: $commentableId }
    ) {
      clientMutationId
      commentEdge {
        node {
          id
          ...PullRequestChatHistory_CommentFragment
        }
      }
    }
  }
}
|}
];

module PullRequestFragment = [%relay.fragment
  {|
fragment PullRequestChatHistory_PullRequestFragment on GitHubPullRequest {
  id
  title
  body
  state
  number
  url
  comments(last: 100) @connection(key: "PullRequestChatHistory_PullRequestFragment_comments") {
    edges {
      node {
      id
       ...PullRequestChatHistory_CommentFragment
      }
    }
  }
}
|}
];

module PullRequestContainerQuery = [%relay.query
  {|
query PullRequestChatHistory_PullRequestContainerQuery($pullRequestId: ID!) {
  gitHub {
    node(id: $pullRequestId) {
      __typename
      ... on GitHubPullRequest {
        ...PullRequestChatHistory_PullRequestFragment
      }
    }
  }
}
|}
];

module Query = [%relay.query
  {|
query PullRequestChatHistory_CommentQuery($query: String!, $last: Int!) {
  gitHub {
    search(query: $query, type: ISSUE, last: $last)
      @connection(key: "PullRequestChatHistory_CommentQuery_gitHub_search") {
      edges {
        node {
          __typename
          ... on GitHubPullRequest {
            id
            ...PullRequestChatHistory_PullRequestFragment
          }
        }
      }
    }
  }
}
|}
];

let timeSince: Js.Date.t => string = [%raw
  {|(date) => {

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
}|}
];

let username = "sgrove";

Utils.assignToWindowForDeveloperDebug(~name="ss", Rangy.serializeSelection);
Utils.assignToWindowForDeveloperDebug(~name="ds", Rangy.deserializeSelection);

module Comment = {
  [@react.component]
  let make = (~comment, ~myUsername) => {
    let comment = CommentFragment.use(comment);
    let (rawMeta, commentBody) = comment.body->EggheadMarkdownMeta.ofString;
    let meta = rawMeta->parseCommentMetadata;
    open React;

    let (removeHighlight, setRemoveHighlight) = useState(() => None);

    let timeEl =
      <span className="message-data-time">
        {(comment.createdAt->Js.Date.fromString->timeSince ++ " ago")
         ->React.string}
      </span>;

    let authorLogin =
      comment.author
      ->Belt.Option.mapWithDefault("Unknown", author => author.login);

    let messageIsMe = authorLogin == myUsername;

    let avatarUrl =
      comment.author
      ->Belt.Option.mapWithDefault("", author => author.avatarUrl);

    let authorEl =
      <span className="message-data-name"> {string(authorLogin)} </span>;

    let avatarEl =
      <img
        src=avatarUrl
        alt="avatar"
        className={
          "chat-avatar " ++ (messageIsMe ? "float-left" : "float-right")
        }
      />;

    <>
      <div
        className={
          "message-data clearfix" ++ (messageIsMe ? "" : " align-right")
        }>
        {messageIsMe
           ? <> avatarEl authorEl timeEl </> : <> timeEl authorEl avatarEl </>}
      </div>
      <div
        className={
          "message "
          ++ (messageIsMe ? " my-message" : " other-message align-right")
        }
        onMouseEnter={_ => {
          meta
          ->Belt.Option.flatMap(meta => {meta.quote})
          ->Belt.Option.forEach(quote => {
              let root = [%bs.raw
                "document.querySelector('.markdown-content')"
              ];

              try(
                switch (
                  quote.range
                  ->Rangy.deserializeRange(root)
                  ->Belt.Option.flatMap(Highlight.highlightRange)
                ) {
                | None => ()
                | Some(removeHighlight) =>
                  setRemoveHighlight(_ => Some(() => removeHighlight()))
                }
              ) {
              | exn =>
                Js.log2(
                  "FIXME: Can't highlight twice with the same range: ",
                  exn,
                )
              };
            })
        }}
        onMouseLeave={_ =>
          removeHighlight
          ->Belt.Option.map(removeHighlight => removeHighlight())
          ->ignore
        }>
        {string(commentBody)}
      </div>
    </>;
  };
};

module MessageCompose = {
  let extractNewCommentId =
      (response: AddPullRequestCommentMutation.Types.response) => {
    switch (response) {
    | {
        gitHub:
          Some({
            addComment: Some({commentEdge: Some({node: Some({id})})}),
          }),
      } =>
      Some(id)
    | _ => None
    };
  };

  [@react.component]
  let make = (~commentableId) => {
    let (body, setBody) = React.useState(() => "");
    let (quote, setQuote) = React.useState(() => None);

    React.useEffect(() => {
      let listener = () => {
        let selection = Rangy.Selection.getCurrent();
        let root = [%bs.raw "document.querySelector('.markdown-content')"];
        selection->Rangy.Selection.isCollapsed
          ? ()
          : setQuote(_ => {
              selection
              ->Rangy.serializeSelection(~root)
              ->Belt.Option.map(range => {
                  {range, text: Rangy.Selection.toString(selection)}
                })
            });
      };

      addDocumentEventListener("selectionchange", listener);
      Some(() => removeDocumentEventListener("selectionchange", listener));
    });

    let (addComment, isMutating) = AddPullRequestCommentMutation.use();

    let mutation = body => {
      let metaData = {commentableId, quote};

      let metadataString = metaData->Utils.uglyStringify;

      let quoteText =
        quote->Belt.Option.mapWithDefault("", ({text}) => {j|> $text
|j});

      let body = {j|$quoteText
$body

```egghead-meta
$metadataString
```|j};

      addComment(
        ~variables={body, commentableId},
        ~updater=
          (store, response) => {
            ReasonRelay.(
              switch (extractNewCommentId(response)) {
              | Some(id) =>
                switch (
                  store->RecordSourceSelectorProxy.get(~dataId=id->makeDataId)
                ) {
                | None => ()
                | Some(node) =>
                  let insertAt: ReasonRelayUtils.insertAt = Start;
                  ReasonRelayUtils.createAndAddEdgeToConnections(
                    ~store,
                    ~node,
                    ~connections=[
                      {
                        key: "PullRequestChatHistory_PullRequestFragment_comments",
                        parentID: commentableId->makeDataId,
                        filters: None,
                      },
                    ],
                    ~edgeName="GitHubIssueEdge",
                    ~insertAt,
                  );
                }
              | None => Js.Console.warn("Could not find node id")
              }
            )
          },
        ~onCompleted=
          (response, _errors) => {
            switch (extractNewCommentId(response)) {
            | Some(_) => setBody(_ => "")
            | None => ()
            }
          },
        (),
      );
    };

    <div>
      <form
        className="chat-message clearfix"
        onSubmit={event => {
          ReactEvent.Form.preventDefault(event);
          ReactEvent.Form.stopPropagation(event);
          let _dispose = mutation(body);
          ();
        }}>
        <textarea
          name="message-to-send"
          id="message-to-send"
          placeholder="Type your message"
          disabled=isMutating
          rows=2
          value=body
          style={ReactDOMRe.Style.make(~color="black", ())}
          onChange={event => {
            let value = ReactEvent.Form.currentTarget(event)##value;
            setBody(_ => value);
          }}
          onKeyDown={event => {
            let metaKey = ReactEvent.Keyboard.metaKey(event);
            let ctrlKey = ReactEvent.Keyboard.ctrlKey(event);
            let enterKey = ReactEvent.Keyboard.which(event) == 13;

            (metaKey || ctrlKey) && enterKey ? mutation(body)->ignore : ();
          }}
        />
        <button> {React.string({|Send|})} </button>
      </form>
    </div>;
  };
};

module Chat = {
  type commentNode = PullRequestFragment.Types.fragment_comments_edges_node;

  [@react.component]
  let make =
      (
        ~comments:
           array(PullRequestFragment.Types.fragment_comments_edges_node),
        ~myUsername: string,
      ) => {
    open React;

    // Filter out any duplicate comments we might have received from the subscription (this will go away in the next version of Relay)
    let helper = (arr: array(commentNode)) =>
      Belt.Array.reduce(arr, []: list(commentNode), (acc, comment) =>
        if (Belt.List.some(acc, ({id}) => id == comment.id)) {
          acc;
        } else {
          [comment, ...acc];
        }
      )
      ->Belt.List.toArray
      ->Belt.Array.reverse;

    let uniqueComments = helper(comments);

    let historyEl =
      uniqueComments
      ->Belt.Array.map(comment => {
          <li className="clearfix" key={comment.id}>
            <Comment comment={comment.getFragmentRefs()} myUsername />
          </li>
        })
      ->array;

    <ul> historyEl </ul>;
  };
};

let prTitle = (pr: PullRequestFragment.Types.fragment): string =>
  "#" ++ pr.number->string_of_int ++ ": " ++ pr.title;

[@bs.get] external clientHeight: Dom.element => int = "clientHeight";
[@bs.set] external setScrollTop: (Dom.element, int) => unit = "scrollTop";

module PullRequestChat = {
  [@react.component]
  let make = (~pullRequest, ~myUsername) => {
    let chatRef = React.useRef(Js.Nullable.null);

    // Scroll to the bottom when the height changes
    let chatRefHeight =
      chatRef.current
      ->Js.Nullable.toOption
      ->Belt.Option.map(chatRef => clientHeight(chatRef))
      ->Belt.Option.getWithDefault(0);

    // TODO: Only do this if the scroll is at 98% or more (standard chat scroll behavior)
    React.useEffect1(
      () => {
        switch (Js.Nullable.toOption(chatRef.current)) {
        | None => None
        | Some(chatDiv) =>
          chatDiv->setScrollTop(chatRefHeight);
          None;
        }
      },
      [|chatRefHeight|],
    );
    let pr = PullRequestFragment.use(pullRequest);
    open React;

    let comments =
      PullRequestFragment.getConnectionNodes_comments(pr.comments);

    let prTitle = prTitle(pr);

    <div className="chat">
      <div className="chat-meta clearfix">
        <div className="chat-about">
          <div className="chat-with">
            {string(prTitle)}
            <a alt={j|$prTitle on GitHub|j} target="_blank" href={pr.url}>
              {string({j|⤴|j})}
            </a>
          </div>
        </div>
      </div>
      <div className="chat-history" ref={ReactDOM.Ref.domRef(chatRef)}>
        <Chat comments myUsername />
      </div>
      <MessageCompose commentableId={pr.id} />
    </div>;
  };
};

[@react.component]
let make = (~pullRequestId, ~myUsername) => {
  let query =
    PullRequestContainerQuery.use(
      ~variables={pullRequestId: pullRequestId},
      (),
    );

  React.(
    <div className="chat-widget-container clearfix">
      {switch (query) {
       | {gitHub: Some({node: Some(`GitHubPullRequest(pullRequest))})} =>
         <PullRequestChat
           pullRequest={pullRequest.getFragmentRefs()}
           myUsername
         />
       | _ => null
       }}
    </div>
  );
};
