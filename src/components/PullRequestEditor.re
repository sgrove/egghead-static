module ContentEditor = {
  [@react.component]
  let make = (~content, ~onChange, ~onEditorDidMount) => {
    let editorHandle = React.useRef(None);

    let _windowSize =
      Hooks.useWindowSize(size => {
        switch (editorHandle->React.Ref.current, size) {
        | (Some(editor), _) => BsReactMonaco.layout(editor)
        | _ => ()
        }
      });

    <div className="editor">
      <ReactMonacoLazy.Editor.Lazy
        className="transcript-editor"
        value=content
        height="250px"
        theme="vs-dark"
        language="markdown"
        options={
          "minimap": {
            "enabled": false,
          },
        }
        editorDidMount={(editor, _monaco) => {
          React.Ref.setCurrent(editorHandle, Some(editor));
          onEditorDidMount(~editor, ~content);
        }}
        onChange={(newValue, _event) => onChange(~value=newValue)}
      />
    </div>;
  };
};

module EditorWithData = {
  [@react.component]
  let make =
      (
        ~sourceRepo: EggheadData.repo,
        ~branch,
        ~filePath,
        ~onEditorDidMount,
        ~onChange,
      ) => {
    let query =
      LessonTranscript.GetFileShaAndContentQuery.use(
        ~variables={
          repoOwner: sourceRepo.owner,
          repoName: sourceRepo.name,
          branchAndFilePath: {j|$branch:$filePath|j},
        },
        (),
      );

    let initialContent =
      LessonTranscript.extractFileShaAndContents(query)
      ->Belt.Option.flatMap(
          (
            blob: LessonTranscript.GetFileShaAndContentQuery.Types.response_gitHub_repository_object__GitHubBlob,
          ) =>
          blob.text
        );

    let (content, setContent) = React.useState(() => initialContent);

    React.(
      switch (content) {
      | None => string({j|No transcript found for $filePath|j})
      | Some(content) =>
        <ContentEditor
          onEditorDidMount
          onChange={(~value) => {
            setContent(_ => Some(value));
            onChange(~value);
          }}
          content
        />
      }
    );
  };
};

[@react.component]
let make =
    (
      ~courseTree: React.element,
      ~sourceRepo: EggheadData.repo,
      ~course,
      ~lesson: EggheadData.lesson,
      ~onEditorDidMount,
      ~username,
      ~onChange,
      ~pullRequestId,
    ) => {
  let branch = "master"; /* Always edit master version of a lesson */
  let filePath = EggheadData.filePathOfCourseLesson(course, lesson);

  React.(
    <EditorControls
      title={
              let lessonTitle = lesson.title;
              {j|Viewing pull request for $lessonTitle|j}->string;
            }
      leftPanel=courseTree
      centerPanel={
        <React.Suspense
          fallback={<div> {j|Loading $filePath...|j}->React.string </div>}>
          <EditorWithData
            sourceRepo
            branch
            filePath
            onEditorDidMount
            onChange
          />
        </React.Suspense>
      }
      rightPanel={
        <React.Suspense fallback={""->React.string}>
          <PullRequestChatHistory myUsername=username pullRequestId />
        </React.Suspense>
      }
      footer={"Footer"->string}
    />
  );
};
