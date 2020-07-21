module PullRequestEditorActivitySubscription = [%relay.subscription
  {|
  subscription PullRequestEditor_CommentActivitySubscription(
    $repoName: String!
    $repoOwner: String!
  ) {
    github {
      issueCommentEvent(input: { repoOwner: $repoOwner, repoName: $repoName }) {
        action
        comment {
          id
          ...PullRequestChatHistory_CommentFragment
        }
      }
    }
  }
|}
];

[@react.component]
let make =
    (
      ~courseTree: React.element,
      ~sourceRepo: EggheadData.repo,
      ~course,
      ~lesson: EggheadData.lesson,
      ~onEditorDidMount,
      ~username,
      ~pullRequestId,
    ) => {
  let branch = "master"; /* Always edit master version of a lesson */
  let filePath = EggheadData.filePathOfCourseLesson(course, lesson);

  let relayEnv = ReasonRelay.useEnvironmentFromContext();

  React.useEffect0(() => {
    let disposable: ReasonRelay.Disposable.t =
      PullRequestEditorActivitySubscription.subscribe(
        ~environment=relayEnv,
        ~variables={repoOwner: sourceRepo.owner, repoName: sourceRepo.name},
        ~updater=
          (store, response) => {
            let extractNewCommentId =
                (
                  response: PullRequestEditorActivitySubscription.Types.response,
                ) => {
              switch (response) {
              | {github: {issueCommentEvent: {comment: Some({id})}}} =>
                Some(id)
              | _ => None
              };
            };

            ReasonRelay.(
              switch (extractNewCommentId(response)) {
              | Some(id) =>
                switch (
                  store->RecordSourceSelectorProxy.get(~dataId=id->makeDataId)
                ) {
                | None => ()
                | Some(node) =>
                  let insertAt: ReasonRelayUtils.insertAt = Start;
                  ReasonRelayUtils.createAndAddEdgeToConnections(
                    ~store,
                    ~node,
                    ~connections=[
                      {
                        key: "PullRequestChatHistory_PullRequestFragment_comments",
                        parentID: pullRequestId->makeDataId,
                        filters: None,
                      },
                    ],
                    ~edgeName="GitHubIssueEdge",
                    ~insertAt,
                  );
                }
              | None => Js.Console.warn("Could not find node id")
              }
            );
          },
        (),
      );

    /* Clean up/dispose of the subscription if we're unmounted */
    Some(() => disposable |> ReasonRelay.Disposable.dispose);
  });

  React.(
    <EditorControls
      title={
              let lessonTitle = lesson.title;
              {j|Viewing pull request for $lessonTitle|j}->string;
            }
      leftPanel=courseTree
      centerPanel={
        <React.Suspense
          fallback={<div> {j|Loading $filePath...|j}->React.string </div>}>
          <RemoteFileEditor
            sourceRepo
            branch
            filePath
            onEditorDidMount
            onChange={(~result as _) => ()}
          />
        </React.Suspense>
      }
      rightPanel={
        <React.Suspense fallback={""->React.string}>
          <PullRequestChatHistory myUsername=username pullRequestId />
        </React.Suspense>
      }
      footer={"Footer"->string}
    />
  );
};
