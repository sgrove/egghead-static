/* import { useState, useEffect } from 'react'; */

/* Usage */
/* function App() { */
/*   const size = useWindowSize(); */

/*   return ( */
/*     <div> */
/*       {size.width}px / {size.height}px */
/*     </div> */
/*   ); */
/* } */

/* Hook */

type window = {
  .
  "innerWidth": int,
  "innerHeight": int,
};

[@bs.send]
external addEventListener: (window, string, unit => unit) => unit =
  "addEventListener";

[@bs.send]
external removeEventListener: (window, string, unit => unit) => unit =
  "removeEventListener";

[@bs.val] external windowSize: Js.Nullable.t(window) = "window";

type size = {
  width: option(int),
  height: option(int),
};

let useWindowSize = () => {
  let window = Js.Nullable.toOption(windowSize);

  let isClient =
    switch (window) {
    | None => false
    | Some(_) => true
    };

  let getSize = () =>
    switch (window) {
    | None => {width: None, height: None}
    | Some(window) => {
        width: Some(window##innerWidth),
        height: Some(window##innerHeight),
      }
    };

  let (windowSize, setWindowSize) = React.useState(getSize);

  React.useEffect0(() =>
    switch (isClient, window) {
    | (true, Some(window)) =>
      let handleResize = () => setWindowSize(_ => getSize());

      addEventListener(window, "resize", handleResize);

      Some((() => removeEventListener(window, "resize", handleResize)));

    | _ => None
    }
  );

  windowSize;
};
