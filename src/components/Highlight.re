type removeHighlightFunction = unit => unit;

[@bs.module "dom-highlight-range"]
external highlightRange:
  (. 'range, string, Js.t('a)) => removeHighlightFunction =
  "default";

let highlightRange = (range: Rangy.Range.t) => {
  let removeHighlights = highlightRange(. range, "mark", {"_": ""});

  // Running removeHighlights() will remove the highlight again.
  Some(removeHighlights);
};

Utils.assignToWindowForDeveloperDebug(~name="ss", Rangy.serializeSelection);
Utils.assignToWindowForDeveloperDebug(~name="ds", Rangy.deserializeSelection);
Utils.assignToWindowForDeveloperDebug(~name="hr", highlightRange);
