/* Bring in all of the matchers. */
[%bs.raw {|require('@testing-library/jest-dom')|}];

type expect;
type t = Dom.element;

module HaveClass = {
  type options = {. "exact": Js.undefined(bool)};

  [@bs.obj] external makeOptions: (~exact: bool=?, unit) => options;
};

module TextContent = {
  type options = {. "normalizeWhitespace": Js.undefined(bool)};

  [@bs.obj]
  external makeOptions: (~normalizeWhitespace: bool=?, unit) => options;
};

[@bs.val] external expect: t => expect = "expect";
[@bs.get] external not_: expect => expect = "not";

let pass: (expect => unit, expect) => Jest.assertion =
  (assertion, expect) => expect->assertion->(_ => Jest.pass);

[@bs.send.pipe: expect] external _toBeDisabled: unit = "toBeDisabled";

let toBeDisabled = _toBeDisabled->pass;

[@bs.send.pipe: expect] external _toBeEnabled: unit = "toBeEnabled";

let toBeEnabled = _toBeEnabled->pass;

[@bs.send.pipe: expect] external _toBeEmpty: unit = "toBeEmpty";

let toBeEmpty = _toBeEmpty->pass;

[@bs.send.pipe: expect]
external _toBeInTheDocument: unit = "toBeInTheDocument";

let toBeInTheDocument = _toBeInTheDocument->pass;

[@bs.send.pipe: expect] external _toBeInvalid: unit = "toBeInvalid";

let toBeInvalid = _toBeInvalid->pass;

[@bs.send.pipe: expect] external _toBeRequired: unit = "toBeRequired";

let toBeRequired = _toBeRequired->pass;

[@bs.send.pipe: expect] external _toBeValid: unit = "toBeValid";

let toBeValid = _toBeValid->pass;

[@bs.send.pipe: expect] external _toBeVisible: unit = "toBeVisible";

let toBeVisible = _toBeVisible->pass;

[@bs.send.pipe: expect]
external _toContainElement: Js.nullable(t) => unit = "toContainElement";

let toContainElement = element =>
  element->Js.Nullable.fromOption->_toContainElement->pass;

[@bs.send.pipe: expect]
external _toContainHTML: string => unit = "toContainHTML";

let toContainHTML = html => html->_toContainHTML->pass;

[@bs.send.pipe: expect]
external _toHaveAttribute: (string, Js.undefined(string)) => unit =
  "toHaveAttribute";

let toHaveAttribute = (attribute, ~value=?) =>
  _toHaveAttribute(attribute, Js.Undefined.fromOption(value))->pass;

[@bs.send.pipe: expect]
external _toHaveClass: (string, Js.undefined(HaveClass.options)) => unit =
  "toHaveClass";

let toHaveClass = (class_, ~options=?) =>
  _toHaveClass(
    switch (class_) {
    | `Str(cls) => cls
    | `Lst(lst) => String.concat(" ", lst)
    },
    Js.Undefined.fromOption(options),
  )
  ->pass;

[@bs.send.pipe: expect] external _toHaveFocus: unit = "toHaveFocus";

let toHaveFocus = _toHaveFocus->pass;

[@bs.send.pipe: expect]
external _toHaveFormValues: Js.t({..}) => unit = "toHaveFormValues";

let toHaveFormValues = values => values->_toHaveFormValues->pass;

[@bs.send.pipe: expect]
external _toHaveStyle:
  ([@bs.unwrap] [ | `Str(string) | `Obj(Js.t({..}))]) => unit =
  "toHaveStyle";

let toHaveStyle = style => style->_toHaveStyle->pass;

[@bs.send.pipe: expect]
external _toHaveTextContent:
  (
    [@bs.unwrap] [ | `Str(string) | `RegExp(Js.Re.t)],
    Js.undefined(TextContent.options)
  ) =>
  unit =
  "toHaveTextContent";

let toHaveTextContent = (content, ~options=?) =>
  _toHaveTextContent(content, Js.Undefined.fromOption(options))->pass;

[@bs.send.pipe: expect]
external _toHaveValue:
  ([@bs.unwrap] [ | `Str(string) | `Arr(array(string)) | `Num(int)]) =>
  unit =
  "toHaveValue";

let toHaveValue = value => value->_toHaveValue->pass;

[@bs.send.pipe: expect]
external _toHaveDisplayValue:
  ([@bs.unwrap] [ | `Str(string) | `Arr(array(string))]) => unit =
  "toHaveDisplayValue";

let toHaveDisplayValue = value => value->_toHaveDisplayValue->pass;

[@bs.send.pipe: expect] external _toBeChecked: unit = "toBeChecked";

let toBeChecked = _toBeChecked->pass;
