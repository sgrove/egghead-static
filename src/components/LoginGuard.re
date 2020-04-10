let amILoggedInto = (auth, ~service, ~ifYes=?, ~ifNo=?, ()) => {
  OneGraphAuth.isLoggedIn(auth, service)
  ->Js.Promise.then_(
      isLoggedIn =>
        {
          switch (isLoggedIn) {
          | false => ifNo->Belt.Option.map(f => f())
          | true => ifYes->Belt.Option.map(f => f())
          };
        }
        ->Js.Promise.resolve,
      _,
    );
};

type authState =
  | Loading
  | LoggedIn(OneJwt.t)
  | LoggedOut;

type state = {
  gitHub: authState,
  egghead: authState,
  me: option(OneJwt.t),
};

type action =
  | SetAuthState(OneGraphAuthEnhanced.service, authState);

[@react.component]
let make = (~auth, ~children) => {
  open React;
  let (state, dispatch) =
    useReducer(
      (state, action) =>
        switch (action) {
        | SetAuthState(service, authState) =>
          let me =
            switch (authState) {
            | LoggedIn(me) => Some(me)
            | _ => state.me
            };
          switch (service) {
          | Egghead => {...state, egghead: authState, me}
          | GitHub => {...state, gitHub: authState, me}
          };
        },
      {egghead: LoggedOut, gitHub: LoggedOut, me: None},
    );
  let checkLogin = (serviceName, service) =>
    amILoggedInto(
      auth,
      ~service=serviceName,
      ~ifYes=
        () => {
          OneGraphAuthEnhanced.getLocalJwtMe(auth)
          ->Belt.Option.map(me =>
              dispatch(SetAuthState(service, LoggedIn(me)))
            )
          ->ignore
        },
      (),
    );
  useEffect0(() => {
    checkLogin("eggheadio", Egghead)->ignore;
    checkLogin("github", GitHub)->ignore;
    None;
  });
  let loggedIn =
    switch (state.egghead, state.gitHub) {
    | (LoggedIn(_), LoggedIn(_)) => true
    | _ => false
    };
  let loginIcon = service => {
    let (serviceName, friendlyName, state) =
      switch ((service: OneGraphAuthEnhanced.service)) {
      | Egghead => ("eggheadio", "Egghead", state.egghead)
      | GitHub => ("github", "GitHub", state.gitHub)
      };
    switch (state) {
    | LoggedIn(_me) => <div> {j|Logged into $friendlyName|j}->string </div>
    | Loading => <div> {j|Logging into $friendlyName...|j}->string </div>
    | LoggedOut =>
      <img
        style={ReactDOMRe.Style.make(~width="50px", ~cursor="pointer", ())}
        onClick={_ => {
          dispatch(SetAuthState(service, Loading));
          OneGraphAuth.login(auth, serviceName)
          /* TODO: Report if localJwt me is None, means something went wrong with parsing the JWT */
          ->Js.Promise.then_(
              () =>
                OneGraphAuth.isLoggedIn(auth, serviceName)
                ->Js.Promise.then_(
                    isLoggedIn =>
                      (
                        switch (isLoggedIn) {
                        | false => dispatch(SetAuthState(service, LoggedOut))
                        | true =>
                          OneGraphAuthEnhanced.getLocalJwtMe(auth)
                          ->Belt.Option.map(me =>
                              dispatch(SetAuthState(service, LoggedIn(me)))
                            )
                          ->ignore
                        }
                      )
                      ->Js.Promise.resolve,
                    _,
                  ),
              _,
            )
          ->ignore;
        }}
        src={j|/images/logos/$serviceName.svg|j}
        alt={j|Login with $friendlyName|j}
      />
    };
  };
  switch (loggedIn, state.me) {
  | (true, Some(me)) =>
    <React.Suspense fallback={<div> "Loading editor..."->React.string </div>}>
      {switch (OneJwt.findGitHubLogin(me)) {
       | None => "Sorry, we couldn't verify your GitHub username"->string
       | Some(username) => children(username)
       }}
    </React.Suspense>
  | (_, _) =>
    <div
      style={ReactDOMRe.Style.make(
        ~border="1px solid gray",
        ~borderRadius="4px",
        ~width="500px",
        (),
      )}>
      "Please log in"->string
      <br />
      {loginIcon(GitHub)}
      {loginIcon(Egghead)}
    </div>
  };
};
