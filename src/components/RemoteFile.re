module Query = [%relay.query
  {|query RemoteFile_GetFileShaQuery($repoName: String!, $repoOwner: String!, $branchAndFilePath: String!) {
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

let extractFileShaAndContents = (query: Query.Types.response) => {
  switch (query) {
  | {gitHub: Some({repository: Some({object_: Some(`GitHubBlob(blob))})})} =>
    Some(blob)
  | _ => None
  };
};
