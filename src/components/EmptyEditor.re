[@react.component]
let make = (~courseTree: React.element) => {
  React.(
    <EditorControls
      title={"Eggy editor"->string}
      leftPanel=courseTree
      centerPanel=React.null
      rightPanel=null
    />
  );
};
