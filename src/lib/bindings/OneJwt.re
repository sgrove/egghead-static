[@bs.deriving abstract]
type user = {
  [@bs.optional]
  id: int,
  [@bs.optional]
  email: string,
  [@bs.optional]
  gitHubLogin: string,
  [@bs.optional]
  login: string,
};

[@bs.deriving abstract]
type t = {
  [@bs.optional]
  user,
};

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

let findGitHubLogin = (~default, jwt: t): string =>
  Belt.(
    userGet(jwt)
    |> Option.flatMap(_, user => gitHubLoginGet(user))
    |> Option.getWithDefault(_, default)
  );
