type renderer;

type props = {
  [@bs.as "data-sourcepos"]
  sourcePos: Js.Nullable.t(string),
  language: string,
  value: string,
};

type t = {
  link: props => React.element,
  blockquote: props => React.element,
  list: props => React.element,
  listItem: props => React.element,
  paragraph: props => React.element,
  strong: props => React.element,
  heading: props => React.element,
  inlineCode: props => React.element,
  code: props => React.element,
};

[@bs.module "react-markdown-github-renderers"]
external renderers: t = "default";

let text = (props): React.element => {
  Js.log2("Text Props: ", props);
  props##children /* <span> {props##children} </span> */;
};
