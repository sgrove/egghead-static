let sourceRepo: EggheadData.repo = {
  owner: "eggheadio",
  name: "egghead-asciicasts",
};

module ContentPreview = {
  [@bs.send]
  external getDOMAttribute: ('t, string) => Js.Nullable.t(string) =
    "getAttribute";

  [@react.component]
  let make = (~editor, ~content) => {
    [@react.component]
    let wrapedMarkdownToForwardIntrospectionClick = (~value: Js.t({..})) =>
      <div
        onClick={event =>
          switch (ReactEvent.Mouse.altKey(event), editor) {
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

    <ReactMarkdown
      source=content
      sourcePos=true
      renderers={"root": wrapedMarkdownToForwardIntrospectionClick}
    />;
  };
};

module EditorContainer = {
  type viewable =
    | Nothing
    | Lesson(EggheadData.lesson)
    | PullRequest(EggheadData.lesson, string);

  type state = {viewing: viewable};

  [@react.component]
  let make =
      (
        ~course: EggheadData.course,
        ~username: string,
        ~onEditorDidMount,
        ~onChange,
      ) => {
    open React;

    let (state, setState) = useState(() => {viewing: Nothing});

    let courseTree = {
      <React.Suspense
        fallback={
          <div> "Loading lessons and pull requests..."->React.string </div>
        }>
        <CourseTree
          course
          username
          onLessonSelected={(~lessonId) => {
            let lesson =
              course.lessons
              ->Belt.Array.getBy(lesson => lesson.id == lessonId);

            let viewing =
              lesson->Belt.Option.mapWithDefault(state.viewing, lesson =>
                Lesson(lesson)
              );

            setState(_ => {viewing: viewing});
          }}
          onPullRequestSelected={(~lessonId, ~pullRequestId) => {
            let lesson =
              course.lessons
              ->Belt.Array.getBy(lesson => lesson.id == lessonId);

            let viewing =
              lesson->Belt.Option.mapWithDefault(state.viewing, lesson =>
                PullRequest(lesson, pullRequestId)
              );

            setState(_ => {viewing: viewing});
          }}
        />
      </React.Suspense>;
    };

    switch (state.viewing) {
    | Nothing => <EmptyEditor courseTree />
    | PullRequest(lesson, pullRequestId) =>
      <PullRequestEditor
        courseTree
        course
        lesson
        sourceRepo
        username
        onEditorDidMount
        onChange
        pullRequestId
      />

    | Lesson(lesson) =>
      <LessonEditor
        courseTree
        course
        lesson
        sourceRepo
        username
        onEditorDidMount
        onChange
      />
    };
  };
};

module Eggy = {
  type state('editor) = {
    content: string,
    editor: option('editor),
  };

  [@react.component]
  let make = (~course, ~username) => {
    let (state, setState) =
      React.useState(() => {content: "", editor: None});

    <div style={ReactDOMRe.Style.make(~marginBottom="250px", ())}>
      <ContentPreview editor={state.editor} content={state.content} />
      <EditorContainer
        course
        username
        onEditorDidMount={(~editor, ~content) => {
          setState(_ => {content, editor: Some(editor)})
        }}
        onChange={(~value) => {
          setState(state => {...state, content: value})
        }}
      />
    </div>;
  };
};

[@react.component]
let make = (~course: EggheadData.courseWithNullableLessons) => {
  /* Because we can't completely trust every course to have lessons, we filter out all null lessons here */
  Js.log2("Course: ", course);

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
         | Some(auth) =>
           <LoginGuard auth>
             {(username => <Eggy course username />)}
           </LoginGuard>
         | _ => "Loading the Egghead™ lesson editor..."->React.string
         }}
      </React.Suspense>
    }
  );
};

let default = make;
