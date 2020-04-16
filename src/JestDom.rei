type t = Dom.element;
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
let toContainElement: (t, [< modifier(t)]) => Jest.assertion;
let toContainHTML: (string, [< modifier(t)]) => Jest.assertion;
let toHaveAttribute:
  (string, ~value: string=?, [< modifier(t)]) => Jest.assertion;
let toHaveClass: ([`Str(string) | `Lst(list(string))], [< modifier(t)]) => Jest.assertion;
let toHaveFocus: [< modifier(t)] => Jest.assertion;
let toHaveFormValues:
  (Js.t({..}), [< modifier(t)]) => Jest.assertion;
let toHaveStyle: (string, [< modifier(t)]) => Jest.assertion;
let toHaveTextContent:
  ([`RegExp(Js.Re.t) | `Str(string)], ~options: TextContent.options=?, [< modifier(t)]) =>
  Jest.assertion;
  Jest.assertion;
