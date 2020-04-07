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

module FindSourceRepositoryIdQuery = [%graphql
  {|
     query FindSourceRepositoryIdQuery($repoOwner: String!, $repoName: String!) {
       gitHub {
         repository(owner: $repoOwner, name: $repoName) {
           id
         }
       }
     }
     |}
];

module ForkGitHubRepoMutation = [%graphql
  {|mutation ForkGitHubRepoMutation($repoOwner: String!, $repoName: String!) {
    gitHub {
      createFork_oneGraph(input: {repoOwner: $repoOwner, repoName: $repoName}) {
        repository {
          nameWithOwner
        }
      }
    }
  }
|}
];

module DoIHaveARepoQuery = [%graphql
  {|
     query DoIHaveARepoQuery($repoOwner: String!, $repoName: String!) {
       gitHub {
         repository(owner: $repoOwner, name: $repoName) {
           id
         }
       }
     }
     |}
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
  {|
mutation CreatePullRequestMutation(
  $repoId: ID!
  $title: String!
  $headRefName: String!
  $baseRefName: String!
  $body: String!
) {
  gitHub {
    createPullRequest(
      input: {
        title: $title
        headRefName: $headRefName
        baseRefName: $baseRefName
        repositoryId: $repoId
        maintainerCanModify: true
        body: $body
      }
    ) {
      pullRequest {
        url
        id
        number
        title
        permalink
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

let exampleQuery = {j|"repo:onegraph/oneserve [パルme] in:title:"|j};

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

type mutationChainResult = result(unit, string);

let mutation =
    (~client, request: UrqlTypes.request('a), errorMessage: string) => {
  let (p, resolve) = Promise.pending();

  ReasonUrql.Client.executeMutation(~client, ~request, ())
  ->Wonka.toPromise
  ->Promise.Js.fromBsPromise
  ->Promise.Js.get(
      ({response}: ReasonUrql.Client.ClientTypes.clientResponse('response)) =>
      switch (response) {
      | Data(_data) => resolve(Ok())
      | _ => resolve(Error(errorMessage))
      }
    );

  p;
};

let query =
    (
      ~client,
      ~request,
      ~cachePolicy: UrqlTypes.requestPolicy=`CacheAndNetwork,
      (),
    ) => {
  let (p, resolve) = Promise.pending();
  let opts =
    ReasonUrql.Client.ClientTypes.partialOperationContext(
      ~partialOpRequestPolicy=cachePolicy,
      (),
    );

  ReasonUrql.Client.executeQuery(~client, ~request, ~opts, ())
  |> Wonka.subscribe((. data) => resolve(Ok(data)))
  |> ignore;

  p;
};

let chain = (mutations: list(unit => Promise.t(mutationChainResult))) => {
  let rec helper = mutations =>
    switch (mutations) {
    | [] => Promise.resolved(Ok())
    | [mutation, ...rest] =>
      mutation()
      ->Promise.flatMap(a =>
          switch (a) {
          | Ok () => helper(rest)
          | Error(err) => Promise.resolved(Error(err))
          }
        )
    };
  helper(mutations);
};
