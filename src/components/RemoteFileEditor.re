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
          "selectOnLineNumbers": false,
          "wordWrap": "on",
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
    RemoteFile.Query.use(
      ~variables={
        repoOwner: sourceRepo.owner,
        repoName: sourceRepo.name,
        branchAndFilePath: {j|$branch:$filePath|j},
      },
      (),
    );

  let initialContent =
    RemoteFile.extractFileShaAndContents(query)
    ->Belt.Option.flatMap(
        (
          blob: RemoteFile.Query.Types.response_gitHub_repository_object__GitHubBlob,
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
