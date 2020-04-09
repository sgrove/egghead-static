[@bs.send]
external getDOMAttribute: ('t, string) => Js.Nullable.t(string) =
  "getAttribute";

module OneGraphAuth = {
  include OneGraphAuth;
  type service =
    | Egghead
    | GitHub;
  let stringOfService = service =>
    switch (service) {
    | Egghead => "eggheadio"
    | GitHub => "github"
    };
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
  let logoutMultipleServices = (auth, services: list(service)) => {
    let promises =
      services->Belt.List.map(service => {
        let serviceName = stringOfService(service);
        OneGraphAuth.logout(auth, serviceName, ())->Promise.Js.fromBsPromise;
      });
    Promise.Js.all(promises);
  };
};

let sourceRepo: EggheadData.repo = {
  owner: "eggheadio",
  name: "egghead-asciicasts",
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

module EditorPanel = {
  type state = {editorOpen: bool};
  type action =
    | ToggleEditorPanel;
  [@react.component]
  let make =
      (
        ~myUsername,
        ~course: EggheadData.course,
        ~onEditorDidMount,
        ~onLessonSelected,
        ~onPullRequestSelected,
        ~onEditLesson,
        ~selectedPullRequest,
        ~editableLesson: option(EggheadData.editableLesson),
      ) => {
    open React;
    let (state, dispatch) =
      useReducer(
        (state, action) =>
          switch (action) {
          | ToggleEditorPanel => {editorOpen: !state.editorOpen}
          },
        {editorOpen: true},
      );
    <div id="eggy-editor-container">
      <div className="editor-title">
        <div className="lesson-title">
          {string(
             course.title ++ " by " ++ course.instructor.full_name ++ " - ",
           )}
        </div>
        <div className="spacer" />
        <div className="chat-control" />
      </div>
      <div className="editor-body">
        <RelayCourseTree
          course
          username=myUsername
          onLessonSelected
          onPullRequestSelected
        />
        <LessonEditor
          lesson=editableLesson
          course
          onChange=onEditLesson
          onEditorDidMount
        />
        <div className="chat-open">
          {switch (selectedPullRequest, editableLesson) {
           | (None, Some(editableLesson)) =>
             <RelaySubmitLessonPullRequest
               sourceRepo
               course
               editableLesson
               username=myUsername
             />
           | (Some(pullRequest), _) =>
             <div>
               <RelayPRChatHistory.PullRequestContainer
                 pullRequestId={pullRequest##id}
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
    </div>;
  };
};

let loadLesson =
    (~relayEnv, ~course, ~lesson: EggheadData.lesson, ~onComplete) => {
  let branch = "master";
  let lessonSlug = lesson.slug;
  let courseSlug = EggheadData.courseSlug(course);
  let filePath = {j|$courseSlug/lessons/$lessonSlug.md|j};
  RelayLessonTranscript.GetFileShaAndContentQuery.fetch(
    ~environment=relayEnv,
    ~variables={
      repoOwner: sourceRepo.owner,
      repoName: sourceRepo.name,
      branchAndFilePath: {j|$branch:$filePath|j},
    },
    ~onResult=result => {
    /* TODO: Handle error */
    switch (result) {
    | Ok({
        gitHub:
          Some({
            repository:
              Some({
                object_: Some(`GitHubBlob({sha, text: Some(transcript)})),
              }),
          }),
      }) =>
      let editPayload: EggheadData.editPayload = {
        transcript,
        sha,
        edited: "This is from relay!  " ++ transcript,
      };
      onComplete(Ok(editPayload));
    | _ =>
      onComplete(Error("Couldn't load lesson, or lesson does not exist"))
    }
  });
};

module Editor = {
  type loadableLesson =
    | NotLoaded(EggheadData.lesson)
    | Loading(EggheadData.lesson)
    | Loaded(EggheadData.editableLesson)
    | Error(string);
  type viewable =
    | PullRequest(string)
    | EditableLesson(loadableLesson)
    | Nothing;
  type state = {
    viewing: viewable,
    lessons: EggheadData.lessonsMap,
  };
  type action('a) =
    | EditLessonTranscript(int, string)
    | SelectLesson(int)
    | SelectPullRequest(string);
  let helper = update =>
    fun
    | Some(lesson) => Some(update(lesson))
    | None => None;
  let updateLesson = (state, id, update) => {
    let lessons = state.lessons->Belt.Map.Int.update(id, helper(update));
    {...state, lessons};
  };
  [@react.component]
  let make = (~course: EggheadData.course, ~username: string) => {
    let relayEnv = ReasonRelay.useEnvironmentFromContext();
    open React;
    let editorHandle = React.useRef(None);
    let (state, dispatch) =
      useReducer(
        (state, action) => {
          switch (action) {
          | EditLessonTranscript(id, edition) =>
            Js.log3("EditLessonTranscript", id, edition);
            /*   updateLesson( */
            /*     state, */
            /*     id, */
            /*     editableLesson => { */
            /*       let updatedLesson = { */
            /*         ...editableLesson, */
            /*         editedTranscript: edition, */
            /*       }; */
            /*       updatedLesson; */
            /*     }, */
            /* ); */
            state;
          | SelectLesson(id) =>
            Js.log2("SelectLesson", id);
            let editableLesson = Belt.Map.Int.get(state.lessons, id);
            switch (editableLesson) {
            | None =>
              Js.Console.warn2("No selectable lesson found for id", id);
              state;
            | Some(editableLesson) =>
              /* { */
              /*   ...state, */
              /*   viewing: EditableLesson(Loaded(editableLesson)), */
              /* } */

              state
            };
          | SelectPullRequest(pullRequestId) =>
            Js.log2("SelectPullRequest", pullRequestId);
            {...state, viewing: PullRequest(pullRequestId)};
          }
        },
        {
          let lessons: EggheadData.lessonsMap =
            course.lessons
            ->Belt.Array.map(lesson
                /* TODO: Change title to transcript */
                => (lesson.id, lesson))
            ->Belt.Map.Int.fromArray;
          {viewing: Nothing, lessons};
        },
      );
    useEffect1(
      () => {
        switch (state.viewing) {
        | EditableLesson(NotLoaded(lesson)) =>
          Js.log2("Lesson Id: ", lesson.id);
          let branch = "master";
          let lessonSlug = lesson.slug;
          let courseSlug = EggheadData.courseSlug(course);
          let filePath = {j|$courseSlug/lessons/$lessonSlug.md|j};
          loadLesson(~relayEnv, ~course, ~lesson, ~onComplete=result =>
            Js.log3("Loading lesson result: ", lesson, result)
          );
        | _ => ()
        };
        None;
      },
      [|state.viewing|],
    );
    [@react.component]
    let wrapedMarkdownToForwardIntrospectionClick = (~value: Js.t({..})) =>
      <div
        onClick={event =>
          switch (
            ReactEvent.Mouse.altKey(event),
            editorHandle->React.Ref.current,
          ) {
          | (true, Some(editorHandle)) =>
            let target = ReactEvent.Mouse.target(event);
            getDOMAttribute(target, "data-sourcepos")
            ->Utils.extractSourcePosition
            ->Belt.Option.forEach(((from, to_)) => {
                /* Lots of imperative calls to set the Monaco editor state */
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
              });
          | _ => ()
          }
        }>
        {value##children}
      </div>;
    <div>
      <div style={ReactDOMRe.Style.make(~marginBottom="250px", ())}>
        /* Add margin here so the bottom isn't cut off by the editor container */

          {switch (state.viewing) {
           | EditableLesson(viewable) =>
             let source =
               switch (viewable) {
               | Loaded(editableLesson) =>
                 editableLesson.editedTranscript ++ "Ahhhh"
               | NotLoaded(lesson)
               | Loading(lesson) =>
                 let title = lesson.title;
                 {j|## Loading "$title" for editing...|j};
               | Error(message) => message ++ "Err"
               };
             <ReactMarkdown
               source
               sourcePos=true
               renderers={"root": wrapedMarkdownToForwardIntrospectionClick}
             />;
           | PullRequest(_lesson) => "Can't render PRs yet"->string
           | Nothing => "No lesson selected"->string
           }}
        </div>
      <EditorPanel
        myUsername=username
        course
        onEditorDidMount={(~editor) => {
          React.Ref.setCurrent(editorHandle, Some(editor))
        }}
        onLessonSelected={(~lessonId) => {dispatch(SelectLesson(lessonId))}}
        onPullRequestSelected={(~lessonId as _, ~pullRequestId) => {
          dispatch(SelectPullRequest(pullRequestId))
        }}
        onEditLesson={(~lessonId, ~value) => {
          dispatch(EditLessonTranscript(lessonId, value))
        }}
        selectedPullRequest=None
        editableLesson=None
      />
    </div>;
  };
};

let amILoggedInto = (auth, ~service, ~ifYes=?, ~ifNo=?, ()) => {
  OneGraphAuth.isLoggedIn(auth, service)
  ->Js.Promise.then_(
      isLoggedIn =>
        {
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
    | SetAuthState(OneGraphAuth.service, authState);
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
    let loginIcon = service => {
      let (serviceName, friendlyName, state) =
        switch ((service: OneGraphAuth.service)) {
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
         | Some(username) => <Editor course username />
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
  /* Because we can't completely trust every course to have lessons, we filter out all null lessons here */
  let lessons =
    switch (Js.Nullable.toOption(course.lessons)) {
    | None => [||]
    | Some(lessons) => lessons
    };
  /* We then create an EggheadData.course (as opposed to a
     EggheadData.courseWithNullableLessons) so that the rest of our code doesn't
     have to deal with nullable lessons. It's now incumbent on our data
     providers to have clean, well-formed data */
  let course: EggheadData.course = {
    description: course.description,
    instructor: course.instructor,
    published_at: course.published_at,
    rating_count: course.rating_count,
    rating_out_of_5: course.rating_out_of_5,
    square_cover_480_url: course.square_cover_480_url,
    summary: course.summary,
    title: course.title,
    lessons,
  };
  React.(
    switch (course.lessons->Belt.List.fromArray) {
    | [] => "No lessons"->string
    | _ =>
      <React.Suspense
        fallback={<div> "One second, loading..."->React.string </div>}>
        {switch (Config.auth) {
         | Some(auth) => <LoginGuard auth course />
         | _ => "Loading the Egghead™ lesson editor..."->React.string
         }}
      </React.Suspense>
    }
  );
};

let default = make;
