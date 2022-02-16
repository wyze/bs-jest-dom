/* Bring in all of the matchers. */
%raw(`require('@testing-library/jest-dom')`)

type expect
type t = Dom.element

module HaveClass = {
  type options = {"exact": Js.undefined<bool>}

  @obj external makeOptions: (~exact: bool=?, unit) => options = ""
}

module TextContent = {
  type options = {"normalizeWhitespace": Js.undefined<bool>}

  @obj
  external makeOptions: (~normalizeWhitespace: bool=?, unit) => options = ""
}

@val external expect: t => expect = "expect"
@get external not__: expect => expect = "not"

let pass: (expect, expect => unit) => Jest.assertion = (expect, assertion) =>
  expect->assertion->(_ => Jest.pass)

@send external _toBeDisabled: expect => unit = "toBeDisabled"

let toBeDisabled = expect => pass(expect, _toBeDisabled)

@send external _toBeEnabled: expect => unit = "toBeEnabled"

let toBeEnabled = expect => pass(expect, _toBeEnabled)

@send external _toBeEmpty: expect => unit = "toBeEmpty"

let toBeEmpty = expect => pass(expect, _toBeEmpty)

@send
external _toBeEmptyDOMElement: expect => unit = "toBeEmptyDOMElement"

let toBeEmptyDOMElement = expect => pass(expect, _toBeEmptyDOMElement)

@send
external _toBeInTheDocument: expect => unit = "toBeInTheDocument"

let toBeInTheDocument = expect => pass(expect, _toBeInTheDocument)

@send external _toBeInvalid: expect => unit = "toBeInvalid"

let toBeInvalid = expect => pass(expect, _toBeInvalid)

@send external _toBeRequired: expect => unit = "toBeRequired"

let toBeRequired = expect => pass(expect, _toBeRequired)

@send external _toBeValid: expect => unit = "toBeValid"

let toBeValid = expect => pass(expect, _toBeValid)

@send external _toBeVisible: expect => unit = "toBeVisible"

let toBeVisible = expect => pass(expect, _toBeVisible)

@send
external _toContainElement: (expect, Js.nullable<t>) => unit = "toContainElement"

let toContainElement = (expect, element) =>
  pass(expect, expect => _toContainElement(expect, element->Js.Nullable.fromOption))

@send
external _toContainHTML: (expect, string) => unit = "toContainHTML"

let toContainHTML = (expect, html) => pass(expect, expect => expect->_toContainHTML(html))

@send
external _toHaveAttribute: (expect, string, Js.undefined<string>) => unit = "toHaveAttribute"

let toHaveAttribute = (expect, ~value=?, attribute) =>
  pass(expect, expect => expect->_toHaveAttribute(attribute, value->Js.Undefined.fromOption))

@send
external _toHaveClass: (expect, string, Js.undefined<HaveClass.options>) => unit = "toHaveClass"

let toHaveClass = (expect, ~options=?, class_) =>
  pass(expect, expect =>
    expect->_toHaveClass(
      switch class_ {
      | #Str(cls) => cls
      | #Lst(lst) => String.concat(" ", lst)
      },
      Js.Undefined.fromOption(options),
    )
  )

@send external _toHaveFocus: expect => unit = "toHaveFocus"

let toHaveFocus = expect => pass(expect, _toHaveFocus)

@send
external _toHaveFormValues: (expect, {..}) => unit = "toHaveFormValues"

let toHaveFormValues = (expect, values) => pass(expect, expect => expect->_toHaveFormValues(values))

@send
external _toHaveStyle: (expect, @unwrap [#Str(string) | #Obj({..})]) => unit = "toHaveStyle"

let toHaveStyle = (expect, style) => pass(expect, expect => _toHaveStyle(expect, style))

@send
external _toHaveTextContent: (
  expect,
  @unwrap [#Str(string) | #RegExp(Js.Re.t)],
  Js.undefined<TextContent.options>,
) => unit = "toHaveTextContent"

let toHaveTextContent = (expect, ~options=?, content) =>
  pass(expect, expect => expect->_toHaveTextContent(content, Js.Undefined.fromOption(options)))

@send
external _toHaveValue: (expect, @unwrap [#Str(string) | #Arr(array<string>) | #Num(int)]) => unit =
  "toHaveValue"

let toHaveValue = (expect, value) => pass(expect, expect => _toHaveValue(expect, value))

@send
external _toHaveDisplayValue: (
  expect,
  @unwrap
  [
    | #Str(string)
    | #RegExp(Js.Re.t)
    | #Arr(array<string>)
  ],
) => unit = "toHaveDisplayValue"

let toHaveDisplayValue = (expect, value) =>
  pass(expect, expect => _toHaveDisplayValue(expect, value))

@send external _toBeChecked: expect => unit = "toBeChecked"

let toBeChecked = expect => pass(expect, _toBeChecked)

@send
external _toBePartiallyChecked: expect => unit = "toBePartiallyChecked"

let toBePartiallyChecked = expect => pass(expect, _toBePartiallyChecked)

@send
external _toHaveDescription: (expect, @unwrap [#Str(string) | #RegExp(Js.Re.t)]) => unit =
  "toHaveDescription"

let toHaveDescription = (expect, content) =>
  pass(expect, expect => expect->_toHaveDescription(content))
