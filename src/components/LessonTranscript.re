[@react.component]
let make = (~branchAndFilePath: string) => {
  open React;

  let query =
    RemoteFile.Query.use(
      ~variables={repoOwner: "sgrove", repoName: "tehila", branchAndFilePath},
      (),
    );

  let message =
    switch (RemoteFile.extractFileShaAndContents(query)) {
    | None => "No such file found " ++ branchAndFilePath
    | Some({sha, text}) =>
      "Found "
      ++ sha
      ++ " with value: "
      ++ Belt.Option.getWithDefault(text, "[binary file]")
    };

  string(message);
};

let default = make;
