[@react.component]
let make =
    (
      ~course: EggheadData.course,
      ~lesson: option(EggheadData.editableLesson),
      ~onChange,
      ~onEditorDidMount,
    ) => {
  open React;

  let editorHandle = React.useRef(None);

  let _windowSize =
    Hooks.useWindowSize(size => {
      switch (editorHandle->React.Ref.current, size) {
      | (Some(editor), _) => BsReactMonaco.layout(editor)
      | _ => ()
      }
    });

  <div className="editor">
    {switch (lesson) {
     | Some(lesson) =>
       let repoOwner = "eggheadio";
       let repoName = "egghead-asciicasts";

       let branch = "master";
       let lessonSlug = lesson.slug;
       let courseSlug = EggheadData.courseSlug(course);
       let filePath = {j|$courseSlug/lessons/$lessonSlug.md|j};

       let branchAndFilePath = {j|$branch:$filePath|j};

       let query =
         RelayLessonTranscript.GetFileShaAndContentQuery.use(
           ~variables={repoOwner, repoName, branchAndFilePath},
           (),
         );

       switch (query) {
       | {gitHub: Some({repository: Some({object_: Some(obj)})})} =>
         switch (obj) {
         | `UnselectedUnionMember(_) => null
         | `GitHubBlob({sha: _sha, text}) =>
           <ReactMonacoLazy.Editor.Lazy
             className="transcript-editor"
             value={
               text->Belt.Option.getWithDefault(
                 "No transcript found for lesson",
               )
             }
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
               onEditorDidMount(~editor);
             }}
             onChange={(newValue, _event) =>
               onChange(~lessonId=lesson.id, ~value=newValue)
             }
           />
         }

       | _ => string("No such file found " ++ branchAndFilePath)
       };

     | _ => null
     }}
  </div>;
};
