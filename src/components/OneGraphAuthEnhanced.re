include OneGraphAuth;

type service =
  | Egghead
  | GitHub;

let stringOfService = service =>
  switch (service) {
  | Egghead => "eggheadio"
  | GitHub => "github"
  };

let getLocalJwtMe = auth =>
  accessToken(auth)
  ->Js.Nullable.toOption
  ->Belt.Option.map(token => OneJwt.payload(token##accessToken));

let getLocalUserId = auth => {
  let jwtMe = getLocalJwtMe(auth);
  let id =
    OneJwt.(
      jwtMe->Belt.Option.flatMap(jwtMe =>
        jwtMe.user->Belt.Option.flatMap(user => user.id)
      )
    )
    ->Belt.Option.map(string_of_int);
  id;
};

let logoutMultipleServices = (auth, services: list(service)) => {
  let promises =
    services->Belt.List.map(service => {
      let serviceName = stringOfService(service);
      OneGraphAuth.logout(auth, serviceName, ())->Promise.Js.fromBsPromise;
    });
  Promise.Js.all(promises);
};
