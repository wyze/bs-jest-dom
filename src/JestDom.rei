type t = option(Dom.element);
type modifier('a) = [ | `Just('a) | `Not('a)];

module TextContent: {
  type options = {. "normalizeWhitespace": Js.undefined(bool)};

  [@bs.obj]
  external makeOptions: (~normalizeWhitespace: bool=?, unit) => options = "";
};

let toBeDisabled: [< modifier(t)] => Jest.assertion;
let toBeEnabled: [< modifier(t)] => Jest.assertion;
let toBeInTheDocument: [< modifier(t)] => Jest.assertion;
let toBeVisible: [< modifier(t)] => Jest.assertion;
let toContainElement: (t, [< | `Just(t) | `Not(t)]) => Jest.assertion;
let toContainHTML: (string, [< | `Just(t) | `Not(t)]) => Jest.assertion;
let toHaveAttribute:
  (string, ~value: string=?, [< | `Just(t) | `Not(t)]) => Jest.assertion;
let toHaveClass: (string, [< | `Just(t) | `Not(t)]) => Jest.assertion;
let toHaveClassMany:
  (list(string), [< | `Just(t) | `Not(t)]) => Jest.assertion;
let toHaveFocus: [< modifier(t)] => Jest.assertion;
let toHaveFormValues:
  (Js.t({..}), [< | `Just(t) | `Not(t)]) => Jest.assertion;
let toHaveStyle: (string, [< | `Just(t) | `Not(t)]) => Jest.assertion;
let toHaveTextContent:
  (string, ~options: TextContent.options=?, [< | `Just(t) | `Not(t)]) =>
  Jest.assertion;
let toHaveTextContentRe:
  (Js.Re.t, ~options: TextContent.options=?, [< | `Just(t) | `Not(t)]) =>
  Jest.assertion;
