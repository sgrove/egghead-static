[@react.component]
let make = (~title, ~leftPanel, ~centerPanel, ~rightPanel, ~footer=?) => {
  <div id="eggy-editor-container">
    <div className="editor-title">
      <div className="lesson-title"> title </div>
      <div className="spacer" />
      <div className="chat-control" />
    </div>
    <div className="editor-body">
      <div className="tree"> leftPanel </div>
      <div className="editor"> centerPanel </div>
      <div className="chat-open"> rightPanel </div>
    </div>
    <div className="editor-footer">
      {footer->Belt.Option.getWithDefault(React.null)}
    </div>
  </div>;
};
