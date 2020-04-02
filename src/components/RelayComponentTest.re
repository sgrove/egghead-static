module Query = [%relay.query
  {|query RelayComponentTest_GitHubUserQuery($login: String!) {

  gitHub {
    licenses {
      body
      name
    }
    user(login: $login) {
      ...RelayComponentTest_GitHubUser
    }
  }
}|}
];

module Fragment = [%relay.fragment
  {|fragment RelayComponentTest_GitHubUser on GitHubUser {
  bio
  avatarUrl
  isHireable
  name
     login
}|}
];

module Avatar = {
  [@react.component]
  let make = (~gitHubUser) => {
    let data = Fragment.use(gitHubUser);
    React.(
      <div>
        <img src={data.avatarUrl} />
        {switch (data.name) {
         | None => string("Hello there, " ++ data.login)
         | Some(name) => string("Hello there, " ++ name)
         }}
      </div>
    );
  };
};

[@react.component]
let make = (~login: string) => {
  open React;

  let query = Query.use(~variables={login: login}, ());

  let (showUser, setShowUser) = React.useState(() => false);

  switch (showUser) {
  | false =>
    <>
      <button onClick={_ => setShowUser(_ => true)}>
        {string("Click me to show")}
      </button>
      <ul>
        {switch (query) {
         | {gitHub: Some({licenses: _})} => string("Got some licenses")
         | _ => string("No licenses")
         }}
      </ul>
    </>
  | true =>
    switch (query) {
    | {gitHub: Some({user: Some(user)})} =>
      let refs = user.getFragmentRefs();
      <Avatar gitHubUser=refs />;
    | _ => string("No such user found: " ++ login)
    }
  };
};

let default = make;
