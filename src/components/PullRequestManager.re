let prTitle = pr => "#" ++ pr##number->string_of_int ++ ": " ++ pr##title;

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

let submitPrComment = (~message, ~pullRequestId) => {
  open GraphQL;

  let requests = [
    () =>
      mutation(
        AddPullRequestCommentMutation.make(~pullRequestId, ~body=message, ()),
        "Error adding comment to PR",
      ),
  ];

  chain(requests);
};

module MessageCompose = {
  [@react.component]
  let make = (~onSubmit) => {
    open React;
    let (text, setText) = useState(() => "");

    <div className="chat-message clearfix">
      <textarea
        name="message-to-send"
        id="message-to-send"
        placeholder="Type your message"
        rows=2
        value=text
        onChange={event => ReactEvent.Form.target(event)##value->setText}
        onKeyDown={event => {
          let metaKey = ReactEvent.Keyboard.metaKey(event);
          let ctrlKey = ReactEvent.Keyboard.ctrlKey(event);
          let enterKey = ReactEvent.Keyboard.which(event) == 13;

          (metaKey || ctrlKey) && enterKey ? onSubmit(text) : ();
        }}
      />
      <button
        onClick={_ => Js.String.trim(text) == "" ? () : onSubmit(text)}>
        {string({|Send|})}
      </button>
    </div>;
  };
};

module ChatHistory = {
  [@react.component]
  let make = (~comments, ~myUsername, ~pr, ~onSubmit, ~onRefresh) => {
    open React;
    let commentsEl =
      comments
      ->Belt.List.map(comment => {
          let author =
            comment##author
            ->Belt.Option.map(
                fun
                | `GitHubActor(author) => author,
              );

          let authorLogin =
            author->Belt.Option.mapWithDefault("Unknown", author =>
              author##login
            );

          let avatarUrl =
            author->Belt.Option.mapWithDefault("", author =>
              author##avatarUrl
            );

          let messageIsMe = authorLogin == myUsername;

          let authorEl =
            <span className="message-data-name">
              {string(authorLogin)}
            </span>;

          let timeEl =
            <span className="message-data-time">
              {(comment##createdAt->Js.Date.fromString->timeSince ++ " ago")
               ->string}
            </span>;

          let avatarEl =
            <img
              src=avatarUrl
              alt="avatar"
              className={
                "chat-avatar " ++ (messageIsMe ? "float-left" : "float-right")
              }
            />;

          <li className="clearfix">
            <div
              className={
                "message-data clearfix" ++ (messageIsMe ? "" : " align-right")
              }>
              {messageIsMe
                 ? <> avatarEl authorEl timeEl </>
                 : <> timeEl authorEl avatarEl </>}
            </div>
            <div
              className={
                "message "
                ++ (messageIsMe ? " my-message" : " other-message align-right")
              }>
              {string(comment##body)}
            </div>
          </li>;
        })
      ->Belt.List.toArray
      ->array;

    let prTitle = prTitle(pr);

    let commentCount = List.length(comments);
    let commentCountString =
      commentCount->string_of_int
      ++ " "
      ++ (commentCount == 1 ? "comment" : "comments");

    <div className="chat">
      <div className="chat-header clearfix">
        <div className="chat-about">
          <div className="chat-with">
            {string({j|Chat about $prTitle|j})}
            <div className="chat-num-messages">
              {string(commentCountString)}
              <button onClick={_ => onRefresh()}>
                {string("Refresh")}
              </button>
            </div>
          </div>
        </div>
      </div>
      <div className="chat-history"> <ul> commentsEl </ul> </div>
      <MessageCompose onSubmit />
    </div>;
  };
};

let stringOfIssueState =
  fun
  | `CLOSED => "closed"
  | `MERGED => "merged"
  | `OPEN => "open";

module PullRequestHistory = {
  [@react.component]
  let make = (~pullRequests, ~onSelectPullRequest, ~onHide) => {
    open React;

    let (search, setSearch) = useState(() => None);

    let pullRequestsEl =
      pullRequests
      ->Belt.List.keepMap(pr => {
          let isMatch =
            switch (search) {
            | None => true
            | Some(search) =>
              let searchRe = search->Js.Re.fromString;
              let isBodyMatch =
                pr##body->Js.String2.match(searchRe)->Belt.Option.isSome;

              let isTitleMatch =
                pr##title->Js.String2.match(searchRe)->Belt.Option.isSome;

              let isStateMatch =
                pr##state
                ->stringOfIssueState
                ->Js.String2.match(searchRe)
                ->Belt.Option.isSome;

              let isNumberMatch =
                pr##number
                ->string_of_int
                ->Js.String2.match(searchRe)
                ->Belt.Option.isSome;

              isBodyMatch || isTitleMatch || isStateMatch || isNumberMatch;
            };

          switch (isMatch) {
          | false => None
          | true =>
            Some(
              <li
                key=pr##title
                className="clearfix"
                style={ReactDOMRe.Style.make(~cursor="pointer", ())}
                onClick={_ => onSelectPullRequest(~pullRequest=pr)}>
                <div className="about">
                  <div className="name"> {string(prTitle(pr))} </div>
                  <div className="status">
                    <i className="fa fa-circle online" />
                    {string(pr##state->stringOfIssueState)}
                  </div>
                </div>
              </li>,
            )
          };
        })
      ->Belt.List.toArray
      ->array;

    <div className="people-list" id="people-list">
      <div
        onClick={_ => onHide()}
        className="search"
        style={ReactDOMRe.Style.make(~color="white", ())}>
        {string("Hide Chat >>")}
      </div>
      <div className="search">
        <input
          type_="text"
          placeholder="search"
          onChange={event => {
            let value =
              switch (ReactEvent.Form.target(event)##value) {
              | "" => None
              | other => Some(other)
              };

            setSearch(_ => value);
          }}
        />
        <i className="fa fa-search" />
      </div>
      <ul className="list"> pullRequestsEl </ul>
    </div>;
  };
};

[@react.component]
let make = (~pullRequests, ~myUsername, ~refresh, ~onHide) => {
  open React;
  let onSubmit = (~message, ~pullRequestId) =>
    submitPrComment(~pullRequestId, ~message)
    ->Js.Promise.then_(
        _ =>
          Js.Promise.resolve(
            refresh(Some(UrqlClient.ClientTypes.partialOperationContext())),
          ),
        _,
      )
    ->ignore;

  let (selectedPullRequest, setSelectedPullRequest) =
    useState(() =>
      switch (
        pullRequests->Belt.List.getBy(pr =>
          pr##comments##nodes
          ->Belt.Option.mapWithDefault(false, nodes =>
              Array.length(nodes) > 0
            )
        )
      ) {
      | None => raise(Failure("No commented Pr found"))
      | Some(pr) => pr
      }
    );

  let comments = Some(selectedPullRequest##comments)->GraphQL.unwrapGHConn;

  <div className="chat-widget-container clearfix">
    <PullRequestHistory
      pullRequests
      onHide
      onSelectPullRequest={(~pullRequest) =>
        setSelectedPullRequest(_ => pullRequest)
      }
    />
    <ChatHistory
      comments
      myUsername
      pr=selectedPullRequest
      onSubmit={message =>
        onSubmit(~message, ~pullRequestId=selectedPullRequest##id)
      }
      onRefresh={_ =>
        refresh(Some(UrqlClient.ClientTypes.partialOperationContext()))
      }
    />
  </div>;
};
