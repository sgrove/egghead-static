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
  let make = (~comment) => {
    let comment = CommentFragment.use(comment);
    let author = comment.author;

    let messageIsMe = true;

    let avatarEl =
      switch (author) {
      | None => "Swedish coward"->React.string
      | Some({login, avatarUrl}) =>
        React.(
          <>
            <img
              src=avatarUrl
              alt="avatar"
              style={ReactDOMRe.Style.make(
                ~maxWidth="50px",
                ~borderRadius="50px",
                (),
              )}
              className={
                "chat-avatar " ++ (messageIsMe ? "float-left" : "float-right")
              }
            />
            {string(login)}
          </>
        )
      };

    React.(<div> avatarEl <br /> comment.body->string <br /> </div>);
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
          (store, _response) => {
            let parentID = commentableId |> ReasonRelay.makeDataId;

            let _r =
              ReasonRelay.RecordSourceSelectorProxy.get(
                store,
                ~dataId=parentID,
              )
              ->Belt.Option.map(node =>
                  ReasonRelay.RecordProxy.invalidateRecord(node)
                );

            /* let valueToLog = */
            /*   ReasonRelay.RecordSourceSelectorProxy.getRootField( */
            /*     store, */
            /*     ~fieldName="gitHub", */
            /*   ); */

            Js.log2("PullREquestId: ", parentID);
          },
        /* [%bs.debugger]; */
        /* Js.log2("Value zth", valueToLog); */
        /* let nodeProxy = */
        /*   ReasonRelayUtils.resolveNestedRecordFromRoot( */
        /*     ~store, */
        /*     ~path=["gitHub", "addComment", "commentEdge", "node"], */
        /*   ); */
        /* switch (nodeProxy) { */
        /* | None => Js.log("No addComment node found after mutation") */
        /* | Some(node) => */
        /*   let key = "RelayPRChatHistory_PullRequestFragment_comments"; */
        /*   let edgeName = "GitHubIssueCommentEdge"; */
        /*   ReasonRelayUtils.createAndAddEdgeToConnections( */
        /*     ~store, */
        /*     ~node, */
        /*     ~edgeName, */
        /*     ~connections=[{parentID, key}], */
        /*     ~insertAt=End, */
        /*   ); */
        /* }; */
        (),
      );

    <div className="chat-message clearfix">
      <form
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
        <button
          onClick={_ =>
            Js.String.trim(body) == "" ? () : mutation(body)->ignore
          }>
          {React.string({|Send|})}
        </button>
      </form>
    </div>;
  };
};

module Chat = {
  [@react.component]
  let make = (~comments: array(PullRequestFragment.Operation.Types.node)) => {
    open React;

    let historyEl =
      comments
      ->Belt.Array.map(comment => {
          <li> <Comment comment={comment.getFragmentRefs()} /> </li>
        })
      ->array;

    <ul> historyEl </ul>;
  };
};

module PullRequestChat = {
  [@react.component]
  let make = (~pr) => {
    let pr = PullRequestFragment.use(pr);
    open React;

    let comments =
      PullRequestFragment.getConnectionNodes_comments(pr.comments);

    let prTitle = pr.title;

    let commentCountString = Array.length(comments)->string_of_int;

    <div className="chat">
      <div className="chat-header clearfix">
        <div className="chat-about">
          <div className="chat-with">
            {string({j|Chat about $prTitle|j})}
            <div className="chat-num-messages">
              {string(commentCountString)}
              <button> {string("Refresh")} </button>
            </div>
          </div>
        </div>
      </div>
      <div className="chat-history"> <Chat comments /> </div>
      <CommentableMessageCompose commentableId={pr.id} />
    </div>;
  };
};

module PullRequestContainer = {
  [@react.component]
  let make = (~pullRequestId) => {
    let query =
      PullRequestContainerQuery.use(
        ~variables={pullRequestId: pullRequestId},
        (),
      );
    React.(
      <div className="chat-widget-container clearfix">
        {switch (query) {
         | {gitHub: Some({node: Some(`GitHubPullRequest(pr))})} =>
           <PullRequestChat pr={pr.getFragmentRefs()} />
         | _ => null
         }}
      </div>
    );
  };
};

[@react.component]
let make = () => {
  let query =
    Query.use(
      ~variables={
        query: {j|repo:eggheadio/egghead-asciicasts [by $username] in:title|j},
        last: 100,
      },
      (),
    );
  open React;
  let element =
    switch (query) {
    | {gitHub: Some({search})} =>
      let nodes = Query.getConnectionNodes_search(search);
      nodes
      ->Belt.Array.map(node => {
          switch (node) {
          | `GitHubPullRequest(pr) =>
            <PullRequestChat pr={pr.getFragmentRefs()} />
          | _ => React.null
          }
        })
      ->array;
    | _ => string("No pull requests found for you")
    };

  <>
    element
    <pre> {prettyStringify(query, Js.Nullable.null, 2)->string} </pre>
  </>;
};
