[@bs.val]
external prettyStringify: ('a, Js.Nullable.t(unit), int) => string =
  "JSON.stringify";

let jsonParse: string => {..} = [%raw
  {|function(jsonString) {
     try {
     return JSON.parse(jsonString);
     } catch (e) {
     return {};
     }
}
|}
];

let unsafeAssign = [%raw {|function(a, b) {
 return Object.assign(a, b);
}
|}];

let assign = [%raw
  {|function(name, item) {
     window[name] = item;
     }|}
];

let toplevelMetaRegex = [%bs.re "/`{3}egghead-meta[\\s\\S]*?`{3}/g"];
let metaContentRegex = [%bs.re " /`{3}egghead-meta([\\s\\S]*)`{3}/m"];

let ofString = (string: string): ('a, string) => {
  let metadata =
    switch (Js.String2.match(string, toplevelMetaRegex)) {
    | Some(matches) =>
      let r =
        matches->Belt.Array.keepMap(match => {
          metaContentRegex
          ->Js.Re.exec_(match)
          ->Belt.Option.flatMapU((. result: Js.Re.result) =>
              switch (result->Js.Re.captures) {
              | [|_, jsonString|] => Js.Nullable.toOption(jsonString)
              | _ => None
              }
            )
        });
      r;
    | None => [||]
    };

  let result =
    metadata->Belt.Array.reduce(
      Js.Obj.empty(),
      (acc, metadataString) => {
        let metadata = jsonParse(metadataString);

        /* Ignore warning 20, we know we're doing unsafe things */
        [@ocaml.warning "-20"] unsafeAssign(acc, metadata);
      },
    );

  (
    result,
    string->Js.String2.replaceByRe(toplevelMetaRegex, "")->Js.String2.trim,
  );
};

let toString = metadata => {
  let json = prettyStringify(metadata, Js.Nullable.null, 2);

  {j|```egghead-meta
$json
```|j};
};

let test = () => {
  let body = {|bla bla

  bla
  ` wow `

```
  grrr
```

```meta
  {
    a: 10,
    wow: "Cool!",
[1, 2, {r: "'tru'"}
  }
```b


```javascript
  grrr
```


```meta
  {
    last: true
  }
```b


|};

  let result = ofString(body);
  Js.log2("loadMeta result: ", result);
};
