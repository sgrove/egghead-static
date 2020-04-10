module GetFileShaAndContentQuery = [%relay.query
  {|query RelayLessonTranscript_GetFileShaQuery($repoName: String!, $repoOwner: String!, $branchAndFilePath: String!) {
  gitHub {
    repository(name: $repoName, owner: $repoOwner) {
      object_: object(expression: $branchAndFilePath) {
        __typename
        ... on GitHubBlob {
          # GitHub uses the object sha as its object id (oid)
          # Rename it so `sha` is used everywhere in our codebase
          sha: oid
          text
        }
      }
    }
  }
}|}
];

let extractFileShaAndContents =
    (query: GetFileShaAndContentQuery.Types.response) => {
  switch (query) {
  | {gitHub: Some({repository: Some({object_: Some(`GitHubBlob(blob))})})} =>
    Some(blob)
  | _ => None
  };
};

[@react.component]
let make = (~branchAndFilePath: string) => {
  open React;

  let query =
    GetFileShaAndContentQuery.use(
      ~variables={repoOwner: "sgrove", repoName: "tehila", branchAndFilePath},
      (),
    );

  let message =
    switch (extractFileShaAndContents(query)) {
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
