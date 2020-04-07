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

let repoOwner = "eggheadio";
let repoName = "egghead-asciicasts";

type repo = {
  name: string,
  owner: string,
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

let getFileShaAndContent = (~repoName, ~repoOwner, ~branchAndFilePath) => {
  let relayEnv = ReasonRelay.useEnvironmentFromContext();

  let (promise, resolve) = Promise.pending();

  RelayLessonTranscript.GetFileShaAndContentQuery.fetch(
    ~environment=relayEnv,
    ~variables={repoName, repoOwner, branchAndFilePath},
    ~onResult=result => {
    switch (result) {
    | Ok({
        gitHub:
          Some({repository: Some({object_: Some(`GitHubBlob(blob))})}),
      }) =>
      resolve(Some((blob.oid, blob.text)))
    | Ok(_) =>
      Js.Console.warn2("No such repo or file:  ", branchAndFilePath);
      resolve(None);
    | Error(err) =>
      Js.Console.warn2("Error getting data response: ", err);
      resolve(None);
    }
  });

  promise;
};

let upsertFileContent =
    (
      ~client,
      ~repoOwner,
      ~repoName,
      ~branchName,
      ~filePath,
      ~content,
      ~sha,
      (),
    ) => {
  GraphQL.(
    mutation(
      ~client,
      UpdateFileContentMutation.make(
        ~repoOwner,
        ~repoName,
        ~branchName,
        ~path=filePath,
        ~message="Updated " ++ filePath,
        ~content,
        ~sha,
        (),
      ),
      "Error updating file content",
    )
  );
};

let filepathOfLesson =
    (course: EggheadData.course, lesson: EggheadData.lesson) => {
  let lessonSlug = lesson.slug;
  let courseSlug = EggheadData.courseSlug(course);
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
    lesson: EggheadData.lesson,
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
        ~onLogout as _,
        ~jwtMe: OneJwt.t,
        ~course: EggheadData.course,
        ~username: string,
      ) => {
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

    let relayEnv = ReasonRelay.useEnvironmentFromContext();

    useEffect1(
      () => {
        switch (lesson) {
        | None
        | Some({editPayload: Some(_)}) => ()
        | Some({lesson, editPayload: None}) =>
          Js.log2("Lesson Id: ", state.lessonId);
          let branch = "master";
          let lessonSlug = lesson.slug;
          let courseSlug = EggheadData.courseSlug(course);
          let filePath = {j|$courseSlug/lessons/$lessonSlug.md|j};

          RelayLessonTranscript.GetFileShaAndContentQuery.fetch(
            ~environment=relayEnv,
            ~variables={
              repoName,
              repoOwner,
              branchAndFilePath: {j|$branch:$filePath|j},
            },
            ~onResult=result => {
              Js.log2("EggheadLessonTranscript: ", result);

              /* TODO: Handle error */
              switch (result) {
              | Ok({
                  gitHub:
                    Some({
                      repository:
                        Some({
                          object_:
                            Some(`GitHubBlob({oid: sha, text: transcript})),
                        }),
                    }),
                }) =>
                switch (sha, transcript) {
                | (sha, Some(transcript)) =>
                  let editPayload = {
                    transcript,
                    sha,
                    edited: "This is from relay!  " ++ transcript,
                  };
                  dispatch(LoadTranscript(lesson.id, editPayload));
                | _ => ()
                }
              | _ => ()
              };
            },
          );
          ();
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
            <RelayCourseTree
              course
              username
              selectedLessonId={state.lessonId}
              onLessonSelected={(~lessonId) => {
                dispatch(SelectLesson(lessonId));
                Js.log2("Selected lesson ", lessonId);
              }}
              onPullRequestSelected={(~lessonId, ~pullRequestId) => {
                dispatch(SelectPR(lessonId, pullRequestId));
                Js.log4("Selected PR ", pullRequestId, " for ", lessonId);
              }}
            />
          </div>
          <LessonEditor
            lesson={lesson->Belt.Option.map(lesson => lesson.lesson)}
            course
            onChange={(~lessonId, ~value) => {
              dispatch(EditLesson(lessonId, value))
            }}
            onEditorDidMount={(~editor) => {
              React.Ref.setCurrent(editorHandle, Some(editor))
            }}
          />
          <div className={state.chatOpen ? "chat-open" : "chat-closed"}>
            {switch (
               pullRequest,
               OneJwt.findGitHubLogin(jwtMe),
               lesson,
               lesson->Belt.Option.flatMap(lesson => lesson.editPayload),
             ) {
             | (None, Some(username), Some(lessonEdit), Some(editPayload)) =>
               <RelaySubmitPullRequest
                 repoOwner
                 repoName
                 editedText={editPayload.edited}
                 sha={editPayload.sha}
                 filePath={filepathOfLesson(course, lessonEdit.lesson)}
                 username
                 lesson={lessonEdit.lesson}
               />
             | (Some(pr), Some(myUsername), _, _) =>
               <div>
                 <RelayPRChatHistory.PullRequestContainer
                   pullRequestId={pr##id}
                   myUsername
                 />
               </div>
             | _ => null
             }}
          </div>
        </div>
        <div className="editor-footer">
          {string(
             "Egghead editor powered by OneGraph, written in ReasonML using Relay",
           )}
        </div>
      </div>
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
  let make = (~auth, ~course) => {
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
        {switch (OneJwt.findGitHubLogin(me)) {
         | None => "Sorry, we couldn't verify your GitHub username"->string
         | Some(username) => <Editor auth jwtMe=me course onLogout username />
         }}
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
let make = (~course: EggheadData.courseWithNullableLessons) => {
  Js.log2("Course: ", course);
  let lessons =
    switch (Js.Nullable.toOption(course.lessons)) {
    | None => [||]
    | Some(lessons) => lessons
    };

  /* Protect our code from nullable lessons */
  let course: EggheadData.course = {
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
      <React.Suspense
        fallback={<div> "Gimme a second..."->React.string </div>}>
        ReasonUrql.(
          switch (Config.auth, GraphQL.urqlClient) {
          | (Some(auth), Some(client)) =>
            <Provider value=client> <LoginGuard auth course /> </Provider>
          | _ => "Loading the Egghead™ lesson editor..."->React.string
          }
        )
      </React.Suspense>
    }
  );
};

let default = make;
