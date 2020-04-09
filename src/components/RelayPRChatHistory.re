[@bs.val]
external prettyStringify: ('a, Js.Nullable.t(unit), int) => string =
  "JSON.stringify";

module CommentFragment = [%relay.fragment
  {|
fragment RelayPRChatHistory_CommentFragment on GitHubComment {
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
  {|mutation RelayPRChatHistory_AddPullRequestCommentMutation(
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
          ...RelayPRChatHistory_CommentFragment
        }
      }
    }
  }
}
|}
];

module PullRequestFragment = [%relay.fragment
  {|
fragment RelayPRChatHistory_PullRequestFragment on GitHubPullRequest {
  id
  title
  body
  state
  number
  comments(last: 100) @connection(key: "RelayPRChatHistory_PullRequestFragment_comments") {
    edges {
      node {
      id
       ...RelayPRChatHistory_CommentFragment
      }
    }
  }
}
|}
];

module PullRequestContainerQuery = [%relay.query
  {|
query RelayPRChatHistory_PullRequestContainerQuery($pullRequestId: ID!) {
  gitHub {
    node(id: $pullRequestId) {
      __typename
      ... on GitHubPullRequest {
        ...RelayPRChatHistory_PullRequestFragment
      }
    }
  }
}
|}
];

module Query = [%relay.query
  {|
query RelayPRChatHistory_CommentQuery(
     $query: String!
     $last: Int!
   ) {
     gitHub {
       search(query: $query, type: ISSUE, last: $last)
         @connection(key:"RelayPRChatHistory_CommentQuery_gitHub_search") {
         edges {
           node {
             __typename
             ... on GitHubPullRequest {
              id
              ...RelayPRChatHistory_PullRequestFragment
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

module Comment = {
  [@react.component]
  let make = (~comment, ~myUsername) => {
    let comment = CommentFragment.use(comment);
    open React;

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
        }>
        {string(comment.body)}
      </div>
    </>;
  };
};

module CommentableMessageCompose = {
  [@react.component]
  let make = (~commentableId) => {
    let (body, setBody) = React.useState(() => "");
    let (addComment, _isMutating) = AddPullRequestCommentMutation.use();

    let mutation = body =>
      addComment(
        ~variables={body, commentableId},
        ~updater=
          (store, response) => {
            ReasonRelay.(
              switch (response) {
              | {
                  gitHub:
                    Some({
                      addComment:
                        Some({commentEdge: Some({node: Some({id})})}),
                    }),
                } =>
                switch (
                  store->RecordSourceSelectorProxy.get(~dataId=id->makeDataId)
                ) {
                | None => ()
                | Some(node) =>
                  ReasonRelayUtils.createAndAddEdgeToConnections(
                    ~store,
                    ~node,
                    ~connections=[
                      {
                        key: "RelayPRChatHistory_PullRequestFragment_comments",
                        parentID: commentableId->makeDataId,
                        filters: None,
                      },
                    ],
                    ~edgeName="GitHubIssueEdge",
                    ~insertAt=End,
                  )
                }
              | _ => Js.Console.warn("Could not find node id")
              }
            )
          },
        (),
      );

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
          disabled=false
          rows=2
          value=body
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
  [@react.component]
  let make =
      (
        ~comments:
           array(PullRequestFragment.Types.fragment_comments_edges_node),
        ~myUsername: string,
      ) => {
    open React;

    let historyEl =
      comments
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

module PullRequestChat = {
  [@react.component]
  let make = (~pullRequest, ~myUsername) => {
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
            <button> {string("Refresh")} </button>
          </div>
        </div>
      </div>
      <div className="chat-history"> <Chat comments myUsername /> </div>
      <CommentableMessageCompose commentableId={pr.id} />
    </div>;
  };
};

module PullRequestContainer = {
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
};
