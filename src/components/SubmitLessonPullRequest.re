// reason-promise doesn't ship with native support for our let%Promise usage, so we simply
// add our own by re-defining the module, including all the stuff from the
// original module, and adding our own function.
module Promise = {
  include Promise;
  let let_ = Promise.flatMap;

  // This is totally optional. It can be nice sometimes to return a
  // non-promise value at the end of a function and have it automatically
  // wrapped. See example inside the Some branch of the switch below.
  module Wrap = {
    let let_ = Promise.map;
  };
};

module Result = {
  let errorEffect = (result, handler) =>
    switch (result) {
    | Ok(_) => ()
    | Error(err) => handler(err)
    };

  let let_ = Belt.Result.flatMap;

  module Wrap = {
    let let_ = Belt.Result.map;
  };
};

module FindSourceRepositoryIdQuery = [%relay.query
  {|
     query SubmitLessonPullRequest_FindSourceRepositoryIdQuery($repoOwner: String!, $repoName: String!) {
       gitHub {
         repository(owner: $repoOwner, name: $repoName) {
           id
         }
       }
     }
     |}
];

module ForkGitHubRepoMutation = [%relay.mutation
  {|mutation SubmitLessonPullRequest_ForkGitHubRepoMutation($repoOwner: String!, $repoName: String!) {
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
     query SubmitLessonPullRequest_DoIHaveARepoQuery($repoOwner: String!, $repoName: String!) {
       gitHub {
         repository(owner: $repoOwner, name: $repoName) {
           id
         }
       }
     }
     |}
];

module CreateBranchMutation = [%relay.mutation
  {|mutation SubmitLessonPullRequest_CreateBranchMutation(
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
  {|mutation SubmitLessonPullRequest_UpdateFileMutation(
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
mutation SubmitLessonPullRequest_CreatePullRequestMutation(
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
  {|mutation SubmitLessonPullRequest_AddLabelToPullRequestMutation(
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

type eggheadMeta = {
  lessonId: int,
  filePath: string,
  username: string,
};

type relayResult('a) =
  Promise.t(result('a, array(ReasonRelay.mutationError)));

let fetchFileShaAndContent =
    (~relayEnv, ~repo: EggheadData.repo, ~branchAndFilePath) => {
  let {owner: repoOwner, name: repoName}: EggheadData.repo = repo;

  let (
    sourceRepoFileShaPromise:
      relayResult(
        RemoteFile.Query.Types.response_gitHub_repository_object__GitHubBlob,
      ),
    resolveSourceRepoFileShaPromise,
  ) =
    Promise.pending();

  /* Get file sha in source repo */
  RemoteFile.Query.fetch(
    ~environment=relayEnv,
    ~variables={repoOwner, repoName, branchAndFilePath},
    ~onResult=result => {
    switch (result) {
    | Ok(query) =>
      switch (RemoteFile.extractFileShaAndContents(query)) {
      | None =>
        resolveSourceRepoFileShaPromise(
          Error([|{message: "File doesn't exist in source repository"}|]),
        )
      | Some(blob) => resolveSourceRepoFileShaPromise(Ok(blob))
      }

    | Error(_error) =>
      resolveSourceRepoFileShaPromise(
        Error([|{message: "Error finding file sha in source repo"}|]),
      )
    }
  });

  sourceRepoFileShaPromise;
};

let forkRepository = (~relayEnv, ~needsFork, ~repoOwner, ~repoName) => {
  let (forkPromise: relayResult(unit), resolveForkPromise) =
    Promise.pending();

  switch (needsFork) {
  | false => resolveForkPromise(Ok())
  | true =>
    let _ =
      ForkGitHubRepoMutation.commitMutation(
        ~environment=relayEnv,
        ~variables={repoOwner, repoName},
        ~onCompleted=
          (data, errors) => {
            let result =
              switch (data, errors) {
              | (Some(_data), None) => Ok()
              | (_, Some(errors)) => Error(errors)
              | _ => Error([|{message: "Unrecognized return value"}|])
              };
            resolveForkPromise(result);
          },
        (),
      );
    ();
  };

  forkPromise;
};

let syncTargetFileAcrossRepositories =
    (
      ~relayEnv,
      ~sourceRepo: EggheadData.repo,
      ~forkedRepo: EggheadData.repo,
      ~masterFilePath,
      ~branchFilePath,
      ~filePath,
    ) => {
  let sourceRepositoryBlobPromise =
    fetchFileShaAndContent(
      ~relayEnv,
      ~repo=sourceRepo,
      ~branchAndFilePath=masterFilePath,
    );

  let forkedRepositoryBlobPromise =
    fetchFileShaAndContent(
      ~relayEnv,
      ~repo=forkedRepo,
      ~branchAndFilePath=branchFilePath,
    );

  let%Promise.Wrap (sourceRepositoryBlobResult, forkedRepositoryBlobResult) =
    Promise.all2(sourceRepositoryBlobPromise, forkedRepositoryBlobPromise);

  let (
    refreshForkedFilePromise: relayResult(unit),
    resolveRefreshForkedFilePromise,
  ) =
    Promise.pending();

  switch (sourceRepositoryBlobResult) {
  | Error(err) => resolveRefreshForkedFilePromise(Error(err))
  | Ok(sourceRepositoryBlob) =>
    let forkedFileSha: option(string) =
      switch (forkedRepositoryBlobResult) {
      | Ok({sha}) => Some(sha)
      | _ => None
      };

    let forkedFileMustBeRefreshed: bool =
      switch (forkedFileSha) {
      | Some(sha) => sha !== sourceRepositoryBlob.sha
      | None => true
      };

    switch (forkedFileMustBeRefreshed) {
    | false => resolveRefreshForkedFilePromise(Ok())
    | true =>
      let _ =
        UpdateFileContentMutation.commitMutation(
          ~environment=relayEnv,
          ~variables={
            repoOwner: forkedRepo.owner,
            repoName: forkedRepo.name,
            branchName: "master",
            path: filePath,
            message: "Syncing forked file contents",
            content:
              sourceRepositoryBlob.text->Belt.Option.getWithDefault(""),
            sha: forkedFileSha->Belt.Option.getWithDefault(""),
          },
          ~onCompleted=
            (data, errors) => {
              let result =
                switch (data, errors) {
                | (Some(_data), None) => Ok()
                | (_, Some(errors)) => Error(errors)
                | _ => Error([|{message: "Unrecognized return value"}|])
                };
              resolveRefreshForkedFilePromise(result);
            },
          (),
        );
      ();
    };
  };
  refreshForkedFilePromise;
};

let createBranch = (~relayEnv, ~username, ~repoName, ~branchName) => {
  let (createBranchPromise: relayResult(unit), resolveCreateBranchPromise) =
    Promise.pending();

  let disposable: ReasonRelay.Disposable.t =
    CreateBranchMutation.commitMutation(
      ~environment=relayEnv,
      ~variables={repoOwner: username, repoName, branchName},
      ~onCompleted=
        (data, errors) => {
          let result =
            switch (data, errors) {
            | (Some(_data), None) => Ok()
            | (_, Some(errors)) => Error(errors)
            | _ => Error([|{message: "Unrecognized return value"}|])
            };
          resolveCreateBranchPromise(result);
        },
      (),
    );

  disposable->ignore;

  createBranchPromise;
};

let commitLessonFileChange =
    (
      ~relayEnv,
      ~forkedRepo: EggheadData.repo,
      ~branchName,
      ~filePath,
      ~commitMessage,
      ~content,
      ~existingFileSha,
    ) => {
  let (
    commitLessonFileChangePromise: relayResult(unit),
    resolveCommitLessonFileChangePromise,
  ) =
    Promise.pending();

  let disposable: ReasonRelay.Disposable.t =
    UpdateFileContentMutation.commitMutation(
      ~environment=relayEnv,
      ~variables={
        repoOwner: forkedRepo.owner,
        repoName: forkedRepo.name,
        branchName,
        path: filePath,
        message: commitMessage,
        content,
        sha: existingFileSha,
      },
      ~onCompleted=
        (data, errors) => {
          let result =
            switch (data, errors) {
            | (Some(_data), None) => Ok()
            | (_, Some(errors)) => Error(errors)
            | _ => Error([|{message: "Unrecognized return value"}|])
            };
          resolveCommitLessonFileChangePromise(result);
        },
      (),
    );

  disposable->ignore;

  commitLessonFileChangePromise;
};

let createPullRequest =
    (~relayEnv, ~repoId, ~title, ~headRefName, ~baseRefName, ~body) => {
  let (
    createPullRequestPromise:
      relayResult(CreatePullRequestMutation.Types.response),
    resolveCreatePullRequestPromise,
  ) =
    Promise.pending();

  let disposable: ReasonRelay.Disposable.t =
    CreatePullRequestMutation.commitMutation(
      ~environment=relayEnv,
      ~variables={repoId, title, headRefName, baseRefName, body},
      ~onCompleted=
        (data, errors) => {
          let result =
            switch (data, errors) {
            | (Some(data), None) => Ok(data)
            | (_, Some(errors)) => Error(errors)
            | _ => Error([|{message: "Unrecognized return value"}|])
            };
          resolveCreatePullRequestPromise(result);
        },
      (),
    );

  disposable->ignore;

  createPullRequestPromise;
};

type status =
  | Idle
  | InProgress(React.element)
  | Finished(React.element);

let displayInlineStyle =
  ReactDOMRe.Style.make(
    ~display="inline",
    /* Seriously, I suck at css */
    ~float="left",
    (),
  );

let statusEl = (status: status) =>
  switch (status) {
  | Idle => React.null
  | InProgress(message) =>
    <div>
      <LoadingSpinner width="50px" height="50px" style=displayInlineStyle />
      message
    </div>
  | Finished(message) => <> message </>
  };

let submitPullRequest =
    (
      ~relayEnv,
      ~branchName,
      ~username,
      ~userSubmittedTitle,
      ~userSubmittedBody,
      ~editedContent,
      ~filePath,
      ~lessonId,
      ~sourceRepositoryId,
      ~needsFork,
      ~existingFileSha,
      ~sourceRepo: EggheadData.repo,
      ~setStatus,
    ) => {
  /*
   1. DoIHaveARepoQuery
   1a. Fork source repo
   2. GetFileShaQuery in our fork
   2a. GetFileShaQuery in source repo
   3. CreateBranchMutation
   4. UpdateFileContentMutation - set to same as source repo
   6. UpdateFileContentMutation - set to new value
   7. CreatePullRequestMutation
   */

  let setIfError = (result, message) => {
    result->Result.errorEffect(error => {
      Js.Console.warn3("Failed to submit pull request: ", message, error);

      setStatus(_ => Finished(message));
    });
  };

  let setStatus = (~inProgress=true, message) => {
    let finished = !inProgress;
    Js.Console.info2(message, {j| - finished? $finished|j});
    setStatus(_ => inProgress ? InProgress(message) : Finished(message));
  };

  let eggheadMeta = {lessonId, filePath, username};

  let forkedRepo = {...sourceRepo, owner: username};

  let masterFilePath = {j|master:$filePath|j};
  let branchFilePath = {j|$branchName:$filePath|j};

  let headRefName = {j|$username:$branchName|j};
  let baseRefName = "master";

  let pullRequestTitle = {j|$userSubmittedTitle [by $username]|j};

  let pullRequestBody = {
    let eggheadMetaText = EggheadMarkdownMeta.toString(eggheadMeta);

    {j|$userSubmittedBody

$eggheadMetaText|j};
  };

  let nameWithOwner = {
    let {owner, name}: EggheadData.repo = sourceRepo;
    {j|$owner/$name|j};
  };

  setStatus("Forking source repository..."->React.string);

  let%Promise.Wrap result: relayResult(unit) =
    forkRepository(
      ~relayEnv,
      ~needsFork,
      ~repoOwner=sourceRepo.owner,
      ~repoName=sourceRepo.name,
    );

  result->setIfError(
    {j|Failed to fork GitHub repo $nameWithOwner|j}->React.string,
  );

  let%Result.Wrap () = result;

  setStatus("Creating new branch..."->React.string);

  let%Promise.Wrap createBranchResult =
    createBranch(
      ~relayEnv,
      ~username,
      ~repoName=forkedRepo.name,
      ~branchName,
    );

  createBranchResult->setIfError(
    <>
      {j|Failed to create branch |j}->React.string
      <code> branchName->React.string </code>
    </>,
  );

  let%Result.Wrap () = createBranchResult;

  setStatus("Syncing lesson file..."->React.string);

  /* At this point, we should have a repo fork */
  let%Promise.Wrap syncResult =
    syncTargetFileAcrossRepositories(
      ~relayEnv,
      ~sourceRepo,
      ~forkedRepo,
      ~masterFilePath,
      ~branchFilePath,
      ~filePath,
    );

  let%Promise.Wrap syncResult = syncResult;

  syncResult->setIfError({j|Failed to sync lesson file|j}->React.string);

  let%Result.Wrap () = syncResult;

  setStatus("Committing lesson changes to Github..."->React.string);

  let%Promise.Wrap commitResult =
    commitLessonFileChange(
      ~relayEnv,
      ~forkedRepo,
      ~branchName,
      ~filePath,
      ~commitMessage=userSubmittedBody,
      ~content=editedContent,
      ~existingFileSha,
    );

  commitResult->setIfError(
    {j|Failed to commit changes to Github|j}->React.string,
  );

  let%Result.Wrap () = commitResult;

  setStatus("Creating pull request..."->React.string);

  let%Promise.Wrap createPullRequestResult =
    createPullRequest(
      ~relayEnv,
      ~repoId=sourceRepositoryId,
      ~title=pullRequestTitle,
      ~headRefName,
      ~baseRefName,
      ~body=pullRequestBody,
    );

  createPullRequestResult->setIfError(
    {j|Failed to create pull request|j}->React.string,
  );

  let%Result.Wrap createPullRequestData = createPullRequestResult;

  let message =
    switch (createPullRequestData) {
    | {
        gitHub:
          Some({
            createPullRequest:
              Some({
                pullRequest:
                  Some(
                    (
                      pullRequest: CreatePullRequestMutation.Types.response_gitHub_createPullRequest_pullRequest
                    ),
                  ),
              }),
          }),
      } =>
      open React;
      let number = pullRequest.number->string_of_int;
      <>
        "Submitted lesson change! "->string
        <a href={pullRequest.url} target="_blank">
          {j|#$number⤴|j}->string
        </a>
      </>;
    | _ =>
      "Submitted change, but unable to find resulting pull request number. Please check on Github to confirm the pull request was submitted successfully."
      ->React.string
    };

  setStatus(~inProgress=false, message);
};

[@react.component]
let make =
    (
      ~course: EggheadData.course,
      ~sourceRepo: EggheadData.repo,
      ~lesson: EggheadData.lesson,
      ~editedText,
      ~existingSha,
      ~username,
    ) => {
  let existingFileSha = existingSha;
  let filePath = EggheadData.filePathOfCourseLesson(course, lesson);

  let doIHaveARepoQuery =
    DoIHaveARepoQuery.use(
      ~variables={repoOwner: username, repoName: sourceRepo.name},
      (),
    );

  let sourceRepositoryIdQuery =
    FindSourceRepositoryIdQuery.use(
      ~variables={repoOwner: sourceRepo.owner, repoName: sourceRepo.name},
      (),
    );

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

  let (status, setStatus) = React.useState(() => Idle);

  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | SetTitle(title) => {...state, title}
        | SetBody(body) => {...state, body}
        },
      {title: "", body: ""},
    );

  let relayEnv = ReasonRelay.useEnvironmentFromContext();

  React.(
    switch (sourceRepositoryId, editedText) {
    | (None, _) => "Couldn't find source repository id"->string
    | (Some(sourceRepositoryId), editedText) =>
      let disabled =
        switch (editedText, status) {
        | (None, _)
        | (_, InProgress(_)) => true
        | (_, Idle)
        | (_, Finished(_)) => false
        };

      <div>
        <form
          disabled
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
            disabled
            onChange={event =>
              dispatch(SetTitle(ReactEvent.Form.target(event)##value))
            }
            value={state.title}
          />
          <h4> {string("What did you change?")} </h4>
          <textarea
            disabled
            onChange={event =>
              dispatch(SetBody(ReactEvent.Form.target(event)##value))
            }
            value={state.body}
          />
          <button
            disabled
            onClick={event => {
              event->ReactEvent.Mouse.stopPropagation;
              event->ReactEvent.Mouse.preventDefault;

              editedText
              ->Belt.Option.map(editedText => {
                  Js.Console.info("Submitting...");

                  submitPullRequest(
                    ~relayEnv,
                    ~branchName=
                      Utils.String.toBranchName(state.title, username),
                    ~username,
                    ~userSubmittedTitle=state.title,
                    ~userSubmittedBody=state.body,
                    ~editedContent=editedText,
                    ~filePath,
                    ~lessonId,
                    ~sourceRepositoryId,
                    ~existingFileSha,
                    ~needsFork,
                    ~sourceRepo,
                    ~setStatus,
                  );
                })
              ->ignore;
            }}>
            {let buttonLabel =
               needsFork
                 ? "Fork Egghead repo and submit pull request"
                 : "Submit pull request";
             string(buttonLabel)}
          </button>
          <div> status->statusEl </div>
        </form>
      </div>;
    }
  );
};
