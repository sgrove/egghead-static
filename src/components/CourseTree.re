module Fragment = [%relay.fragment
  {|
fragment CourseTree_GitHubPullRequest on GitHubPullRequest {
  body
  id
  number
  permalink
  state
  title
  url
}
|}
];

module Query = [%relay.query
  {|
query CourseTree_SearchForPullRequestsQuery(
  $query: String!
  $last: Int!
) {
  gitHub {
    search(query: $query, type: ISSUE, last: $last)
      @connection(
        key: "CourseTree_SearchForPullRequestsQuery_gitHub_search"
        filters: ["query"]
      ) {
      edges {
        node {
          __typename
          ... on GitHubPullRequest {
            ...CourseTree_GitHubPullRequest
              @relay(mask: false)
          }
        }
      }
    }
  }
}
|}
];

/* The main local state for our component is a map of Egghead lesson id =>
   (a semi-ordered, by PR number) *set* of pullRequests */
module PullRequestSetModule =
  Belt.Id.MakeComparable({
    type t = Query.Types.response_gitHub_search_edges_node_GitHubPullRequest;
    let cmp = (a: t, b: t) => {
      compare(a.number, b.number);
    };
  });

type state =
  Belt.Map.Int.t(
    Belt.Set.t(PullRequestSetModule.t, PullRequestSetModule.identity),
  );

let emptyPullRequestSet = Belt.Set.make(~id=(module PullRequestSetModule));

let makeSearchQuery = (~username) => {
  {j|repo:eggheadio/egghead-asciicasts [by $username] in:title|j};
};

[@react.component]
let make =
    (
      ~username,
      ~course: EggheadData.course,
      ~onLessonSelected,
      ~onPullRequestSelected,
    ) => {
  module Tree = BsReactAnimatedTree;

  let (allPullRequests: state, setPullRequests) =
    React.useState(() => Belt.Map.Int.empty);

  let search = makeSearchQuery(~username);

  let query =
    Query.use(
      ~variables={
        {query: search, last: 100};
      },
      (),
    );

  React.useEffect1(
    () => {
      switch (query) {
      | {gitHub: Some({search})} =>
        let nodes = Query.getConnectionNodes_search(search);

        let gitHubPullRequests =
          nodes->Belt.Array.keepMap(node => {
            switch (node) {
            | `GitHubPullRequest(pr) =>
              let body = pr.body;
              let (metadata, _) = EggheadMarkdownMeta.ofString(body);

              switch (metadata##lessonId) {
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
              | Some(pullRequestSet) =>
                Some(Belt.Set.add(pullRequestSet, pr))
              | None => Some(Belt.Set.add(emptyPullRequestSet, pr)),
            )
          });

        setPullRequests(_existingPullRequests => newPullRequests);

      | _ => ()
      };

      None;
    },
    [|query|],
  );

  React.(
    <div className="tree">
      <Tree content={course.title->string} _open=true>
        {course.lessons
         ->Belt.Array.map(lesson => {
             let lessonPullRequests =
               allPullRequests
               ->Belt.Map.Int.getWithDefault(lesson.id, emptyPullRequestSet)
               ->Belt.Set.toArray;

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
                | [||] => null
                | prs =>
                  prs
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
                            style={ReactDOMRe.Style.make(
                              ~cursor="pointer",
                              (),
                            )}
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
    </div>
  );
};
