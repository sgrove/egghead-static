type user = {
  id: option(int),
  email: option(string),
  gitHubLogin: option(string),
  login: option(string),
  avatarUrl: option(string),
};

type t = {user: option(user)};

[@bs.val] external btoa: string => string = "btoa";
[@bs.val] external atob: string => string = "atob";

let payload = (jwt: string): t => {
  let pieces = jwt |> Js.String.split(".", _);
  let payload = pieces[1];
  let decoded = atob(payload);
  let json = Js.Json.parseExn(decoded);
  let t: t = Obj.magic(json);
  t;
};

/* let payload = jwt: option(t) => */
/*   switch (Js.Null_undefined.toOption(jwt)) { */
/*   | None => None */
/*   | Some(jwt) => Some(payload_(jwt)) */
/*   }; */

let findGitHubLogin = (jwt: t): option(string) =>
  Belt.(jwt.user |> Option.flatMap(_, user => user.gitHubLogin));

let avatarUrl = (jwt: t): option(string) =>
  Belt.(jwt.user |> Option.flatMap(_, user => user.avatarUrl));
