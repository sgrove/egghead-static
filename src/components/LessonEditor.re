let assign = [%raw {|function(name, item) {
     window[name] = item;
}|}];

[@bs.send]
external getAttribute: ('t, string) => Js.Nullable.t(string) = "getAttribute";

[@bs.val]
external prettyStringify: ('a, Js.Nullable.t(unit), int) => string =
  "JSON.stringify";

module Utils = {
  module String = {
    let random = length => {
      let gen = () =>
        switch (Js.Math.random_int(0, 26 + 26 + 10)) {
        | n when n < 26 => int_of_char('a') + n
        | n when n < 26 + 26 => int_of_char('A') + n - 26
        | n => int_of_char('0') + n - 26 - 26
        };
      let gen = _ => String.make(1, char_of_int(gen()));
      String.concat("", Array.to_list(Array.init(length, gen)));
    };
    let toBranchName = (string, username) => {
      let sanitized =
        Js.String.replaceByRe([%bs.re {|/[^a-zA-Z0-9]+/g|}], "-", string);
      Js.String.toLocaleLowerCase(
        "branch-name-" ++ sanitized ++ {j|$username|j},
      );
    };
  };

  type lineChar = {
    line: int,
    char: int,
  };
  type sourcePosition = (lineChar, lineChar);
  let extractSourcePosition = string =>
    switch (Js.Nullable.toOption(string)) {
    | None => None
    | Some(string) =>
      switch (Js.String.split("-", string)) {
      | [|from, to_|] =>
        switch (Js.String.(split(":", from), split(":", to_))) {
        | ([|fromLine, fromChar|], [|toLine, toChar|]) =>
          Some((
            {line: int_of_string(fromLine), char: int_of_string(fromChar)},
            {line: int_of_string(toLine), char: int_of_string(toChar)},
          ))
        | _ => None
        }

      | _ => None
      }
    };
};

module OneGraphAuth = {
  include OneGraphAuth;

  let getLocalJwtMe = auth =>
    accessToken(auth)
    ->Js.Nullable.toOption
    ->Belt.Option.map(token => OneJwt.payload(token##accessToken));

  let getLocalUserId = auth => {
    let jwtMe = getLocalJwtMe(auth);

    let id =
      OneJwt.(
        jwtMe->Belt.Option.flatMap(jwtMe =>
          userGet(jwtMe)->Belt.Option.flatMap(user => idGet(user))
        )
      )
      ->Belt.Option.map(string_of_int);

    id;
  };
};

module ReactResizable = {
  type size = {
    width: int,
    height: int,
  };

  type resizeCallbackData('handle) = {
    element: React.element,
    size,
    handle: 'handle,
  };

  module Box = {
    [@bs.module "react-resizable"] [@react.component]
    external make:
      (
        ~width: int=?,
        ~height: int=?,
        ~className: string=?,
        // If you change this=?, be sure to update your css
        ~handleSize: array(int)=?,
        ~lockAspectRatio: bool=?,
        ~axis: [@bs.string] [ | `both | `x | `y | `none]=?,
        ~minConstraints: array(int)=?,
        ~maxConstraints: array(int)=?,
        ~onResizeStop: ('event, resizeCallbackData('handle)) => unit=?,
        ~onResizeStart: ('event, resizeCallbackData('handle)) => unit=?,
        ~onResize: ('event, resizeCallbackData('handle)) => unit=?,
        /* ~draggableOpts?: ?Object=?, */
        ~resizeHandles: array(string)=?,
        ~children: 'children
      ) =>
      React.element =
      "ResizableBox";
  };
};

module ReactMarkdown = {
  [@bs.module] [@react.component]
  external make:
    (
      ~source: string,
      ~onClick: 'a => unit=?,
      ~sourcePos: bool=?,
      ~renderers: Js.t({..})=?
    ) =>
    React.element =
    "react-markdown";

  module WrapRoot = {
    let wrapper = (~onClick: 'b) =>
      [@react.component]
      (
        (~value as _: React.element, ~children: 'a) =>
          <div onClick> children </div>
      );
  };
};

module ReactDraggable = {
  [@bs.module] [@react.component]
  external make:
    (
      ~allowAnyClick: bool=?,
      ~axis: string=?,
      ~bounds: {
                 .
                 "left": int,
                 "top": int,
                 "right": int,
                 "bottom": int,
               }
                 =?,
      ~cancel: string=?,
      ~defaultClassName: string=?,
      ~defaultClassNameDragging: string=?,
      ~defaultClassNameDragged: string=?,
      ~defaultPosition: {
                          .
                          "x": int,
                          "y": int,
                        }
                          =?,
      ~disabled: bool=?,
      ~grid: array(int)=?,
      ~handle: string=?,
      ~offsetParent: React.element=?,
      ~onMouseDown: 'mouseEvent => unit=?,
      ~positionOffset: {
                         .
                         "x": int,
                         "y": int,
                       }
                         =?,
      ~scale: int=?,
      ~children: 'b
    ) =>
    React.element =
    "react-draggable";
};

module ReactModal = {
  [@bs.module "react-modal"] [@bs.val]
  external defaultStyles: ReactDOMRe.style = "defaultStyles";

  [@bs.module] [@react.component]
  external make:
    (
      ~isOpen: bool,
      ~onAfterOpen: unit => unit=?,
      ~onRequestClose: unit => unit=?,
      ~closeTimeoutMS: int=?,
      ~style: {
                .
                "overlay": ReactDOMRe.style,
                "content": ReactDOMRe.style,
              }
                =?,
      ~contentLabel: string=?,
      ~portalClassName: string=?,
      ~overlayClassName: string=?,
      ~className: string=?,
      ~bodyOpenClassName: string=?,
      ~htmlOpenClassName: string=?,
      ~ariaHideApp: bool=?,
      ~shouldFocusAfterRender: bool=?,
      ~shouldCloseOnOverlayClick: bool=?,
      ~shouldCloseOnEsc: bool=?,
      ~shouldReturnFocusAfterClose: bool=?,
      ~role: string=?,
      ~parentSelector: unit => React.element=?,
      ~aria: {
               .
               "labelledby": string,
               "describedby": string,
             }
               =?,
      ~data: {..}=?,
      ~overlayRef: 'ref=?,
      ~contentRef: 'ref=?,
      ~children: 'b
    ) =>
    React.element =
    "react-modal";
};

module ReactDiffViewer = {
  [@bs.module "react-diff-viewer"] [@react.component]
  external make:
    (
      ~oldValue: string,
      ~newValue: string,
      ~splitView: bool=?,
      ~disableWordDiff: bool=?,
      ~hideLineNumbers: bool=?,
      ~onLineNumberClick: {. "lineId": string} => unit=?,
      ~highlightLines: array(string)=?,
      ~showDiffOnly: bool=?,
      ~extraLinesSurroundingDiff: int=?,
      ~styles: {.}=?
    ) =>
    React.element =
    "default";
};

let repoOwner = "OneGraph";
let repoName = "egghead-asciicasts-experiment";

module Egghead = {
  type transcript = {
    enhanced: bool,
    text: string,
  };

  type lesson = {
    title: string,
    duration: int,
    enhanced_transcript_url: string,
    id: int,
    slug: string,
    transcript_url: string,
  };
};

module ReadOnly = {
  [@react.component]
  let make = (~lesson: Egghead.lesson, ~transcript: Egghead.transcript) => {
    ignore(0);
    let result =
      React.(
        <div>
          <h4> {string(lesson.title)} </h4>
          <ReactMarkdown source={transcript.text} />
        </div>
      );

    result;
  };
};

let modalStyle =
  ReactDOMRe.Style.make(
    ~position="relative",
    ~display="flex",
    ~flexDirection="column",
    ~marginTop="50%",
    (),
  );

let activeEditorStyle =
  ReactDOMRe.Style.make(
    ~minHeight="250px",
    ~position="fixed",
    ~left="0px",
    ~bottom="0px",
    ~borderRadius="4px",
    ~border="1px solid #ccc",
    ~backgroundColor="white",
    ~overflowX="scroll",
    ~boxShadow="6px 4px 24px 0px rgba(0, 0, 0, 0.34)",
    (),
  );

let inactiveEditorStyle =
  ReactDOMRe.Style.make(
    ~minHeight="250px",
    ~position="fixed",
    ~left="0px",
    ~bottom="0px",
    ~borderRadius="4px",
    ~border="1px solid #ccc",
    ~backgroundColor="white",
    ~overflowX="scroll",
    ~opacity="0.25",
    (),
  );

let textEditorStyle =
  ReactDOMRe.Style.make(~width="100%", ~height="20ch", ~fontSize="2em", ());

let submitPr =
    (
      ~client,
      ~branchName,
      ~title,
      ~body,
      ~editedContent,
      ~filePath,
      ~sha,
      ~username,
    ) => {
  open GraphQL;

  /*
     1. GetFileShaQuery
     2. CreateBranchMutation
     3. UpdateFileContentMutation
     4. CreatePullRequestMutation
     5. AddLabelsToPullRequestMutation
   */

  let requests = [
    () =>
      mutation(
        ~client,
        CreateBranchMutation.make(~repoOwner, ~repoName, ~branchName, ()),
        "Error creating branch for PR",
      ),
    () =>
      mutation(
        ~client,
        UpdateFileContentMutation.make(
          ~repoOwner,
          ~repoName,
          ~branchName,
          ~path=filePath,
          ~message="Updated " ++ filePath,
          ~content=editedContent,
          ~sha,
          (),
        ),
        "Error updating file content",
      ),
    () =>
      mutation(
        ~client,
        CreatePullRequestMutation.make(
          ~repoOwner,
          ~repoName,
          ~sourceBranch=branchName,
          ~destinationBranch="master",
          ~title=title ++ "[by " ++ username ++ "]",
          ~body=
            {j|Submitted by user $username (eggheadUser: seangrove)
--
|j}
            ++ body,
          (),
        ),
        "Error creating PullRequest",
      ),
  ];

  chain(requests);
};

module Editor = {
  type state = {
    userId: option(string),
    username: string,
    gitHubLogin: string,
    text: string,
    isEditing: bool,
    width: int,
  };

  type action =
    | Login(string)
    | Logout
    | SetEditing(bool)
    | Resize(int);

  [@react.component]
  let make = (~auth, ~content, ~onInitiateSubmit, ~onLogout, ~jwtMe) => {
    open ReasonUrql;
    open React;
    let editorHandle = React.useRef(None);

    let (state, dispatch) =
      useReducer(
        (state, action) =>
          switch (action) {
          | Login(userId) => {...state, userId: Some(userId)}
          | Logout =>
            OneGraphAuth.logout(auth, "github", ())
            ->Js.Promise.then_(
                _ => auth->OneGraphAuth.clearToken->Js.Promise.resolve,
                _,
              )
            ->ignore;
            {...state, userId: None};
          | Resize(width) =>
            editorHandle
            ->React.Ref.current
            ->Belt.Option.map(BsReactMonaco.layout)
            ->ignore;

            {...state, width};
          | SetEditing(isEditing) => {...state, isEditing}
          },
        {
          userId: OneGraphAuth.getLocalUserId(auth),
          text: content,
          isEditing: true,
          username: "",
          gitHubLogin: "",
          width: 250,
        },
      );

    let (isHovered, setIsHovered) = React.useState(() => true);

    let (editedText, setEditedText) = React.useState(() => state.text);

    let loginEl =
      switch (state.userId) {
      | None =>
        <button
          style={ReactDOMRe.Style.make(~width="50%", ())}
          onClick={_ =>
            (
              OneGraphAuth.login(auth, "github")
              |> Js.Promise.then_(() =>
                   OneGraphAuth.isLoggedIn(auth, "github")
                   ->Js.Promise.then_(
                       isLoggedIn =>
                         (
                           switch (isLoggedIn) {
                           | false => dispatch(Logout)
                           | true =>
                             let userId = OneGraphAuth.getLocalUserId(auth);
                             switch (userId) {
                             | None => ()
                             | Some(userId) => dispatch(Login(userId))
                             };
                           }
                         )
                         ->Js.Promise.resolve,
                       _,
                     )
                 )
            )
            ->ignore
          }>
          {string("Login with GitHub")}
        </button>
      | Some(_userId) =>
        <div>
          <span>
            {string(
               "Logged in as "
               ++ OneJwt.findGitHubLogin(~default="unknown", jwtMe),
             )}
          </span>
          <button onClick={_ => onLogout()}> {string("Logout")} </button>
          {editedText == content
             ? null
             : <button
                 onClick={_ => onInitiateSubmit(~editedContent=editedText)}
                 style={ReactDOMRe.Style.make(
                   ~position="absolute",
                   ~right="10px",
                   (),
                 )}>
                 {string("Create PR")}
               </button>}
        </div>
      };

    [@react.component]
    let rootWrapper = (~value: Js.t({..})) =>
      <div
        onClick={event =>
          switch (
            ReactEvent.Mouse.altKey(event),
            editorHandle->React.Ref.current,
          ) {
          | (_, None)
          | (false, _) => ()
          | (true, Some(editorHandle)) =>
            let target = ReactEvent.Mouse.target(event);
            getAttribute(target, "data-sourcepos")
            ->Utils.extractSourcePosition
            ->Belt.Option.map(((from, to_)) => {
                BsReactMonaco.revealLine(editorHandle, from.line);
                BsReactMonaco.setSelection(
                  editorHandle,
                  {
                    startLineNumber: from.line,
                    startColumn: from.char,
                    endLineNumber: to_.line,
                    endColumn: to_.char,
                  },
                );
                BsReactMonaco.focus(editorHandle);
              })
            ->ignore;
          }
        }>
        {value##children}
      </div>;

    <div>
      {state.isEditing
         ? <ReactDraggable cancel=".react-monaco-editor-container">
             <div
               id="eggy-editor-container"
               style={ReactDOMRe.Style.combine(
                 {isHovered ? activeEditorStyle : inactiveEditorStyle},
                 ReactDOMRe.Style.make(
                   ~width=state.width->string_of_int ++ "px",
                   (),
                 ),
               )}
               onMouseEnter={_ => setIsHovered(_ => true)}
               onMouseLeave={_ => setIsHovered(_ => false)}>
               <div>
                 loginEl
                 <button onClick={_ => dispatch(SetEditing(false))}>
                   {string("Hide Editor")}
                 </button>
               </div>
               <ReactMonacoLazy.Editor.Lazy
                 className="transcript-editor"
                 value=editedText
                 height="250px"
                 theme="vs-dark"
                 language="markdown"
                 options={
                   "minimap": {
                     "enabled": false,
                   },
                 }
                 editorDidMount={(editor, _monaco) =>
                   React.Ref.setCurrent(editorHandle, Some(editor))
                 }
                 onChange={(newValue, _event) => setEditedText(_ => newValue)}
               />
             </div>
           </ReactDraggable>
         : <div
             style={ReactDOMRe.Style.make(
               ~position="fixed",
               ~bottom="0px",
               ~left="0px",
               (),
             )}>
             <button onClick={_ => dispatch(SetEditing(true))}>
               {string("Show Editor")}
             </button>
           </div>}
      <ReactMarkdown
        onClick={event => Js.log2("Please tell me this works", event)}
        source=editedText
        sourcePos=true
        renderers={"root": rootWrapper}
      />
    </div>;
  };
};

module PullRequestPreparation = {
  type action =
    | SetTitle(string)
    | SetBody(string);

  type state = {
    title: string,
    body: string,
  };

  [@react.component]
  let make =
      (~client, ~editedText, ~content, ~sha, ~filePath, ~onClose, ~username) => {
    open React;
    let editorHandle = React.useRef(None);

    Js.log2("basic editor handle: ", editorHandle);

    let _windowSize =
      Hooks.useWindowSize(size => {
        Js.log2("basic editor handle: ", editorHandle);

        Js.log3("Resize detected", editorHandle, size);
        switch (editorHandle->React.Ref.current, size) {
        | (Some(editor), _) =>
          Js.log3("Resizing editor: ", BsReactMonaco.layout, editor);
          BsReactMonaco.layout(editor);
        | _ => ()
        };
      });

    let (state, dispatch) =
      useReducer(
        (state, action) =>
          switch (action) {
          | SetTitle(title) => {...state, title}
          | SetBody(body) => {...state, body}
          },
        {title: "", body: ""},
      );

    <div
      style={ReactDOMRe.Style.make(
        ~display="flex",
        ~flexWrap="nowrap",
        ~flexDirection="row",
        ~justifyContent="space-around",
        ~alignItems="stretch",
        ~alignContent="stretch",
        (),
      )}>
      <div
        style={ReactDOMRe.Style.make(
          ~flex="0 0 auto",
          ~margin="0px",
          ~flexGrow="1",
          (),
        )}>
        <React.Suspense fallback={<div> "Loading..."->React.string </div>}>
          <ReactMonacoLazy.DiffViewer.Lazy
            className="transcript-editor"
            original=content
            value=editedText
            height="80vh"
            theme="vs-dark"
            language="markdown"
            options={"renderSideBySide": false}
            editorDidMount={(editor, _monaco) =>
              React.Ref.setCurrent(editorHandle, Some(editor))
            }
          />
        </React.Suspense>
      </div>
      <div
        style={ReactDOMRe.Style.make(
          ~flex="0 0 auto",
          ~display="flex",
          ~flexWrap="nowrap",
          ~flexDirection="column",
          ~justifyContent="flex-start",
          ~alignItems="stretch",
          ~alignContent="stretch",
          (),
        )}>
        <h4> {string("Title of your change")} </h4>
        <input
          type_="text"
          onChange={event =>
            dispatch(SetTitle(ReactEvent.Form.target(event)##value))
          }
          value={state.title}
        />
        <h4> {string("Explanation of your change")} </h4>
        <textarea
          onChange={event =>
            dispatch(SetBody(ReactEvent.Form.target(event)##value))
          }
          value={state.body}
        />
        <button
          onClick={_ => {
            let submitPromise =
              submitPr(
                ~client,
                ~branchName=Utils.String.toBranchName(state.title, username),
                ~username,
                ~title=state.title,
                ~body=state.body,
                ~editedContent=editedText,
                ~sha,
                ~filePath,
              );
            submitPromise
            ->Js.Promise.then_(
                (result: GraphQL.mutationChainResult) => {
                  switch (result) {
                  | Ok () => Js.log("Ok, PR created!")
                  | Error(message) => Js.log2("Error creating PR: ", message)
                  };

                  onClose()->Js.Promise.resolve;
                },
                _,
              )
            ->ignore;
          }}>
          {string("Submit PR")}
        </button>
        <button
          onClick={_ => onClose()}
          style={ReactDOMRe.Style.make(~marginTop="auto", ())}>
          {string("Back to editing")}
        </button>
      </div>
    </div>;
  };
};

module Conversation = {
  [@react.component]
  let make = (~client, ~username, ~onHide) => {
    open React;
    open ReasonUrql.Hooks;
    let request =
      GraphQL.SearchForPullRequestsQuery.make(
        ~query=
          {j|repo:OneGraph/egghead-asciicasts-experiment [by $username] in:title|j},
        ~last=100,
        (),
      );

    let ({response}, executeQuery) =
      useQuery(~request, ~requestPolicy=`NetworkOnly, ());

    Js.log2("Response: ", response);

    <div>
      {switch (response) {
       | NotFound => <div> {string("Not found")} </div>
       | Error({graphQLErrors: _}) =>
         <div> {string("Error loading conversation")} </div>
       | Fetching => <div> {string("Loading conversation...")} </div>
       | Data(data) =>
         open Belt.Option;

         let pullRequests =
           data##gitHub
           ->map(d => d##search)
           ->GraphQL.filterGHConn((acc, next) =>
               switch (next) {
               | Some(`GitHubPullRequest(pr)) => [pr, ...acc]
               | _ => acc
               }
             );

         <PullRequestManager
           client
           myUsername="sgrove"
           pullRequests
           onHide
           refresh={_ => {
             Js.log(executeQuery);
             executeQuery(None);
           }}
         />;
       }}
    </div>;
  };
};

module ConversationBubble = {
  type action =
    | Hide
    | Show;

  type state = {
    username: string,
    isOpen: bool,
  };

  [@react.component]
  let make = (~client, ~username) => {
    open React;

    let (state, dispatch) =
      useReducer(
        (state, action) =>
          switch (action) {
          | Hide => {...state, isOpen: false}
          | Show => {...state, isOpen: true}
          },
        {username, isOpen: false},
      );

    <div
      style={ReactDOMRe.Style.make(
        ~height="100vh",
        ~position="fixed",
        ~top="0px",
        ~right="0px",
        (),
      )}>
      {state.isOpen
         ? <Conversation client onHide={_ => dispatch(Hide)} username />
         : <div
             style={ReactDOMRe.Style.make(
               ~position="fixed",
               ~bottom="10px",
               ~right="10px",
               ~display=state.isOpen ? "none" : "block",
               (),
             )}>
             <button
               style={ReactDOMRe.Style.make(
                 ~cursor="pointer",
                 ~borderRadius="50px",
                 ~width="60px",
                 ~height="60px",
                 ~backgroundColor="black",
                 ~color="white",
                 ~border="none",
                 (),
               )}
               onClick={_ => dispatch(Show)}>
               <Icons.Chat />
             </button>
           </div>}
    </div>;
  };
};

module Container = {
  let modalStyle = {
    "overlay":
      ReactDOMRe.Style.make(~backgroundColor="rgba(100, 100, 100, 0.75)", ()),
    "content": ReactModal.defaultStyles,
  };

  type mode =
    | Editing
    | Submitting;

  type content = {
    original: string,
    edited: string,
  };

  type state = {
    userId: option(string),
    content,
    title: option(string),
    body: option(string),
    mode,
  };

  type action =
    | SetTitle(option(string))
    | SetBody(option(string))
    | SetContentEditing
    | SetSubmitting(string);

  [@react.component]
  let make =
      (~auth, ~client, ~sha: string, ~content, ~filePath, ~onLogout, ~jwtMe) => {
    let username = OneJwt.findGitHubLogin(~default="unknown", jwtMe);
    open React;
    let (state, dispatch) =
      useReducer(
        (state, action) =>
          switch (action) {
          | SetTitle(title) => {...state, title}
          | SetBody(body) => {...state, body}
          | SetContentEditing => {...state, mode: Editing}
          | SetSubmitting(newContent) => {
              ...state,
              mode: Submitting,
              content: {
                original: state.content.original,
                edited: newContent,
              },
            }
          },
        {
          userId: None,
          content: {
            original: content,
            edited: content,
          },
          title: None,
          body: None,
          mode: Editing,
        },
      );

    switch (state.mode) {
    | Editing =>
      <div>
        <ConversationBubble client username />
        <React.Suspense
          fallback={<div> "Loading editor..."->React.string </div>}>
          <Editor
            auth
            jwtMe
            content
            onInitiateSubmit={(~editedContent) =>
              dispatch(SetSubmitting(editedContent))
            }
            onLogout
          />
        </React.Suspense>
      </div>
    | Submitting =>
      <ReactModal isOpen=true style=modalStyle ariaHideApp=false>
        <PullRequestPreparation
          client
          editedText={state.content.edited}
          content={state.content.original}
          sha
          filePath
          onClose={_ => dispatch(SetContentEditing)}
          username={OneJwt.findGitHubLogin(~default="unknown", jwtMe)}
        />
      </ReactModal>
    };
  };
};

module Fetcher = {
  type mode =
    | Editing
    | Loading
    | Submitting;

  type content = {
    original: string,
    editing: string,
  };

  type state = {
    missingAuthServices: list(string),
    jwtMe: option(OneJwt.t),
  };

  type action =
    | SetLoggedIn(OneJwt.t)
    | SetLoggedOut;

  [@react.component]
  let make =
      (
        ~auth,
        ~client,
        ~lesson: Egghead.lesson,
        ~transcript as _: Egghead.transcript,
      ) => {
    open React;
    open ReasonUrql.Hooks;

    let branch = "master";
    let filePath =
      "the-beginner-s-guide-to-figma/lessons/" ++ lesson.slug ++ ".md";

    let (state, dispatch) =
      useReducer(
        (state, action) =>
          switch (action) {
          | SetLoggedIn(jwtMe) => {...state, jwtMe: Some(jwtMe)}
          | SetLoggedOut => {...state, jwtMe: None}
          },
        {missingAuthServices: [], jwtMe: OneGraphAuth.getLocalJwtMe(auth)},
      );

    let request =
      GraphQL.GetFileShaAndContentQuery.make(
        ~repoName,
        ~repoOwner,
        ~branchAndFilePath={j|$branch:$filePath|j},
        (),
      );

    let loginButton = (auth, service, ~onLogin) =>
      <button
        style={ReactDOMRe.Style.make(~width="50%", ())}
        onClick={_ =>
          OneGraphAuth.login(auth, service)
          ->Js.Promise.then_(
              () =>
                OneGraphAuth.isLoggedIn(auth, service)
                ->Js.Promise.then_(
                    isLoggedIn =>
                      (
                        switch (isLoggedIn) {
                        | false => dispatch(SetLoggedOut)
                        | true => onLogin(OneGraphAuth.getLocalJwtMe(auth))
                        }
                      )
                      ->Js.Promise.resolve,
                    _,
                  ),
              _,
            )
          ->ignore
        }>
        {string("Login with " ++ service)}
      </button>;

    let onLogout = () =>
      OneGraphAuth.logout(auth, "github", ())
      ->Js.Promise.then_(
          _next => dispatch(SetLoggedOut)->Js.Promise.resolve,
          _,
        )
      ->ignore;

    let ({response}, _) =
      useQuery(~request, ~requestPolicy=`NetworkOnly, ());

    switch (state.jwtMe) {
    | None =>
      <div>
        {string("Please ")}
        {loginButton(auth, "github", ~onLogin=jwtMe =>
           switch (jwtMe) {
           | None => ()
           | Some(jwtMe) => dispatch(SetLoggedIn(jwtMe))
           }
         )}
        {string(" to edit lesson transcripts")}
      </div>
    | Some(_jwtMe) =>
      switch (response) {
      | NotFound => <div> {string("Not found")} </div>
      | Error({graphQLErrors}) =>
        switch (OneGraphAuth.findMissingAuthServices(auth, graphQLErrors)) {
        | [] =>
          <div>
            {string(
               "Error: "
               ++ prettyStringify(graphQLErrors, Js.Nullable.null, 2),
             )}
            <button
              onClick={_ =>
                OneGraphAuth.logout(auth, "github", ())
                ->Js.Promise.then_(
                    _next => dispatch(SetLoggedOut)->Js.Promise.resolve,
                    _,
                  )
                ->ignore
              }>
              {string("Logout")}
            </button>
          </div>
        | [missingService, ..._rest] =>
          <div>
            {string("Please ")}
            {loginButton(auth, missingService, ~onLogin=jwtMe =>
               switch (jwtMe) {
               | None => ()
               | Some(jwtMe) => dispatch(SetLoggedIn(jwtMe))
               }
             )}
            {string(" to edit lesson transcripts")}
          </div>
        }
      | Fetching => <div> {string("Loading...")} </div>
      | Data(data) =>
        open Belt;

        let blob =
          data##gitHub
          ->Option.flatMap(d => d##repository)
          ->Option.flatMap(d => d##object_)
          ->Option.flatMap(
              fun
              | `GitHubBlob(d) => Some(d)
              | `GitHubGitObject(_) => None,
            );

        let sha = blob->Option.map(d => d##oid);
        let content = blob->Option.flatMap(d => d##text);

        switch (sha, content, state.jwtMe) {
        | (None, _, _) =>
          <>
            {string("Unable to determine sha: ")}
            <pre> {data->prettyStringify(Js.Nullable.null, 2)->string} </pre>
          </>
        | (_, None, _) => <pre> {string("No content to edit")} </pre>
        | (_, _, None) =>
          <pre> {string("Unable to ascertain local user")} </pre>
        | (Some(sha), Some(content), Some(jwtMe)) =>
          <Container client auth sha content filePath onLogout jwtMe />
        };
      }
    };
  };
};

[@react.component]
let make = (~lesson: Egghead.lesson, ~transcript: Egghead.transcript) => {
  open ReasonUrql;

  let (isEditing, _setIsEditing) = React.useState(() => true);

  switch (Config.auth, GraphQL.urqlClient) {
  | (Some(auth), Some(client)) =>
    <Provider value=client>
      {isEditing
         ? <Fetcher auth client lesson transcript />
         : <ReadOnly lesson transcript />}
    </Provider>
  | _ => "Loading lesson editor..."->React.string
  };
};

let default = make;
