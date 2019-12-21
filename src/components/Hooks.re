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
  width: int,
  height: int,
};

let useWindowSize = onResize => {
  let window = Js.Nullable.toOption(windowSize);

  let isClient =
    switch (window) {
    | None => false
    | Some(_) => true
    };

  let getSize = () =>
    switch (window) {
    | None => None
    | Some(window) =>
      Some({width: window##innerWidth, height: window##innerHeight})
    };

  let (windowSize, setWindowSize) = React.useState(getSize);

  React.useEffect0(() =>
    switch (isClient, window) {
    | (true, Some(window)) =>
      let handleResize = () =>
        setWindowSize(_ => {
          let size = getSize();
          onResize(size);
          size;
        });

      addEventListener(window, "resize", handleResize);

      Some((() => removeEventListener(window, "resize", handleResize)));

    | _ => None
    }
  );

  windowSize;
};
