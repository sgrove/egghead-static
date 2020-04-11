let sourceRepo: EggheadData.repo = {
  owner: "eggheadio",
  name: "egghead-asciicasts",
};

module ContentPreview = {
  [@bs.send]
  external getDOMAttribute: ('t, string) => Js.Nullable.t(string) =
    "getAttribute";

  /* We want our wrapping divs that capture introspection clicks to not affect
     the layout if at all possible */
  let introspectionDivStyle =
    ReactDOMRe.Style.make(~display="inline-block", ());

  let emptyStyle = ReactDOMRe.Style.make();

  [@react.component]
  let make = (~editor, ~content) => {
    [@react.component]
    let wrappedRootForIntrospectionClick = (~value) => {
      <div
        style={ReactDOMRe.Style.make(
          ~padding="20px",
          ~width="60%",
          ~backgroundColor="#fff",
          ~borderRadius="4px",
          (),
        )}
        className="markdown-content"
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
    };

    [@react.component]
    let wrapForIntrospectionClick =
        (~style=emptyStyle, elRender, props: ReactGitHubMarkdown.props) => {
      <div
        className="introspection-middleware"
        style={ReactDOMRe.Style.combine(introspectionDivStyle, style)}
        onClick={event => {
          switch (ReactEvent.Mouse.altKey(event), editor) {
          | (true, Some(editorHandle)) =>
            event->ReactEvent.Mouse.stopPropagation;
            props.sourcePos
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
        }}>
        {elRender(props)}
      </div>;
    };

    let renderers = {
      "link": wrapForIntrospectionClick(ReactGitHubMarkdown.renderers.link),
      "blockquote":
        wrapForIntrospectionClick(ReactGitHubMarkdown.renderers.blockquote),
      "list": wrapForIntrospectionClick(ReactGitHubMarkdown.renderers.list),
      "listItem":
        wrapForIntrospectionClick(ReactGitHubMarkdown.renderers.listItem),
      "paragraph":
        wrapForIntrospectionClick(ReactGitHubMarkdown.renderers.paragraph),
      "strong":
        wrapForIntrospectionClick(ReactGitHubMarkdown.renderers.strong),
      "heading":
        wrapForIntrospectionClick(ReactGitHubMarkdown.renderers.heading),
      "inlineCode":
        wrapForIntrospectionClick(ReactGitHubMarkdown.renderers.inlineCode),
      "code":
        wrapForIntrospectionClick(
          ReactGitHubMarkdown.renderers.code,
          ~style=ReactDOMRe.Style.make(~display="block", ()),
        ),
      "root": wrappedRootForIntrospectionClick,
    };

    <div style={ReactDOMRe.Style.make(~display="flex", ())}>
      <div
        className="content-left-padding"
        style={ReactDOMRe.Style.make(
          ~backgroundColor="#1e1e1e",
          ~width="20%",
          (),
        )}
      />
      <ReactMarkdown source=content sourcePos=true renderers />
      <div
        className="content-right-padding"
        style={ReactDOMRe.Style.make(
          ~backgroundColor="#1e1e1e",
          ~width="20%",
          (),
        )}
      />
    </div>;
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

    <div
      style={ReactDOMRe.Style.make(
        ~paddingBottom="550px",
        ~paddingTop="50px",
        ~backgroundColor="#1e1e1e",
        (),
      )}>
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
