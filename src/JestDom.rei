type t = Dom.element;
type modifier('a) = [ | `Just('a) | `Not('a)];

module TextContent: {
  type options = {. "normalizeWhitespace": Js.undefined(bool)};

  [@bs.obj]
  external makeOptions: (~normalizeWhitespace: bool=?, unit) => options = "";
};

let toBeDisabled: [< modifier(t)] => Jest.assertion;
let toBeEnabled: [< modifier(t)] => Jest.assertion;
let toBeEmpty: [< modifier(t)] => Jest.assertion;
let toBeInTheDocument: [< modifier(t)] => Jest.assertion;
let toBeInvalid: [< modifier(t)] => Jest.assertion;
let toBeRequired: [< modifier(t)] => Jest.assertion;
let toBeValid: [< modifier(t)] => Jest.assertion;
let toBeVisible: [< modifier(t)] => Jest.assertion;
let toContainElement: (t, [< modifier(t)]) => Jest.assertion;
let toContainHTML: (string, [< modifier(t)]) => Jest.assertion;
let toHaveAttribute:
  (string, ~value: string=?, [< modifier(t)]) => Jest.assertion;
let toHaveClass:
  ([ | `Str(string) | `Lst(list(string))], [< modifier(t)]) =>
  Jest.assertion;
let toHaveFocus: [< modifier(t)] => Jest.assertion;
let toHaveFormValues: (Js.t({..}), [< modifier(t)]) => Jest.assertion;
let toHaveStyle: (string, [< modifier(t)]) => Jest.assertion;
let toHaveTextContent:
  (
    [ | `RegExp(Js.Re.t) | `Str(string)],
    ~options: TextContent.options=?,
    [< modifier(t)]
  ) =>
  Jest.assertion;
let toHaveValue:
  ([ | `Str(string) | `Lst(list(string)) | `Num(int)], [< modifier(t)]) =>
  Jest.assertion;
let toHaveDisplayValue:
  ([ | `Str(string) | `Lst(list(string))], [< modifier(t)]) =>
  Jest.assertion;
let toBeChecked: [< modifier(t)] => Jest.assertion;
