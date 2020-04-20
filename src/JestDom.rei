type t = Dom.element;
// type modifier('a) = [ | `Just('a) | `Not('a)];

module TextContent: {
  type options = {. "normalizeWhitespace": Js.undefined(bool)};

  [@bs.obj]
  external makeOptions: (~normalizeWhitespace: bool=?, unit) => options;
};

/* New */

type expect;
[@bs.val] external expect: t => expect = "expect";
[@bs.get] external not_: expect => expect = "not";

let toBeDisabled: expect => Jest.assertion;
let toBeEnabled: expect => Jest.assertion;
let toBeEmpty: expect => Jest.assertion;
let toBeInTheDocument: expect => Jest.assertion;
let toBeInvalid: expect => Jest.assertion;
let toBeRequired: expect => Jest.assertion;
let toBeValid: expect => Jest.assertion;
let toBeVisible: expect => Jest.assertion;
let toContainElement: (t, expect) => Jest.assertion;
let toContainHTML: (string, expect) => Jest.assertion;
let toHaveAttribute: (string, ~value: string=?, expect) => Jest.assertion;

// let toBeDisabled: [< modifier(t)] => Jest.assertion;
// let toBeEnabled: [< modifier(t)] => Jest.assertion;
// let toBeEmpty: [< modifier(t)] => Jest.assertion;
// let toBeInTheDocument: [< modifier(t)] => Jest.assertion;
// let toBeInvalid: [< modifier(t)] => Jest.assertion;
// let toBeRequired: [< modifier(t)] => Jest.assertion;
// let toBeValid: [< modifier(t)] => Jest.assertion;
// let toBeVisible: [< modifier(t)] => Jest.assertion;
// let toContainElement: (t, [< modifier(t)]) => Jest.assertion;
// // let toContainHTML: (string, [< modifier(t)]) => Jest.assertion;
// let toHaveAttribute:
//   (string, ~value: string=?, [< modifier(t)]) => Jest.assertion;
// let toHaveClass:
//   ([ | `Str(string) | `Lst(list(string))], [< modifier(t)]) =>
//   Jest.assertion;
// let toHaveFocus: [< modifier(t)] => Jest.assertion;
// let toHaveFormValues: (Js.t({..}), [< modifier(t)]) => Jest.assertion;
// let toHaveStyle: (string, [< modifier(t)]) => Jest.assertion;
// let toHaveTextContent:
//   (
//     [ | `RegExp(Js.Re.t) | `Str(string)],
//     ~options: TextContent.options=?,
//     [< modifier(t)]
//   ) =>
//   Jest.assertion;
// let toHaveValue:
//   ([ | `Str(string) | `Lst(list(string)) | `Num(int)], [< modifier(t)]) =>
//   Jest.assertion;
// let toHaveDisplayValue:
//   ([ | `Str(string) | `Lst(list(string))], [< modifier(t)]) =>
//   Jest.assertion;
// let toBeChecked: [< modifier(t)] => Jest.assertion;
