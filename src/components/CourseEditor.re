let sourceRepo: EggheadData.repo = {
  owner: "eggheadio",
  name: "egghead-asciicasts",
};

module ContentPreview = {
  [@bs.send]
  external getDOMAttribute: ('t, string) => Js.Nullable.t(string) =
    "getAttribute";

  module WithIntrospectionClick = {
    [@react.component]
    let make = (~onClick, ~children) =>
      ReasonReact.cloneElement(children, ~props={"onClick": onClick}, [||]);
  };

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
        (elRender, props: ReactGitHubMarkdown.props) => {
      <WithIntrospectionClick
        onClick={event => {
          switch (ReactEvent.Mouse.altKey(event), editor) {
          | (true, Some(editorHandle)) =>
            event->ReactEvent.Mouse.stopPropagation;
            event->ReactEvent.Mouse.preventDefault;
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
      </WithIntrospectionClick>;
    };

    /* TODO: This shouldn't be necessary, but I can't get introspection-click on
       the codeblock (<pre><code></code></pre>) to work without it */
    [@react.component]
    let wrapWithDivForIntrospectionClick =
        (elRender, props: ReactGitHubMarkdown.props) => {
      <div
        onClick={event => {
          switch (ReactEvent.Mouse.altKey(event), editor) {
          | (true, Some(editorHandle)) =>
            event->ReactEvent.Mouse.stopPropagation;
            event->ReactEvent.Mouse.preventDefault;
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
        wrapWithDivForIntrospectionClick(ReactGitHubMarkdown.renderers.code),
      /* "text": wrapWithDivForIntrospectionClick(ReactGitHubMarkdown.text), */
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
        onChange={(~value, ~originalSha as _) => {
          setState(state => {...state, content: value})
        }}
      />
    </div>;
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

  let title = course.title;

  React.(
    switch (course.lessons->Belt.List.fromArray) {
    | [] => {j|No lessons found for course $title|j}->string
    | _ =>
      <React.Suspense
        fallback={<div> "One second, loading..."->React.string </div>}>
        {switch (Config.auth) {
         | Some(auth) =>
           <LoginGuard auth>
             {(username => <Eggy course username />)}
           </LoginGuard>
         | _ => <LoginGuard.StaticPlaceholder />
         }}
      </React.Suspense>
    }
  );
};

let default = make;
