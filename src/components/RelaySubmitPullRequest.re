module FindSourceRepositoryIdQuery = [%relay.query
  {|
     query RelaySubmitPullRequest_FindSourceRepositoryIdQuery($repoOwner: String!, $repoName: String!) {
       gitHub {
         repository(owner: $repoOwner, name: $repoName) {
           id
         }
       }
     }
     |}
];

module ForkGitHubRepoMutation = [%relay.mutation
  {|mutation RelaySubmitPullRequest_ForkGitHubRepoMutation($repoOwner: String!, $repoName: String!) {
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

module DoIHaveARepoQuery = [%relay.query
  {|
     query RelaySubmitPullRequest_DoIHaveARepoQuery($repoOwner: String!, $repoName: String!) {
       gitHub {
         repository(owner: $repoOwner, name: $repoName) {
           id
         }
       }
     }
     |}
];

module CreateBranchMutation = [%relay.mutation
  {|mutation RelaySubmitPullRequest_CreateBranchMutation(
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

module UpdateFileContentMutation = [%relay.mutation
  {|mutation RelaySubmitPullRequest_UpdateFileMutation(
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

module CreatePullRequestMutation = [%relay.mutation
  {|
mutation RelaySubmitPullRequest_CreatePullRequestMutation(
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

module AddLabelsToPullRequestMutation = [%relay.mutation
  {|mutation RelaySubmitPullRequest_AddLabelToPullRequestMutation(
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
             __typename
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

type action =
  | SetTitle(string)
  | SetBody(string);

type state = {
  title: string,
  body: string,
};

type frontMatter = {
  lessonId: int,
  filePath: string,
  username: string,
  sha: string,
};

[@react.component]
let make =
    (
      ~lesson: EggheadData.lesson,
      ~repoOwner,
      ~repoName,
      ~editedText,
      ~sha,
      ~filePath,
      ~username,
    ) => {
  let (forkGitHubRepo, _isForkGitHubRepo) = ForkGitHubRepoMutation.use();
  let (createBranch, _isCreateBranch) = CreateBranchMutation.use();
  let (updateFileContent, _isUpdateFileContent) =
    UpdateFileContentMutation.use();
  let (createPullRequest, _isCreatePullRequest) =
    CreatePullRequestMutation.use();
  let (addLabelsToPullRequest, _isAddLabelsToPullRequest) =
    AddLabelsToPullRequestMutation.use();

  let doIHaveARepoQuery =
    DoIHaveARepoQuery.use(~variables={repoOwner, repoName}, ());

  let sourceRepositoryIdQuery =
    FindSourceRepositoryIdQuery.use(~variables={repoOwner, repoName}, ());

  let needsFork =
    switch (doIHaveARepoQuery) {
    | {gitHub: Some({repository: Some({id: _id})})} => false
    | _ => true
    };

  let sourceRepositoryId =
    switch (sourceRepositoryIdQuery) {
    | {gitHub: Some({repository: Some({id})})} => Some(id)
    | _ => None
    };

  let lessonId = lesson.id;

  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | SetTitle(title) => {...state, title}
        | SetBody(body) => {...state, body}
        },
      {title: "", body: ""},
    );

  let submitPullRequest =
      (
        ~client,
        ~branchName,
        ~username,
        ~title,
        ~body,
        ~editedContent,
        ~sha,
        ~filePath,
        ~frontMatter,
      ) => {
    /*
     1. DoIHaveARepoQuery
     1a. Fork source repo
     1. GetFileShaQuery in our fork
     2. GetFileShaQuery in source repo
     2. CreateBranchMutation
     3. UpdateFileContentMutation - set to same as source repo
     4. UpdateFileContentMutation - set to new value
     4. CreatePullRequestMutation
     5. AddLabelsToPullRequestMutation
     */

    let masterFilePath = {j|master:$filePath|j};
    let branchFilePath = {j|$branchName:$filePath|j};

    ();
  };

  React.(
    <div
      style={ReactDOMRe.Style.make(
        ~flex="0 0 auto",
        ~display="flex",
        ~flexWrap="nowrap",
        ~flexDirection="column",
        ~justifyContent="flex-start",
        ~alignItems="stretch",
        ~alignContent="stretch",
        (),
      )}>
      <h4> {string("Title of your change")} </h4>
      <input
        type_="text"
        onChange={event =>
          dispatch(SetTitle(ReactEvent.Form.target(event)##value))
        }
        value={state.title}
      />
      <h4> {string("What did you change?")} </h4>
      <textarea
        onChange={event =>
          dispatch(SetBody(ReactEvent.Form.target(event)##value))
        }
        value={state.body}
      />
      <button
        onClick={_ => {
          let frontMatter = {lessonId, filePath, sha, username};
          Js.log("Submitting...");
          let result =
            submitPullRequest(
              ~branchName=Utils.String.toBranchName(state.title, username),
              ~username,
              ~title=state.title,
              ~body=state.body,
              ~editedContent=editedText,
              ~sha,
              ~filePath,
              ~frontMatter,
            );

          Js.log2("SubmitPromise...", result);
        }}>
        /* submitPromise */
        /* ->Promise.map((result: GraphQL.mutationChainResult) => { */
        /*     ( */
        /*       switch (result) { */
        /*       | Ok () => Js.log("Ok, PR created!") */
        /*       | Error(message) => Js.log2("Error creating PR: ", message) */
        /*       } */
        /*     ) */
        /*     ->Js.Promise.resolve */
        /*   }) */
        /* ->ignore; */

          {string((needsFork ? "Fork Repo and s" : "S") ++ "ubmit PR")}
        </button>
    </div>
  );
};
