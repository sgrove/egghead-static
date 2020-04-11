type editableContent = {
  text: string,
  originalSha: string,
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
          onChange={(~result) => {
            let (text, originalSha) =
              switch (result) {
              | RemoteFileEditor.Updated({text, originalSha}) => (
                  text,
                  originalSha,
                )
              | NotFound({branch, filePath}) =>
                let repoOwner = sourceRepo.owner;
                let repoName = sourceRepo.name;

                let link = {j|https://github.com/$repoOwner/$repoName/blob/$branch/$filePath|j};
                (
                  {j|No text file found at path `$filePath` on branch "`$branch`"

It should be [here]($link)|j},
                  link,
                );
              };

            setEditedText(_ => Some({text, originalSha}));
            onChange(~value=text, ~originalSha);
          }}
        />
      </React.Suspense>
    }
    rightPanel={
      <React.Suspense fallback={""->React.string}>
        {switch (editedText) {
         | Some({text: editedText, originalSha: existingSha}) =>
           <SubmitLessonPullRequest
             sourceRepo
             course
             lesson
             username
             editedText={Some(editedText)}
             existingSha
           />
         | None => React.null
         }}
      </React.Suspense>
    }
  />;
};
