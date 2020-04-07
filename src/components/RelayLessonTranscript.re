module GetFileShaAndContentQuery = [%relay.query
  {|query RelayLessonTranscript_GetFileShaQuery($repoName: String!, $repoOwner: String!, $branchAndFilePath: String!) {
  gitHub {
    repository(name: $repoName, owner: $repoOwner) {
      object_: object(expression: $branchAndFilePath) {
        __typename
        ... on GitHubBlob {
          oid
          text
        }
      }
    }
  }
}|}
];

[@react.component]
let make = (~branchAndFilePath: string) => {
  open React;

  let query =
    GetFileShaAndContentQuery.use(
      ~variables={repoOwner: "sgrove", repoName: "tehila", branchAndFilePath},
      (),
    );

  switch (query) {
  | {gitHub: Some({repository: Some({object_: Some(obj)})})} =>
    switch (obj) {
    | `UnselectedUnionMember(_) => string("UnselectedUnionMember")
    | `GitHubBlob({oid: sha, text}) =>
      string(
        "Found "
        ++ sha
        ++ " with value: "
        ++ Belt.Option.getWithDefault(text, "[binary file]"),
      )
    }

  | _ => string("No such file found " ++ branchAndFilePath)
  };
};

let default = make;
