[@bs.module] [@react.component]
external make:
  (
    ~source: string,
    ~onClick: 'a => unit=?,
    ~sourcePos: bool=?,
    ~renderers: Js.t({..})=?
  ) =>
  React.element =
  "react-markdown";

module WrapRoot = {
  let wrapper = (~onClick: 'b) =>
    [@react.component]
    (
      (~value as _: React.element, ~children: 'a) =>
        <div onClick> children </div>
    );
};
