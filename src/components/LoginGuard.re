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

let emptyStyle = ReactDOMRe.Style.make();

module ServiceIcon = {
  [@react.component]
  let make = (~serviceName, ~friendlyName, ~onClick=?, ~customStyle=?) => {
    let baseStyle =
      ReactDOMRe.Style.make(~width="250px", ~cursor="pointer", ());
    let style =
      ReactDOMRe.Style.combine(
        baseStyle,
        customStyle->Belt.Option.getWithDefault(emptyStyle),
      );

    <img
      style
      ?onClick
      src={j|/images/logos/$serviceName.svg|j}
      alt={j|Login with $friendlyName|j}
    />;
  };
};

let checkmark = (width, height) =>
  <svg
    xmlns="http://www.w3.org/2000/svg"
    width
    height
    viewBox="0 0 24 24"
    style={ReactDOMRe.Style.make(~position="absolute", ())}>
    <path
      fill="rgb(12, 116, 0, 0.8)"
      d="M20.285 2l-11.285 11.567-5.286-5.011-3.714 3.716 9 8.728 15-15.285z"
    />
  </svg>;

let loadingSpinner = (~height, ~width, ~style=emptyStyle, ()) =>
  <div
    className="inner"
    style={
      ReactDOMRe.Style.make(~width, ~height, ())
      ->ReactDOMRe.Style.combine(style)
    }>
    <svg
      xmlns="http://www.w3.org/2000/svg"
      style={ReactDOMRe.Style.make(
        ~margin=" auto",
        ~display=" block",
        ~backgroundPosition=" initial initial",
        ~backgroundRepeat=" initial initial",
        (),
      )}
      width
      height
      viewBox="0 0 100 100"
      preserveAspectRatio="xMidYMid">
      <g transform="rotate(0 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="-0.9166666666666666s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
      <g transform="rotate(30 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="-0.8333333333333334s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
      <g transform="rotate(60 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="-0.75s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
      <g transform="rotate(90 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="-0.6666666666666666s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
      <g transform="rotate(120 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="-0.5833333333333334s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
      <g transform="rotate(150 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="-0.5s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
      <g transform="rotate(180 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="-0.4166666666666667s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
      <g transform="rotate(210 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="-0.3333333333333333s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
      <g transform="rotate(240 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="-0.25s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
      <g transform="rotate(270 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="-0.16666666666666666s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
      <g transform="rotate(300 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="-0.08333333333333333s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
      <g transform="rotate(330 50 50)">
        <rect x="47" y="24" rx="3" ry="6" width="6" height="12" fill="#0a0a0a">
          <animate
            attributeName="opacity"
            values="1;0"
            keyTimes="0;1"
            dur="1s"
            begin_="0s"
            repeatCount="indefinite"
          />
        </rect>
      </g>
    </svg>
  </div>;

module LoginIcon = {
  [@react.component]
  let make =
      (
        ~auth,
        ~service: OneGraphAuthEnhanced.service,
        ~serviceState,
        ~onLoginStateChange,
        ~whyMessage,
      ) => {
    let (serviceName, friendlyName) =
      switch (service) {
      | Egghead => ("eggheadio", "Egghead")
      | GitHub => ("github", "GitHub")
      };

    let container =
      ReactDOMRe.Style.make(
        ~display="flex",
        ~position="relative",
        ~flexDirection="column",
        ~width="100%",
        ~alignItems="center",
        (),
      );

    let tryLogin = () => {
      onLoginStateChange(Loading);

      OneGraphAuthEnhanced.login(auth, serviceName)
      /* TODO: Report if localJwt me is None, means something went wrong when parsing the JWT */
      ->Js.Promise.then_(
          () =>
            OneGraphAuthEnhanced.isLoggedIn(auth, serviceName)
            ->Js.Promise.then_(
                isLoggedIn =>
                  (
                    switch (isLoggedIn) {
                    | false => onLoginStateChange(LoggedOut)
                    | true =>
                      OneGraphAuthEnhanced.getLocalJwtMe(auth)
                      ->Belt.Option.map(me =>
                          onLoginStateChange(LoggedIn(me))
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
    };

    let textStyle =
      ReactDOMRe.Style.make(
        ~fontSize="large",
        ~fontWeight="bold",
        ~color="black",
        (),
      );

    React.(
      switch (serviceState) {
      | LoggedIn(_me) =>
        <button style=container disabled=true>
          <ServiceIcon serviceName friendlyName />
          {checkmark("250px", "250px")}
          <span style=textStyle>
            {j|Logged into $friendlyName!|j}->string
          </span>
        </button>
      | Loading =>
        <button style=container disabled=true>
          <ServiceIcon serviceName friendlyName />
          {loadingSpinner(
             ~height="250px",
             ~width="250px",
             ~style=ReactDOMRe.Style.make(~position="absolute", ()),
             (),
           )}
          <span style=textStyle>
            {j|Logging into $friendlyName...|j}->string
          </span>
        </button>
      | LoggedOut =>
        <button style=container>
          <ServiceIcon serviceName friendlyName onClick={_ => tryLogin()} />
          <span style=textStyle> {string(whyMessage)} </span>
        </button>
      }
    );
  };
};

let amILoggedInto = (auth, ~service, ~ifYes=?, ~ifNo=?, ()) => {
  OneGraphAuthEnhanced.isLoggedIn(auth, service)
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

[@react.component]
let make = (~auth, ~children) => {
  Utils.assignToWindowForDeveloperDebug(~name="oneauth", auth);
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
      {egghead: Loading, gitHub: Loading, me: None},
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
      ~ifNo=() => {dispatch(SetAuthState(service, LoggedOut))},
      (),
    );

  /* Kick off the initial logged-in check */
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
      style={ReactDOMRe.Style.make(~display="flex", ~minHeight="100vh", ())}>
      <div
        className="content-left-padding"
        style={ReactDOMRe.Style.make(
          ~backgroundColor="#1e1e1e",
          ~width="20%",
          (),
        )}
      />
      <div
        style={ReactDOMRe.Style.make(
          ~width="60%",
          ~backgroundColor="#fff",
          ~textAlign="center",
          ~alignItems="center",
          ~justifyContent="center",
          ~display="flex",
          (),
        )}>
        <div
          style={ReactDOMRe.Style.make(
            ~alignSelf="center",
            ~borderRadius="4000px",
            (),
          )}>
          <LoginIcon
            auth
            onLoginStateChange={newState =>
              dispatch(SetAuthState(GitHub, newState))
            }
            serviceState={state.gitHub}
            service=GitHub
            whyMessage="Log into GitHub so we can submit your changes to our repository"
          />
          <LoginIcon
            auth
            onLoginStateChange={newState =>
              dispatch(SetAuthState(Egghead, newState))
            }
            serviceState={state.egghead}
            service=Egghead
            whyMessage="Log into Egghead so we can thank you for your contributions"
          />
        </div>
      </div>
      <div
        className="content-right-padding"
        style={ReactDOMRe.Style.make(
          ~backgroundColor="#1e1e1e",
          ~width="20%",
          (),
        )}
      />
    </div>
  };
};
