let assign = [%raw
  {|function(name, item) {
     window[name] = item;
     }|}
];

[@bs.val] external confirm: string => bool = "window.confirm";

[@bs.send]
external getAttribute: ('t, string) => Js.Nullable.t(string) = "getAttribute";

[@bs.val]
external prettyStringify: ('a, Js.Nullable.t(unit), int) => string =
  "JSON.stringify";

type frontMatter = {
  lessonId: int,
  filePath: string,
  username: string,
  sha: string,
};

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

module YamlFrontMatter = {
  [@bs.module "yaml-front-matter"]
  external loadFront: string => 'a = "loadFront";
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
          jwtMe.user->Belt.Option.flatMap(user => user.id)
        )
      )
      ->Belt.Option.map(string_of_int);

    id;
  };
};

module ReactAnimatedTree = {
  [@bs.module "react-animated-tree"] [@react.component]
  external make:
    (
      ~content: React.element,
      ~_type: React.element=?,
      ~_open: bool=?,
      ~canHide: bool=?,
      ~visible: bool=?,
      ~onClick: ReactEvent.Mouse.t => unit=?,
      ~children: 'children=?
    ) =>
    React.element =
    "default";
};

module Tree = ReactAnimatedTree;

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

  type instructor = {
    avatar_32_url: string,
    full_name: string,
  };

  type course = {
    description: string,
    instructor,
    lessons: array(lesson),
    published_at: string,
    rating_count: int,
    rating_out_of_5: float,
    square_cover_480_url: string,
    summary: string,
    title: string,
  };

  type courseWithNullableLessons = {
    description: string,
    instructor,
    lessons: Js.Nullable.t(array(lesson)),
    published_at: string,
    rating_count: int,
    rating_out_of_5: float,
    square_cover_480_url: string,
    summary: string,
    title: string,
  };

  let courseSlug = (course: course) =>
    course.title
    ->Js.String2.replaceByRe([%bs.re "/\W+/g"], "-")
    ->Js.String2.toLocaleLowerCase;
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
    ~width="100%",
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
    ~opacity="0.98",
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
      ~frontMatter,
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
    () => {
      let frontMatterContent =
        frontMatter->prettyStringify(Js.Nullable.null, 2);
      let frontMatterText = {j|---
$frontMatterContent
---|j};
      mutation(
        ~client,
        CreatePullRequestMutation.make(
          ~repoOwner,
          ~repoName,
          ~sourceBranch=branchName,
          ~destinationBranch="master",
          ~title=title ++ "[by " ++ username ++ "]",
          ~body={j|$frontMatterText

$body|j},
          (),
        ),
        "Error creating PullRequest",
      );
    },
  ];

  chain(requests);
};

module ChatHistory = {
  [@react.component]
  let make = (~client, ~comments, ~myUsername, ~pr, ~onSubmit, ~onRefresh) => {
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
              {(
                 comment##createdAt
                 ->Js.Date.fromString
                 ->PullRequestManager.timeSince
                 ++ " ago"
               )
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
          Js.log2("Comment id: ", comment##id);

          <li
            className="clearfix"
            key={
              comment##id;
            }>
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

    let prTitle = PullRequestManager.prTitle(pr);

    let commentCount = List.length(comments);
    let commentCountString =
      commentCount->string_of_int
      ++ " "
      ++ (commentCount == 1 ? "comment" : "comments");

    let pullRequestId = pr##id;

    <div className="chat">
      <div className="chat-meta"> prTitle->string </div>
      <div className="chat-history">
        <ul className="chat-messages"> commentsEl </ul>
      </div>
      <PullRequestManager.MessageCompose
        onSubmit={message =>
          PullRequestManager.submitPrComment(
            ~client,
            ~pullRequestId,
            ~message,
          )
        }
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
      (~client, ~editedText, ~content, ~sha, ~filePath, ~username, ~lessonId) => {
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
          let frontMatter = {lessonId, filePath, sha, username};
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
              ~frontMatter,
            );
          submitPromise
          /* onClose()->Js.Promise.resolve; */
          ->Js.Promise.then_(
              (result: GraphQL.mutationChainResult) => {
                (
                  switch (result) {
                  | Ok () => Js.log("Ok, PR created!")
                  | Error(message) => Js.log2("Error creating PR: ", message)
                  }
                )
                ->Js.Promise.resolve
              },
              _,
            )
          ->ignore;
        }}>
        {string("Submit PR")}
      </button>
    </div>;
    /* onClick={_ => onClose()} */
  };
};

let filepathOfLesson = (course: Egghead.course, lesson: Egghead.lesson) => {
  let lessonSlug = lesson.slug;
  let courseSlug = Egghead.courseSlug(course);
  let filePath = {j|$courseSlug/lessons/$lessonSlug.md|j};
  filePath;
};

module Editor = {
  type editPayload = {
    transcript: string,
    edited: string,
    sha: string,
  };

  type lessonEdit = {
    lesson: Egghead.lesson,
    editPayload: option(editPayload),
  };

  type pr('pr) = {
    lessonId: int,
    pr: 'pr,
  };

  type state('pr) = {
    prs: Belt.Map.Int.t(list('pr)),
    chatOpen: bool,
    lessons: Belt.Map.Int.t(lessonEdit),
    lessonId: option(int),
    prId: option(string),
  };

  type action('a) =
    | EditLesson(int, string)
    | SelectLesson(int)
    | SelectPR(int, string)
    | LoadTranscript(int, editPayload)
    | LoadPrs('a)
    | ToggleChat;

  let updateLesson = (state, id, update) => {
    let lessons =
      state.lessons
      ->Belt.Map.Int.update(
          id,
          fun
          | Some(lesson) => Some(update(lesson))

          | None => None,
        );
    {...state, lessons};
  };

  [@react.component]
  let make =
      (
        ~auth as _,
        ~client,
        ~onInitiateSubmit,
        ~onLogout as _,
        ~jwtMe: OneJwt.t,
        ~course: Egghead.course,
      ) => {
    open ReasonUrql;
    open React;
    let editorHandle = React.useRef(None);

    let lessons = course.lessons->Belt.List.fromArray;

    let firstLessonId =
      switch (lessons) {
      | [lesson, ..._] => Some(lesson.id)
      | _ => None
      };

    let (state, dispatch) =
      useReducer(
        (state, action) =>
          switch (action) {
          | EditLesson(id, edited) =>
            updateLesson(
              state,
              id,
              lesson => {
                let editPayload =
                  lesson.editPayload
                  ->Belt.Option.map(editPayload => {...editPayload, edited});
                {...lesson, editPayload};
              },
            )
          | SelectLesson(id) =>
            Js.log2("Looking at ", id);
            {...state, lessonId: Some(id), prId: None};
          | SelectPR(lessonId, prId) =>
            Js.log2("Looking at ", prId);
            {...state, lessonId: Some(lessonId), prId: Some(prId)};
          | LoadPrs(prs) =>
            Js.log2("Pre-pro prs", prs);
            let prs =
              Belt.List.reduce(prs, state.prs, (acc, next: pr('a)) => {
                Belt.Map.Int.update(
                  acc,
                  next.lessonId,
                  fun
                  | Some(prs) => Some([next.pr, ...prs])
                  | None => Some([next.pr]),
                )
              });

            {...state, prs};
          | LoadTranscript(id, editPayload) =>
            updateLesson(state, id, lesson => {
              {...lesson, editPayload: Some(editPayload)}
            })
          | ToggleChat => {...state, chatOpen: !state.chatOpen}
          },
        {
          let lessons =
            course.lessons
            ->Belt.Array.map(lesson
                /* TODO: Change title to transcript */
                => (lesson.id, {lesson, editPayload: None}))
            ->Belt.Map.Int.fromArray;
          {
            chatOpen: true,
            lessons,
            lessonId: firstLessonId,
            prId: None,
            prs: Belt.Map.Int.empty,
          };
        },
      );

    let lesson =
      state.lessonId
      ->Belt.Option.flatMap(lessonId =>
          Belt.Map.Int.get(state.lessons, lessonId)
        );

    let pullRequest =
      switch (state.lessonId, state.prId) {
      | (Some(lessonId), Some(prId)) =>
        let pr =
          state.prs
          ->Belt.Map.Int.get(lessonId)
          ->Belt.Option.flatMap(prs =>
              prs->Belt.List.getBy(pr => pr##id == prId)
            );
        pr;
      | _ => None
      };

    Js.log2("Selected lesson: ", lesson);
    Js.log2("Selected PullRequest: ", pullRequest);

    useEffect0(() => {
      switch (OneJwt.findGitHubLogin(jwtMe)) {
      | None => ()
      | Some(username) =>
        let request =
          GraphQL.SearchForPullRequestsQuery.make(
            ~query=
              {j|repo:OneGraph/egghead-asciicasts-experiment [by $username] in:title|j},
            ~last=100,
            (),
          );

        (
          ReasonUrql.Client.executeQuery(~client, ~request, ())
          |> Wonka.subscribe((. data) => {
               ReasonUrql.Client.(
                 switch (data.response) {
                 | Data(data) =>
                   open Belt.Option;
                   let pullRequests =
                     data##gitHub
                     ->map(d => d##search)
                     ->GraphQL.filterGHConn((acc, next) =>
                         switch (next) {
                         | Some(`GitHubPullRequest(pr)) =>
                           let body = pr##body;
                           let parsed = YamlFrontMatter.loadFront(body);
                           Js.log2("PR: ", parsed);

                           let next =
                             switch (parsed##lessonId) {
                             | None => acc
                             | Some(lessonId) =>
                               let pr = {lessonId, pr};
                               [pr, ...acc];
                             };

                           Js.log2("Next: ", next);
                           next;

                         | _ => acc
                         }
                       );

                   dispatch(LoadPrs(pullRequests));

                 | _ => ()
                 }
               )
             })
        )
        ->ignore;
        ();
      };

      None;
    });

    useEffect1(
      () => {
        editorHandle
        ->React.Ref.current
        ->Belt.Option.map(BsReactMonaco.layout)
        ->ignore;
        None;
      },
      [|state.chatOpen|],
    );

    useEffect1(
      () => {
        switch (lesson) {
        | None
        | Some({editPayload: Some(_)}) => ()
        | Some({lesson, editPayload: None}) =>
          Js.log2("Lesson Id: ", state.lessonId);
          let branch = "master";
          let lessonSlug = lesson.slug;
          let courseSlug = Egghead.courseSlug(course);
          let filePath = {j|$courseSlug/lessons/$lessonSlug.md|j};
          let request =
            GraphQL.GetFileShaAndContentQuery.make(
              ~repoName,
              ~repoOwner,
              ~branchAndFilePath={j|$branch:$filePath|j},
              (),
            );
          (
            ReasonUrql.Client.executeQuery(~client, ~request, ())
            |> Wonka.subscribe((. data) => {
                 ReasonUrql.Client.(
                   switch (data.response) {
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
                     let transcript = blob->Option.flatMap(d => d##text);

                     switch (sha, transcript) {
                     | (Some(sha), Some(transcript)) =>
                       let editPayload = {
                         transcript,
                         sha,
                         edited: transcript,
                       };
                       dispatch(LoadTranscript(lesson.id, editPayload));
                     | _ => ()
                     };

                   | _ => ()
                   }
                 )
               })
          )
          ->ignore;
        };
        None;
      },
      [|state.lessonId|],
    );

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
      <div style={ReactDOMRe.Style.make(~marginBottom="250px", ())}>
        /* Add margin here so the bottom isn't cut off by the editor container */

          {switch (lesson) {
           | None => "No lesson selected"->string
           | Some(lesson) =>
             switch (lesson.editPayload) {
             | None => "No lesson transcript"->string
             | Some(editPayload) =>
               <ReactMarkdown
                 onClick={event =>
                   Js.log2("Please tell me this works", event)
                 }
                 source={editPayload.edited}
                 sourcePos=true
                 renderers={"root": rootWrapper}
               />
             }
           }}
        </div>
      <div id="eggy-editor-container">
        <div className="editor-title">
          <div className="lesson-title">
            {string(
               course.title ++ " by " ++ course.instructor.full_name ++ " - ",
             )}
            {switch (OneJwt.avatarUrl(jwtMe)) {
             | None => null
             | Some(url) =>
               <img
                 style={ReactDOMRe.Style.make(
                   ~display="inline",
                   ~borderRadius="50px",
                   ~width="28px",
                   (),
                 )}
                 src=url
               />
             }}
            {jwtMe
             ->OneJwt.findGitHubLogin
             ->Belt.Option.getWithDefault("unknown")
             ->string}
          </div>
          <div className="spacer" />
          <div className="chat-control" />
        </div>
        <div className="editor-body">
          <div className="tree">
            <Tree content={course.title->string} _open=true>
              {course.lessons
               ->Belt.Array.map(lesson => {
                   let prs =
                     state.prs->Belt.Map.Int.getWithDefault(lesson.id, []);
                   <Tree
                     key={lesson.id->string_of_int}
                     content={
                       <span
                         style={ReactDOMRe.Style.make(~cursor="pointer", ())}
                         onClick={_ => dispatch(SelectLesson(lesson.id))}>
                         lesson.title->string
                       </span>
                     }>
                     {switch (prs) {
                      | [] => null
                      | prs =>
                        prs
                        ->Belt.List.map(pr =>
                            <Tree
                              key={pr##id}
                              _type={
                                <span>
                                  (
                                    switch (pr##state) {
                                    | `OPEN => {j|📖|j}
                                    | `MERGED => {j|✅|j}
                                    | `CLOSED => {j|❌|j}
                                    }
                                  )
                                  ->string
                                </span>
                              }
                              content={
                                <span
                                  style={ReactDOMRe.Style.make(
                                    ~cursor="pointer",
                                    (),
                                  )}
                                  onClick={_ =>
                                    dispatch(SelectPR(lesson.id, pr##id))
                                  }>
                                  {pr##title->string}
                                </span>
                              }
                            />
                          )
                        ->Belt.List.toArray
                        ->array
                      }}
                   </Tree>;
                 })}
            </Tree>
          </div>
          <div className="editor">
            {switch (lesson) {
             | Some({lesson, editPayload: Some({edited})}) =>
               <ReactMonacoLazy.Editor.Lazy
                 className="transcript-editor"
                 value=edited
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
                 onChange={(newValue, _event) =>
                   dispatch(EditLesson(lesson.id, newValue))
                 }
               />
             | _ => null
             }}
          </div>
          <div className={state.chatOpen ? "chat-open" : "chat-closed"}>
            {switch (
               pullRequest,
               OneJwt.findGitHubLogin(jwtMe),
               lesson,
               lesson->Belt.Option.flatMap(lesson => lesson.editPayload),
             ) {
             | (None, Some(username), Some(lessonEdit), Some(editPayload)) =>
               <PullRequestPreparation
                 client
                 editedText={editPayload.edited}
                 content={editPayload.edited}
                 sha={editPayload.sha}
                 filePath={filepathOfLesson(course, lessonEdit.lesson)}
                 username
                 lessonId={lessonEdit.lesson.id}
               />
             | (Some(pr), Some(myUsername), _, _) =>
               <div>
                 <ChatHistory
                   client
                   myUsername
                   comments={Some(pr##comments)->GraphQL.unwrapGHConn}
                   pr
                   onSubmit={_ => ()}
                   onRefresh={_ => ()}
                 />
               </div>
             | _ => null
             }}
          </div>
        </div>
        <div className="editor-footer">
          {string("Egghead editor powered by OneGraph")}
          {switch (lesson) {
           | Some({editPayload: Some({edited, transcript})}) =>
             switch (transcript == edited) {
             | false =>
               <button
                 onClick={_ => onInitiateSubmit(~editedContent=edited)}
                 style={ReactDOMRe.Style.make(
                   ~position="absolute",
                   ~right="10px",
                   (),
                 )}>
                 {string("Create PR")}
               </button>
             | true => null
             }
           | _ => null
           }}
        </div>
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

let amILoggedInto = (auth, ~service, ~ifYes=?, ~ifNo=?, ()) => {
  Js.log2("Am I logged into ", service);
  OneGraphAuth.isLoggedIn(auth, service)
  ->Js.Promise.then_(
      isLoggedIn =>
        {
          Js.log3("Logged in? ", service, isLoggedIn);
          switch (isLoggedIn) {
          | false => ifNo->Belt.Option.map(f => f())
          | true => ifYes->Belt.Option.map(f => f())
          };
        }
        ->Js.Promise.resolve,
      _,
    );
};

module LoginGuard = {
  type service =
    | Egghead
    | GitHub;

  type authState =
    | Loading
    | LoggedIn(OneJwt.t)
    | LoggedOut;

  type state = {
    gitHub: authState,
    egghead: authState,
    me: option(OneJwt.t),
  };

  type action =
    | SetAuthState(service, authState);

  [@react.component]
  let make = (~auth, ~client, ~course) => {
    open React;

    let (state, dispatch) =
      useReducer(
        (state, action) =>
          switch (action) {
          | SetAuthState(service, authState) =>
            let me =
              switch (authState) {
              | LoggedIn(me) => Some(me)
              | _ => state.me
              };
            switch (service) {
            | Egghead => {...state, egghead: authState, me}
            | GitHub => {...state, gitHub: authState, me}
            };
          },
        {egghead: LoggedOut, gitHub: LoggedOut, me: None},
      );

    let checkLogin = (serviceName, service) =>
      amILoggedInto(
        auth,
        ~service=serviceName,
        ~ifYes=
          () => {
            OneGraphAuth.getLocalJwtMe(auth)
            ->Belt.Option.map(me =>
                dispatch(SetAuthState(service, LoggedIn(me)))
              )
            ->ignore
          },
        (),
      );

    useEffect0(() => {
      checkLogin("eggheadio", Egghead)->ignore;
      checkLogin("github", GitHub)->ignore;
      None;
    });

    let loggedIn =
      switch (state.egghead, state.gitHub) {
      | (LoggedIn(_), LoggedIn(_)) => true
      | _ => false
      };

    let onLogout = () => {
      let services = [Egghead, GitHub];

      services->Belt.List.forEach(service => {
        let serviceName =
          switch (service) {
          | Egghead => "eggheadio"
          | GitHub => "github"
          };

        OneGraphAuth.logout(auth, serviceName, ())
        ->Js.Promise.then_(
            _next =>
              dispatch(SetAuthState(service, LoggedOut))->Js.Promise.resolve,
            _,
          )
        ->ignore;
      });
    };

    let loginIcon = service => {
      let (serviceName, friendlyName, state) =
        switch (service) {
        | Egghead => ("eggheadio", "Egghead", state.egghead)
        | GitHub => ("github", "GitHub", state.gitHub)
        };

      switch (state) {
      | LoggedIn(_me) => <div> {j|Logged into $friendlyName|j}->string </div>
      | Loading => <div> {j|Logging into $friendlyName...|j}->string </div>
      | LoggedOut =>
        <img
          style={ReactDOMRe.Style.make(~width="50px", ~cursor="pointer", ())}
          onClick={_ => {
            dispatch(SetAuthState(service, Loading));
            OneGraphAuth.login(auth, serviceName)
            /* TODO: Report if localJwt me is None, means something went wrong with parsing the JWT */
            ->Js.Promise.then_(
                () =>
                  OneGraphAuth.isLoggedIn(auth, serviceName)
                  ->Js.Promise.then_(
                      isLoggedIn =>
                        (
                          switch (isLoggedIn) {
                          | false =>
                            dispatch(SetAuthState(service, LoggedOut))
                          | true =>
                            OneGraphAuth.getLocalJwtMe(auth)
                            ->Belt.Option.map(me =>
                                dispatch(
                                  SetAuthState(service, LoggedIn(me)),
                                )
                              )
                            ->ignore
                          }
                        )
                        ->Js.Promise.resolve,
                      _,
                    ),
                _,
              )
            ->ignore;
          }}
          src={j|/images/logos/$serviceName.svg|j}
          alt={j|Login with $friendlyName|j}
        />
      };
    };

    switch (loggedIn, state.me) {
    | (true, Some(me)) =>
      <React.Suspense
        fallback={<div> "Loading editor..."->React.string </div>}>
        <Editor
          auth
          client
          jwtMe=me
          course
          onInitiateSubmit={(~editedContent) => Js.log(editedContent)}
          onLogout
          /* dispatch(SetSubmitting(editedContent)) */
        />
      </React.Suspense>
    | (_, _) =>
      <div
        style={ReactDOMRe.Style.make(
          ~border="1px solid gray",
          ~borderRadius="4px",
          ~width="500px",
          (),
        )}>
        "Please log in"->string
        <br />
        {loginIcon(GitHub)}
        {loginIcon(Egghead)}
      </div>
    };
  };
};

[@react.component]
let make = (~course: Egghead.courseWithNullableLessons) => {
  Js.log2("Course: ", course);
  let lessons =
    switch (Js.Nullable.toOption(course.lessons)) {
    | None => [||]
    | Some(lessons) => lessons
    };

  /* Protect our code from nullable lessons */
  let course: Egghead.course = {
    description: course.description,
    instructor: course.instructor,
    lessons,
    published_at: course.published_at,
    rating_count: course.rating_count,
    rating_out_of_5: course.rating_out_of_5,
    square_cover_480_url: course.square_cover_480_url,
    summary: course.summary,
    title: course.title,
  };

  React.(
    switch (course.lessons->Belt.List.fromArray) {
    | [] => "No lessons"->string
    | _ =>
      ReasonUrql.(
        switch (Config.auth, GraphQL.urqlClient) {
        | (Some(auth), Some(client)) =>
          <Provider value=client> <LoginGuard auth client course /> </Provider>
        | _ => "Loading the Egghead™ lesson editor..."->React.string
        }
      )
    }
  );
};

let default = make;
