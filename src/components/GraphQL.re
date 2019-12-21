let urqlClient =
  switch (Config.auth) {
  | None => None
  | Some(auth) =>
    Some(
      ReasonUrql.(
        Client.make(
          ~url=Config.oneGraphUrl,
          ~fetchOptions=
            FetchFn(
              () => {
                let headers =
                  switch (OneGraphAuth.authHeaders(auth)) {
                  | None => None
                  | Some(header) =>
                    Some(Fetch.HeadersInit.make({"Authorization": header}))
                  };
                Fetch.RequestInit.make(~headers?, ());
              },
            ),
          (),
        )
      ),
    )
  };

module GetFileShaAndContentQuery = [%graphql
  {|query GetFileSha($repoName: String!, $repoOwner: String!, $branchAndFilePath: String!) {
  gitHub {
    repository(name: $repoName, owner: $repoOwner) {
      object_: object(expression: $branchAndFilePath) {
        ... on GitHubBlob {
          oid
          text
        }
      }
    }
  }
}|}
];

module CreateBranchMutation = [%graphql
  {|mutation CreateBranchMutation(
  $repoOwner: String!
  $repoName: String!
  $branchName: String!
) {
  gitHub {
    createBranch_oneGraph(
      input: {
        branchName: $branchName
        repoName: $repoName
        repoOwner: $repoOwner
      }
    ) {
      ref_: ref {
        name
        id
      }
    }
  }
}|}
];

module UpdateFileContentMutation = [%graphql
  {|mutation UpdateFileMutation(
  $repoOwner: String!
  $repoName: String!
  $branchName: String!
  $path: String!
  $message: String!
  $content: String!
  $sha: String!
) {
  gitHub {
    createOrUpdateFileContent_oneGraph(
      input: {
        message: $message
        path: $path
        repoName: $repoName
        repoOwner: $repoOwner
        branchName: $branchName
        plainContent: $content
        existingFileSha: $sha
      }
    ) {
      commit {
        message
      }
    }
  }
}|}
];

module CreatePullRequestMutation = [%graphql
  {|mutation CreatePullRequestMutation(
  $repoOwner: String!
  $repoName: String!
  $sourceBranch: String!
  $title: String!
  $body: String
  $destinationBranch: String
) {
  gitHub {
    createPullRequest_oneGraph(
      input: {
        sourceBranch: $sourceBranch
        title: $title
        repoName: $repoName
        repoOwner: $repoOwner
        body: $body
        destinationBranch: $destinationBranch
      }
    ) {
      pullRequest {
        id
        number
        title
      }
    }
  }
}|}
];

module AddLabelsToPullRequestMutation = [%graphql
  {|mutation AddLabelToPullRequestMutation(
  $labelIds: [ID!]!
  $labelableId: ID!
) {
  gitHub {
    addLabelsToLabelable(
      input: {
        labelIds: $labelIds
        labelableId: $labelableId
      }
    ) {
      clientMutationId
      labelable {
        labels {
          nodes {
            name
          }
        }
      }
    }
  }
}|}
];

module GetPRListQuery = [%graphql
  {|query GetPullRequestsQuery(
  $filterTag: [String!]
  $repoName: String!
  $repoOwner: String!
  $limit: Int!
) {
  gitHub {
    repository(name: $repoName, owner: $repoOwner) {
      pullRequests(
        orderBy: { direction: DESC, field: CREATED_AT }
        first: $limit
        states: OPEN
        labels: $filterTag
      ) {
        nodes {
          number
          id
          title
          body
          isCrossRepository
          comments(last: 20) {
            nodes {
              id
              bodyText
              author {
                login
                avatarUrl
              }
              createdAt
            }
          }
          baseRefName
          headRef {
            prefix
            name
            id
            target {
              id
              oid
              repository {
                owner {
                  login
                  id
                }
              }
            }
          }
        }
      }
    }
  }
}|}
];

module GetPRSingleFileQuery = [%graphql
  {|query GetPRSingleFileQuery(
  $repoName: String!
  $repoOwner: String!
  $branchAndFilePath: String = "master:package.json"
) {
  gitHub {
    repository(name: $repoName, owner: $repoOwner) {
      object_: object(expression: $branchAndFilePath) {
        ... on GitHubBlob {
          text
        }
      }
    }
  }
}|}
];

module MergePRMutation = [%graphql
  {|mutation MergePullRequest(
  $repoOwner: String!
  $repoName: String!
  $number: Int!
  $sha: String!
  $title: String!
) {
  gitHub {
    mergePullRequest_oneGraph(
      input: {
        repoOwner: $repoOwner
        repoName: $repoName
        number: $number
        sha: $sha
        commitTitle: $title
      }
    ) {
      pullRequest {
        id
        title
        merged
        state
      }
    }
  }
}|}
];

let exampleQuery = "repo:onegraph/oneserve [パルme] in:title:";

module SearchForPullRequestsQuery = [%graphql
  {|query SearchForPullRequests(
       $query: String!
       $last: Int!
     ) {
       gitHub {
         search(query: $query, type: ISSUE, last: $last) {
           nodes {
             ... on GitHubPullRequest {
               id
               title
               body
               state
               number
               comments(last: 100) {
                 nodes {
                   id
                   author {
                     login
                     avatarUrl
                   }
                   createdAt
                   body
                 }
               }
             }
           }
         }
       }
     }|}
];

module AddPullRequestCommentMutation = [%graphql
  {|mutation AddPullRequestCommentMutation(
  $body: String!
  $pullRequestId: ID!
) {
  gitHub {
    addComment(
      input: { body: $body, subjectId: $pullRequestId }
    ) {
      clientMutationId
    }
  }
}|}
];

let unwrapGHConn = conn =>
  Belt.Option.(
    conn
    ->flatMap(d => d##nodes)
    ->map(d =>
        Array.to_list(d)
        |> Belt.List.reduce(_, [], (acc, next) =>
             switch (next) {
             | Some(thing) => [thing, ...acc]
             | _ => acc
             }
           )
        |> Belt.List.reverse
      )
    ->getWithDefault([])
  );

let filterGHConn = (conn, filterer) =>
  Belt.Option.(
    conn
    ->flatMap(d => d##nodes)
    ->map(d =>
        Array.to_list(d)
        |> Belt.List.reduce(_, [], (acc, next) => filterer(acc, next))
        |> Belt.List.reverse
      )
    ->getWithDefault([])
  );

type result('a, 'b) =
  | Ok('a)
  | Error('b);

type mutationChainResult = result(unit, string);

let mutation =
    (~client, request: UrqlTypes.request('a), errorMessage: string) =>
  ReasonUrql.Client.executeMutation(~client, ~request, ())
  |> Wonka.toPromise
  |> Js.Promise.(
       then_(
         (
           {response}:
             ReasonUrql.Client.ClientTypes.clientResponse('response),
         ) =>
         switch (response) {
         | Data(_data) => resolve(Ok())
         | _ => resolve(Error(errorMessage))
         }
       )
     );

let chain = (mutations: list(unit => Js.Promise.t(mutationChainResult))) => {
  let rec helper = mutations =>
    Js.Promise.(
      switch (mutations) {
      | [] => resolve(Ok())
      | [mutation, ...rest] =>
        mutation()
        |> then_((a: mutationChainResult) =>
             switch (a) {
             | Ok () => helper(rest)
             | other => resolve(other)
             }
           )
      }
    );
  helper(mutations);
};
