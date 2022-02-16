type expect
type t = Dom.element

module HaveClass: {
  type options = {"exact": Js.undefined<bool>}

  @obj external makeOptions: (~exact: bool=?, unit) => options = ""
}

module TextContent: {
  type options = {"normalizeWhitespace": Js.undefined<bool>}

  @obj
  external makeOptions: (~normalizeWhitespace: bool=?, unit) => options = ""
}

@val external expect: t => expect = "expect"
@get external not__: expect => expect = "not"

let toBeDisabled: expect => Jest.assertion
let toBeEnabled: expect => Jest.assertion
let toBeEmpty: expect => Jest.assertion
let toBeEmptyDOMElement: expect => Jest.assertion
let toBeInTheDocument: expect => Jest.assertion
let toBeInvalid: expect => Jest.assertion
let toBeRequired: expect => Jest.assertion
let toBeValid: expect => Jest.assertion
let toBeVisible: expect => Jest.assertion
let toContainElement: (expect, option<t>) => Jest.assertion
let toContainHTML: (expect, string) => Jest.assertion
let toHaveAttribute: (expect, ~value: string=?, string) => Jest.assertion
let toHaveClass: (
  expect,
  ~options: HaveClass.options=?,
  [#Str(string) | #Lst(list<string>)],
) => Jest.assertion
let toHaveFocus: expect => Jest.assertion
let toHaveFormValues: (expect, {..}) => Jest.assertion
let toHaveStyle: (expect, [#Str(string) | #Obj({..})]) => Jest.assertion
let toHaveTextContent: (
  expect,
  ~options: TextContent.options=?,
  [#Str(string) | #RegExp(Js.Re.t)],
) => Jest.assertion
let toHaveValue: (expect, [#Str(string) | #Arr(array<string>) | #Num(int)]) => Jest.assertion
let toHaveDisplayValue: (
  expect,
  [#Str(string) | #RegExp(Js.Re.t) | #Arr(array<string>)],
) => Jest.assertion
let toBeChecked: expect => Jest.assertion
let toBePartiallyChecked: expect => Jest.assertion
let toHaveDescription: (expect, [#Str(string) | #RegExp(Js.Re.t)]) => Jest.assertion
