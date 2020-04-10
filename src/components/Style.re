let modalStyle =
  ReactDOMRe.Style.make(
    ~position="relative",
    ~display="flex",
    ~flexDirection="column",
    ~marginTop="50%",
    (),
  );

let activeEditorStyle =
  ReactDOMRe.Style.make(
    ~minHeight="250px",
    ~position="fixed",
    ~left="0px",
    ~bottom="0px",
    ~borderRadius="4px",
    ~border="1px solid #ccc",
    ~backgroundColor="white",
    ~overflowX="scroll",
    ~boxShadow="6px 4px 24px 0px rgba(0, 0, 0, 0.34)",
    ~width="100%",
    (),
  );

let inactiveEditorStyle =
  ReactDOMRe.Style.make(
    ~minHeight="250px",
    ~position="fixed",
    ~left="0px",
    ~bottom="0px",
    ~borderRadius="4px",
    ~border="1px solid #ccc",
    ~backgroundColor="white",
    ~overflowX="scroll",
    ~opacity="0.98",
    (),
  );

let textEditorStyle =
  ReactDOMRe.Style.make(~width="100%", ~height="20ch", ~fontSize="2em", ());
