type updated = {
  text: string,
  originalSha: string,
};

type notFound = {
  branch: string,
  filePath: string,
};

type remoteFileEditorUpdated =
  | Updated(updated)
  | NotFound(notFound);

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
  let branchAndFilePath = {j|$branch:$filePath|j};

  let query =
    RemoteFile.Query.use(
      ~variables={
        repoOwner: sourceRepo.owner,
        repoName: sourceRepo.name,
        branchAndFilePath,
      },
      (),
    );

  let initialBlob = RemoteFile.extractFileShaAndContents(query);
  let initialContent = initialBlob->Belt.Option.flatMap(blob => blob.text);
  let originalSha = initialBlob->Belt.Option.map(blob => blob.sha);

  let (content, setContent) = React.useState(() => initialContent);

  React.useEffect1(
    () => {
      switch (initialContent, originalSha) {
      | (Some(text), Some(originalSha)) =>
        setContent(_ => Some(text));
        onChange(~result=Updated({text, originalSha}));
      | _ =>
        setContent(_ => None);
        onChange(~result=NotFound({branch, filePath}));
      };

      None;
    },
    [|branchAndFilePath|],
  );

  React.(
    switch (content) {
    | None => string({j|No transcript found for $filePath|j})
    | Some(content) =>
      <ContentEditor
        onEditorDidMount
        onChange={(~value) => {
          switch (originalSha) {
          | Some(originalSha) =>
            setContent(_ => Some(value));
            onChange(~result=Updated({text: value, originalSha}));
          | _ => ()
          }
        }}
        content
      />
    }
  );
};
