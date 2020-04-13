module NodeList = {
  type t = Dom.nodeList;

  [@bs.val] external toArray: t => array(Dom.node) = "Array.from";

  [@bs.get] external length: t => int = "length";

  [@bs.send] [@bs.return nullable]
  external item: (t, int) => option(Dom.node) = "item";
};

module DomNode = {
  type t = Dom.node;

  [@bs.get] external parentNode: t => Js.Nullable.t(t) = "parentNode";
  [@bs.get]
  external previousSibling: t => Js.Nullable.t(t) = "previousSibling";

  /* NB: Not really an array, it's a NodeList! But we only need .length and
     index access, so it's close enough for our purposes*/
  [@bs.get] external childNodes: t => NodeList.t = "childNodes";

  let rec getNodeIndex = node => {
    switch (Js.Nullable.toOption(previousSibling(node))) {
    | None => 0
    | Some(sibling) => 1 + getNodeIndex(sibling)
    };
  };
};

module Serialized = {
  type position = {
    path: array(int),
    offset: int,
  };

  type range = (position, position);

  type selection = (range, range);
};

let serializePosition = (~root, ~target, ~charOffset) => {
  let rec helper = node => {
    let nodeIndex = DomNode.getNodeIndex(node);

    let parts =
      switch (root == node) {
      | false =>
        switch (Js.Nullable.toOption(DomNode.parentNode(node))) {
        | None => []
        | Some(parent) => [nodeIndex, ...helper(parent)]
        }
      | true => []
      };

    parts;
  };
  Serialized.{
    path: target->helper->List.rev->Belt.List.toArray,
    offset: charOffset,
  };
};

type position = {
  node: Dom.node,
  offset: int,
};

let deserializePosition =
    (~pos as serialized: Serialized.position, ~root): option(position) => {
  let path = serialized.path;
  let offset = serialized.offset;
  let originalPath = path->Belt.List.fromArray;

  let rec helper = (path, next) => {
    switch (path) {
    | [] => Some({node: next, offset})
    | [nodeIndex, ...path] =>
      let children = DomNode.childNodes(next);

      switch (NodeList.item(children, nodeIndex)) {
      | None => None
      | Some(childNode) => helper(path, childNode)
      };
    };
  };

  let node = helper(originalPath, root);

  node;
};

module Range = {
  type t = Dom.range;

  [@bs.new] external make: unit => t = "Range"; /* experimental */

  [@bs.get] external collapsed: t => bool = "collapsed";
  [@bs.get]
  external commonAncestorContainer: t => Dom.node = "commonAncestorContainer";
  [@bs.get] external endContainer: t => Dom.node = "endContainer";
  [@bs.get] external endOffset: t => int = "endOffset";
  [@bs.get] external startContainer: t => Dom.node = "startContainer";
  [@bs.get] external startOffset: t => int = "startOffset";

  [@bs.send]
  external setStart: (t, Dom.node_like('a), int) => unit = "setStart";
  [@bs.send] external setEnd: (t, Dom.node_like('a), int) => unit = "setEnd";
  [@bs.send]
  external setStartBefore: (t, Dom.node_like('a)) => unit = "setStartBefore";
  [@bs.send]
  external setStartAfter: (t, Dom.node_like('a)) => unit = "setStartAfter";
  [@bs.send]
  external setEndBefore: (t, Dom.node_like('a)) => unit = "setEndBefore";
  [@bs.send]
  external setEndAfter: (t, Dom.node_like('a)) => unit = "setEndAfter";
  [@bs.send]
  external selectNode: (t, Dom.node_like('a)) => unit = "selectNode";
  [@bs.send]
  external selectNodeContents: (t, Dom.node_like('a)) => unit =
    "selectNodeContents";
  [@bs.send] external collapse: t => unit = "collapse";
  [@bs.send]
  external collapseToStart: (t, [@bs.as {json|true|json}] _) => unit =
    "collapse";
  [@bs.send]
  external cloneContents: t => Dom.documentFragment = "cloneContents";
  [@bs.send] external deleteContents: t => unit = "deleteContents";
  [@bs.send]
  external extractContents: t => Dom.documentFragment = "extractContents";
  [@bs.send]
  external insertNode: (t, Dom.node_like('a)) => unit = "insertNode";
  [@bs.send]
  external surroundContents: (t, Dom.node_like('a)) => unit =
    "surroundContents";
  [@bs.send]
  external compareBoundaryPoints:
    (t, int /* compareHow enum */, t) => int /* compareResult enum */ =
    "compareBoundaryPoints";
  [@bs.send] external cloneRange: t => t = "cloneRange";
  [@bs.send] external detach: t => unit = "detach";
  [@bs.send] external toString: t => string = "toString";
  [@bs.send]
  external comparePoint:
    (t, Dom.node_like('a), int) => int /* compareRsult enum */ =
    "comparePoint";
  [@bs.send]
  external intersectsNode: (t, Dom.node_like('a)) => bool = "intersectsNode";
  [@bs.send]
  external isPointInRange: (t, Dom.node_like('a), int) => bool =
    "isPointInRange";
};

module Selection = {
  type t = Dom.selection;

  [@bs.val] external getCurrent: unit => t = "window.getSelection";

  [@bs.get] [@bs.return nullable]
  external anchorNode: t => option(Dom.node) = "anchorNode";
  [@bs.get] external anchorOffset: t => int = "anchorOffset";
  [@bs.get] [@bs.return nullable]
  external focusNode: t => option(Dom.node) = "focusNode";
  [@bs.get] external focusOffset: t => int = "focusOffset";
  [@bs.get] external isCollapsed: t => bool = "isCollapsed";
  [@bs.get] external rangeCount: t => int = "rangeCount";

  [@bs.send] external getRangeAt: (t, int) => Dom.range = "getRangeAt";
  [@bs.send]
  external collapse: (t, Dom.node_like(_), int) => unit = "collapse";
  [@bs.send] external extend: (t, Dom.node_like(_), int) => unit = "extend";
  [@bs.send] external collapseToStart: t => unit = "collapseToStart";
  [@bs.send] external collapseToEnd: t => unit = "collapseToEnd";
  [@bs.send]
  external selectAllChildren: (t, Dom.node_like(_)) => unit =
    "selectAllChildren";
  [@bs.send]
  external setBaseAndExtent:
    (t, Dom.node_like(_), int, Dom.node_like(_), int) => unit =
    "setBaseAndExtent";
  [@bs.send] external addRange: (t, Dom.range) => unit = "addRange";
  [@bs.send] external removeRange: (t, Dom.range) => unit = "removeRange";
  [@bs.send] external removeAllRanges: t => unit = "removeAllRanges";
  [@bs.send] external deleteFromDocument: t => unit = "deleteFromDocument";
  [@bs.send] external toString: t => string = "toString";
  [@bs.send]
  external containsNode:
    (t, Dom.node_like(_), [@bs.as {json|false|json}] _) => bool =
    "containsNode";
  [@bs.send]
  external containsNodePartly:
    (t, Dom.node_like(_), [@bs.as {json|true|json}] _) => bool =
    "containsNode";
};

let deserializeRange = (range: Serialized.range, root) => {
  let (start, finish) = range;
  let startPosition = deserializePosition(~root, ~pos=start);
  let finishPosition = deserializePosition(~root, ~pos=finish);

  switch (startPosition, finishPosition) {
  | (Some(start), Some(finish)) =>
    let range = Range.make();
    range->Range.setStart(start.node, start.offset);
    range->Range.setEnd(finish.node, finish.offset);
    Some(range);
  | _ => None
  };
};

let serializeRange = (range: Range.t, root): Serialized.range => {
  let (startNode, startOffset) = (
    Range.startContainer(range),
    Range.startOffset(range),
  );

  let (finishNode, finishOffset) = (
    Range.endContainer(range),
    Range.endOffset(range),
  );

  let start =
    serializePosition(~root, ~target=startNode, ~charOffset=startOffset);
  let finish =
    serializePosition(~root, ~target=finishNode, ~charOffset=finishOffset);

  (start, finish);
};

let serializeSelection =
    (selection: Selection.t, ~root): option(Serialized.range) => {
  let rangeCount = Selection.rangeCount(selection);

  let selectionIsSerializable =
    switch (rangeCount, Selection.isCollapsed(selection)) {
    | (1, false) => true
    | _ => false
    };

  switch (selectionIsSerializable) {
  | false => None
  | true =>
    let range = Selection.getRangeAt(selection, 0);

    Some(serializeRange(range, root));
  };
};

let deserializeSelection = deserializeRange;
