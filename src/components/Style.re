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
  let make = (~comments, ~myUsername, ~prTitle, ~onSubmit, ~onRefresh) => {
    open React;
    let commentsEl =
      comments
      ->Belt.List.map(comment => {
          let authorLogin =
            comment##author
            ->Belt.Option.mapWithDefault(
                "Unknown",
                fun
                | `GitHubActor(author) => author##login,
              );

          let messageIsMe = authorLogin == myUsername;

          let authorEl =
            <span className="message-data-name">
              {string(authorLogin)}
            </span>;

          let timeEl =
            <span className="message-data-time">
              {string(comment##createdAt)}
            </span>;

          <li className="clearfix">
            <div
              className={"message-data" ++ (messageIsMe ? "" : " align-right")}>
              {messageIsMe ? <> authorEl timeEl </> : <> timeEl authorEl </>}
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

    <div className="chat">
      <div className="chat-header clearfix">
        <div className="chat-about">
          <div className="chat-with">
            {string({j|Chat about $prTitle|j})}
            <span className="chat-num-messages">
              {string(List.length(comments)->string_of_int ++ " comments")}
            </span>
            <button onClick={_ => onRefresh()}> {string("Refresh")} </button>
          </div>
        </div>
      </div>
      <div className="chat-history"> <ul> commentsEl </ul> </div>
      <MessageCompose onSubmit />
    </div>;
  };
};

module PullRequestHistory = {
  [@react.component]
  let make = () =>
    React.(
      <div className="people-list" id="people-list">
        <div className="search">
          <input type_="text" placeholder="search" />
          <i className="fa fa-search" />
        </div>
        <ul className="list">
          <li className="clearfix">
            <img
              src="https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_01.jpg"
              alt="avatar"
            />
            <div className="about">
              <div className="name"> {string({|Vincent Porter|})} </div>
              <div className="status">
                <i className="fa fa-circle online" />
                {string({| online
            |})}
              </div>
            </div>
          </li>
          <li className="clearfix">
            <img
              src="https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_02.jpg"
              alt="avatar"
            />
            <div className="about">
              <div className="name"> {string({|Aiden Chavez|})} </div>
              <div className="status">
                <i className="fa fa-circle offline" />
                {string({| left 7 mins ago
            |})}
              </div>
            </div>
          </li>
          <li className="clearfix">
            <img
              src="https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_03.jpg"
              alt="avatar"
            />
            <div className="about">
              <div className="name"> {string({|Mike Thomas|})} </div>
              <div className="status">
                <i className="fa fa-circle online" />
                {string({| online
            |})}
              </div>
            </div>
          </li>
          <li className="clearfix">
            <img
              src="https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_04.jpg"
              alt="avatar"
            />
            <div className="about">
              <div className="name"> {string({|Erica Hughes|})} </div>
              <div className="status">
                <i className="fa fa-circle online" />
                {string({| online
            |})}
              </div>
            </div>
          </li>
          <li className="clearfix">
            <img
              src="https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_05.jpg"
              alt="avatar"
            />
            <div className="about">
              <div className="name"> {string({|Ginger Johnston|})} </div>
              <div className="status">
                <i className="fa fa-circle online" />
                {string({| online
            |})}
              </div>
            </div>
          </li>
          <li className="clearfix">
            <img
              src="https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_06.jpg"
              alt="avatar"
            />
            <div className="about">
              <div className="name"> {string({|Tracy Carpenter|})} </div>
              <div className="status">
                <i className="fa fa-circle offline" />
                {string({| left 30 mins ago
            |})}
              </div>
            </div>
          </li>
          <li className="clearfix">
            <img
              src="https://s3-us-west-2.amazonaws.com/s.cdpn.io/195612/chat_avatar_07.jpg"
              alt="avatar"
            />
            <div className="about">
              <div className="name"> {string({|Christian Kelly|})} </div>
              <div className="status">
                <i className="fa fa-circle offline" />
                {string({| left 10 hours ago
            |})}
              </div>
            </div>
          </li>
        </ul>
      </div>
    );
};
