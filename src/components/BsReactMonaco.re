type editor;

module Editor: {
  [@react.component]
  let make:
    (
      ~width: string=?,
      ~height: string=?,
      ~value: string=?,
      ~defaultValue: string=?,
      ~language: string=?,
      ~theme: string=?,
      ~options: Js.t({..})=?,
      ~overrideServices: string=?,
      ~onChange: (string, 'event) => unit=?,
      ~editorWillMount: 'monaco => unit=?,
      ~editorDidMount: (editor, 'monaco) => unit=?,
      ~className: string=?
    ) =>
    React.element;
} = {
  [@bs.module "react-monaco-editor1"] [@react.component]
  external make:
    (
      ~width: string=?,
      ~height: string=?,
      ~value: string=?,
      ~defaultValue: string=?,
      ~language: string=?,
      ~theme: string=?,
      ~options: Js.t({..})=?,
      ~overrideServices: string=?,
      ~onChange: (string, 'event) => unit=?,
      ~editorWillMount: 'monaco => unit=?,
      ~editorDidMount: (editor, 'monaco) => unit=?,
      ~className: string=?
    ) =>
    React.element =
    "default";
};

module DiffViewer: {
  [@react.component]
  let make:
    (
      ~width: string=?,
      ~height: string=?,
      ~original: string,
      ~value: string,
      ~defaultValue: string=?,
      ~language: string=?,
      ~theme: string=?,
      ~options: Js.t({..})=?,
      ~overrideServices: string=?,
      ~onChange: (string, 'event) => unit=?,
      ~editorWillMount: 'monaco => unit=?,
      ~editorDidMount: (editor, 'monaco) => unit=?,
      ~className: string=?
    ) =>
    React.element;
} = {
  [@bs.module "react-monaco-editor"] [@react.component]
  external make:
    (
      ~width: string=?,
      ~height: string=?,
      ~original: string,
      ~value: string,
      ~defaultValue: string=?,
      ~language: string=?,
      ~theme: string=?,
      ~options: Js.t({..})=?,
      ~overrideServices: string=?,
      ~onChange: (string, 'event) => unit=?,
      ~editorWillMount: 'monaco => unit=?,
      ~editorDidMount: (editor, 'monaco) => unit=?,
      ~className: string=?
    ) =>
    React.element =
    "MonacoDiffEditor";
};

[@bs.send] external layout: editor => unit = "layout";

type selection = {
  startLineNumber: int,
  startColumn: int,
  endLineNumber: int,
  endColumn: int,
};

[@bs.send] external setSelection: (editor, selection) => unit = "setSelection";

[@bs.send] external revealLine: (editor, int) => unit = "revealLine";

[@bs.send] external focus: editor => unit = "focus";
