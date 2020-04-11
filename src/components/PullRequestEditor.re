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
          <RemoteFileEditor
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
