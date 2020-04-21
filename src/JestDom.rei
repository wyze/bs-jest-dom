type expect;
type t = Dom.element;

module HaveClass: {
  type options = {. "exact": Js.undefined(bool)};

  [@bs.obj] external makeOptions: (~exact: bool=?, unit) => options;
};

module TextContent: {
  type options = {. "normalizeWhitespace": Js.undefined(bool)};

  [@bs.obj]
  external makeOptions: (~normalizeWhitespace: bool=?, unit) => options;
};

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
let toContainElement: (option(t), expect) => Jest.assertion;
let toContainHTML: (string, expect) => Jest.assertion;
let toHaveAttribute: (string, ~value: string=?, expect) => Jest.assertion;
let toHaveClass:
  (
    [ | `Str(string) | `Lst(list(string))],
    ~options: HaveClass.options=?,
    expect
  ) =>
  Jest.assertion;
let toHaveFocus: expect => Jest.assertion;
let toHaveFormValues: (Js.t({..}), expect) => Jest.assertion;
let toHaveStyle:
  ([ | `Str(string) | `Obj(Js.t({..}))], expect) => Jest.assertion;
let toHaveTextContent:
  (
    [ | `Str(string) | `RegExp(Js.Re.t)],
    ~options: TextContent.options=?,
    expect
  ) =>
  Jest.assertion;
let toHaveValue:
  ([ | `Str(string) | `Arr(array(string)) | `Num(int)], expect) =>
  Jest.assertion;
let toHaveDisplayValue:
  ([ | `Str(string) | `Arr(array(string))], expect) => Jest.assertion;
let toBeChecked: expect => Jest.assertion;
