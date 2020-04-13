[@bs.val]
external prettyStringify:
  ('a, [@bs.as {json|null|json}] _, [@bs.as {json|2|json}] _) => string =
  "JSON.stringify";

[@bs.val] external uglyStringify: 'a => string = "JSON.stringify";

/* Using some raw JavaScript to assign a value to window for console debugging */
let assignToWindowForDeveloperDebug =
    (~name as _name: string, _value: 'b): unit => [%bs.raw
  {|window[_name] = _value|}
];

module String = {
  let random = length => {
    let gen = () =>
      switch (Js.Math.random_int(0, 26 + 26 + 10)) {
      | n when n < 26 => int_of_char('a') + n
      | n when n < 26 + 26 => int_of_char('A') + n - 26
      | n => int_of_char('0') + n - 26 - 26
      };
    let gen = _ => String.make(1, char_of_int(gen()));
    String.concat("", Array.to_list(Array.init(length, gen)));
  };
  let toBranchName = (string, username) => {
    let sanitized =
      Js.String.replaceByRe([%bs.re {|/[^a-zA-Z0-9]+/g|}], "-", string);
    Js.String.toLocaleLowerCase(sanitized ++ {j|$username|j});
  };
};

type lineChar = {
  line: int,
  char: int,
};

type sourcePosition = (lineChar, lineChar);

let extractSourcePosition = string =>
  switch (Js.Nullable.toOption(string)) {
  | None => None
  | Some(string) =>
    switch (Js.String.split("-", string)) {
    | [|from, to_|] =>
      switch (Js.String.(split(":", from), split(":", to_))) {
      | ([|fromLine, fromChar|], [|toLine, toChar|]) =>
        Some((
          {line: int_of_string(fromLine), char: int_of_string(fromChar)},
          {line: int_of_string(toLine), char: int_of_string(toChar)},
        ))
      | _ => None
      }

    | _ => None
    }
  };
