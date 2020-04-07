module Tree = BsReactAnimatedTree;

module Fragment = [%relay.fragment
  {|
fragment RelayCourseTree_PullRequestFragment on GitHubPullRequest {
  id
  title
  body
  state
  number
  comments(last: 100) {
    edges {
      node {
        id
        author {
          __typename
          login
          avatarUrl
        }
        createdAt
        body
      }
    }
  }
}
|}
];

module Query = [%relay.query
  {|
query RelayCourseTree_SearchForPullRequestsQuery(
  $query: String!
  $last: Int!
) {
  gitHub {
    search(query: $query, type: ISSUE, last: $last)
      @connection(key:"RelayCourseTree_SearchForPullRequestsQuery_gitHub_search")
      {
      edges {
        node {
          __typename
          ... on GitHubPullRequest {
            ...RelayCourseTree_PullRequestFragment
          }
        }
      }
    }
  }
}|}
];

type state = Belt.Map.Int.t(list(Fragment.Operation.fragment));

[@react.component]
let make =
    (
      ~username,
      ~course: EggheadData.course,
      ~selectedLessonId: option(int),
      ~onLessonSelected,
      ~onPullRequestSelected,
    ) => {
  let relayEnv = ReasonRelay.useEnvironmentFromContext();

  let (allPullRequests: state, setPullRequests) =
    React.useState(() => Belt.Map.Int.empty);

  React.useEffect2(
    () => {
      Query.fetch(
        ~environment=relayEnv,
        ~variables={
          query: {j|repo:eggheadio/egghead-asciicasts [by $username] in:title|j},
          last: 100,
        },
        ~onResult=result => {
          Js.log2("Relevant PullRequests: ", result);

          /* TODO: Handle error */
          switch (result) {
          | Ok({gitHub: Some({search})}) =>
            let nodes = Query.getConnectionNodes_search(search);

            let gitHubPullRequests =
              nodes->Belt.Array.keepMap(node => {
                switch (node) {
                | `GitHubPullRequest(pr) =>
                  let pr = pr.getFragmentRefs()->Fragment.use;
                  let body = pr.body;
                  let parsed = YamlFrontMatter.loadFront(body);

                  switch (parsed##lessonId) {
                  | None => None
                  | Some(lessonId) => Some((lessonId, pr))
                  };

                | _ => None
                }
              });

            let newPullRequests =
              gitHubPullRequests->Belt.Array.reduce(
                allPullRequests, (acc, (lessonId, pr)) => {
                Belt.Map.Int.update(
                  acc,
                  lessonId,
                  fun
                  | Some(prs) => Some([pr, ...prs])
                  | None => Some([pr]),
                )
              });

            setPullRequests(_existingPullRequests => newPullRequests);

          | _ => ()
          };
        },
      );

      None;
    },
    (selectedLessonId, username),
  );

  React.(
    <Tree content={course.title->string} _open=true>
      {course.lessons
       ->Belt.Array.map(lesson => {
           let lessonPullRequests =
             allPullRequests->Belt.Map.Int.getWithDefault(lesson.id, []);
           <Tree
             key={lesson.id->string_of_int}
             content={
               <span
                 style={ReactDOMRe.Style.make(~cursor="pointer", ())}
                 onClick={_ => onLessonSelected(~lessonId=lesson.id)}>
                 lesson.title->string
               </span>
             }>
             {switch (lessonPullRequests) {
              | [] => null
              | prs =>
                prs
                ->Belt.List.toArray
                ->Belt.Array.map(pr =>
                    <Tree
                      key={pr.id}
                      _type={
                        <span>
                          (
                            switch (pr.state) {
                            | `OPEN => {j|📖|j}
                            | `MERGED => {j|✅|j}
                            | `CLOSED => {j|❌|j}
                            | `FutureAddedValue(other) =>
                              Js.Console.warn2("Unknown PR state", other);
                              {j|??|j};
                            }
                          )
                          ->string
                        </span>
                      }
                      content={
                        <span
                          style={ReactDOMRe.Style.make(~cursor="pointer", ())}
                          onClick={_ =>
                            onPullRequestSelected(
                              ~lessonId=lesson.id,
                              ~pullRequestId=pr.id,
                            )
                          }>
                          pr.title->string
                        </span>
                      }
                    />
                  )
                ->array
              }}
           </Tree>;
         })}
    </Tree>
  );
};
