[@react.component]
let make = (~courseTree: React.element) => {
  React.(
    <EditorControls
      title={"Eggy editor"->string}
      leftPanel=courseTree
      centerPanel=null
      rightPanel=null
    />
  );
};
