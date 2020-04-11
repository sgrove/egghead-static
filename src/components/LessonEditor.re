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
    ) => {
  let branch = "master"; /* Always edit master version of a lesson */
  let filePath = EggheadData.filePathOfCourseLesson(course, lesson);
  open React;

  let (editedText, setEditedText) = useState(() => None);

  <EditorControls
    title={
            let title = lesson.title;
            {j|Editing "$title"|j}->string;
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
          onChange={(~value) => {
            setEditedText(_ => Some(value));
            onChange(~value);
          }}
        />
      </React.Suspense>
    }
    rightPanel={
      <React.Suspense fallback={""->React.string}>
        <SubmitLessonPullRequest
          sourceRepo
          course
          lesson
          username
          editedText
          existingSha="x"
        />
      </React.Suspense>
    }
  />;
};
