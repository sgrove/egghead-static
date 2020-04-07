[@bs.module "react-animated-tree"] [@react.component]
external make:
  (
    ~content: React.element,
    ~_type: React.element=?,
    ~_open: bool=?,
    ~canHide: bool=?,
    ~visible: bool=?,
    ~onClick: ReactEvent.Mouse.t => unit=?,
    ~children: 'children=?
  ) =>
  React.element =
  "default";
