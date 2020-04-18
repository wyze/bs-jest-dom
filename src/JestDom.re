/* Bring in all of the matchers. */
[%bs.raw {|require('@testing-library/jest-dom')|}];

type t = Dom.element;
type modifier('a) = [ | `Just('a) | `Not('a)];

module TextContent = {
  type options = {. "normalizeWhitespace": Js.undefined(bool)};

  [@bs.obj]
  external makeOptions: (~normalizeWhitespace: bool=?, unit) => options = "";
};

type assertion =
  | BeDisabled(modifier(t)): assertion
  | BeEnabled(modifier(t)): assertion
  | BeEmpty(modifier(t)): assertion
  | BeInTheDocument(modifier(t)): assertion
  | BeInvalid(modifier(t)): assertion
  | BeRequired(modifier(t)): assertion
  | BeValid(modifier(t)): assertion
  | BeVisible(modifier(t)): assertion
  | ContainElement(modifier((t, t))): assertion
  | ContainHTML(modifier((t, string))): assertion
  | HaveAttribute(modifier((t, string, option(string)))): assertion
  | HaveClass(modifier((t, string))): assertion
  | HaveFocus(modifier(t)): assertion
  | HaveFormValues(modifier((t, Js.t({..})))): assertion
  | HaveStyle(modifier((t, string))): assertion
  | HaveTextContent(modifier((t, string, option(TextContent.options))))
    : assertion
  | HaveTextContentRe(modifier((t, Js.Re.t, option(TextContent.options))))
    : assertion
  | HaveValue(modifier((t, string))) : assertion
  | HaveValueInt(modifier((t, int))) : assertion
  | HaveValueMany(modifier((t, array(string)))) : assertion
  | HaveDisplayValue(modifier((t, string))) : assertion
  | HaveDisplayValueMany(modifier((t, array(string)))) : assertion
  | BeChecked(modifier((t))) : assertion;

[@bs.val] external expect: t => Js.t({..}) = "expect";

let joinList = lst => lst->Array.of_list |> Js.Array.joinWith(" ");

let mapMod = f =>
  fun
  | `Just(expected) => `Just(f(expected))
  | `Not(expected) => `Not(f(expected));

let toJestAssertion = expected =>
  Jest.Expect.((() => expected)->Jest.Expect.expect->not_->toThrow);

let affirm =
  fun
  | BeDisabled(`Just(expected)) => expect(expected)##toBeDisabled()
  | BeDisabled(`Not(expected)) => expect(expected)##(!)##toBeDisabled()
  | BeEnabled(`Just(expected)) => expect(expected)##toBeEnabled()
  | BeEnabled(`Not(expected)) => expect(expected)##(!)##toBeEnabled()
  | BeEmpty(`Just(expected)) => expect(expected)##toBeEmpty()
  | BeEmpty(`Not(expected)) => expect(expected)##(!)##toBeEmpty()
  | BeInTheDocument(`Just(expected)) =>
    expect(expected)##toBeInTheDocument()
  | BeInTheDocument(`Not(expected)) =>
    expect(expected)##(!)##toBeInTheDocument()
  | BeInvalid(`Just(expected)) => expect(expected)##toBeInvalid()
  | BeInvalid(`Not(expected)) => expect(expected)##(!)##toBeInvalid()
  | BeRequired(`Just(expected)) => expect(expected)##toBeRequired()
  | BeRequired(`Not(expected)) => expect(expected)##(!)##toBeRequired()
  | BeValid(`Just(expected)) => expect(expected)##toBeValid()
  | BeValid(`Not(expected)) => expect(expected)##(!)##toBeValid()
  | BeVisible(`Just(expected)) => expect(expected)##toBeVisible()
  | BeVisible(`Not(expected)) => expect(expected)##(!)##toBeVisible()
  | ContainElement(`Just(expected, element)) =>
    expect(expected)##toContainElement(element)
  | ContainElement(`Not(expected, element)) =>
    expect(expected)##(!)##toContainElement(element)
  | ContainHTML(`Just(expected, html)) =>
    expect(expected)##toContainHTML(html)
  | ContainHTML(`Not(expected, html)) =>
    expect(expected)##(!)##toContainHTML(html)
  | HaveAttribute(`Just(expected, attribute, value)) =>
    expect(expected)##toHaveAttribute(
      attribute,
      Js.Undefined.fromOption(value),
    )
  | HaveAttribute(`Not(expected, attribute, value)) =>
    expect(expected)##(!)##toHaveAttribute(
      attribute,
      Js.Undefined.fromOption(value),
    )
  | HaveClass(`Just(expected, class_)) =>
    expect(expected)##toHaveClass(class_)
  | HaveClass(`Not(expected, class_)) =>
    expect(expected)##(!)##toHaveClass(class_)
  | HaveFocus(`Just(expected)) => expect(expected)##toHaveFocus()
  | HaveFocus(`Not(expected)) => expect(expected)##(!)##toHaveFocus()
  | HaveFormValues(`Just(expected, values)) =>
    expect(expected)##toHaveFormValues(values)
  | HaveFormValues(`Not(expected, values)) =>
    expect(expected)##(!)##toHaveFormValues(values)
  | HaveStyle(`Just(expected, style)) =>
    expect(expected)##toHaveStyle(style)
  | HaveStyle(`Not(expected, style)) =>
    expect(expected)##(!)##toHaveStyle(style)
  | HaveTextContent(`Just(expected, text, opts)) =>
    expect(expected)##toHaveTextContent(text, Js.Undefined.fromOption(opts))
  | HaveTextContentRe(`Just(expected, re, opts)) =>
    expect(expected)##toHaveTextContent(re, Js.Undefined.fromOption(opts))
  | HaveTextContent(`Not(expected, text, opts)) =>
    expect(expected)##(!)##toHaveTextContent(
      text,
      Js.Undefined.fromOption(opts),
    )
  | HaveTextContentRe(`Not(expected, re, opts)) =>
    expect(expected)##(!)##toHaveTextContent(
      re,
      Js.Undefined.fromOption(opts),
    )
  | HaveValue(`Just(expected, value)) => expect(expected)##toHaveValue(value)
  | HaveValue(`Not(expected, value)) => expect(expected)##(!)##toHaveValue(value)
  | HaveValueInt(`Just(expected, value)) => expect(expected)##toHaveValue(value)
  | HaveValueInt(`Not(expected, value)) => expect(expected)##(!)##toHaveValue(value)
  | HaveValueMany(`Just(expected, value)) => expect(expected)##toHaveValue(value)
  | HaveValueMany(`Not(expected, value)) => expect(expected)##(!)##toHaveValue(value)
  | HaveDisplayValue(`Just(expected, value)) => expect(expected)##toHaveDisplayValue(value)
  | HaveDisplayValue(`Not(expected, value)) => expect(expected)##(!)##toHaveDisplayValue(value)
  | HaveDisplayValueMany(`Just(expected, value)) => expect(expected)##toHaveDisplayValue(value)
  | HaveDisplayValueMany(`Not(expected, value)) => expect(expected)##(!)##toHaveDisplayValue(value)
  | BeChecked(`Just(expected)) => expect(expected)##toBeChecked()
  | BeChecked(`Not(expected)) => expect(expected)##(!)##toBeChecked();

let toBeDisabled = expected =>
  BeDisabled((expected :> modifier(_)))->affirm->toJestAssertion;

let toBeEnabled = expected =>
  BeEnabled((expected :> modifier(_)))->affirm->toJestAssertion;

let toBeEmpty = expected =>
  BeEmpty((expected :> modifier(_)))->affirm->toJestAssertion;

let toBeInvalid = expected =>
  BeInvalid((expected :> modifier(_)))->affirm->toJestAssertion;

let toBeRequired = expected =>
  BeRequired((expected :> modifier(_)))->affirm->toJestAssertion;

let toBeValid = expected =>
  BeValid((expected :> modifier(_)))->affirm->toJestAssertion;

let toBeInTheDocument = expected =>
  BeInTheDocument((expected :> modifier(_)))->affirm->toJestAssertion;

let toBeVisible = expected =>
  BeVisible((expected :> modifier(_)))->affirm->toJestAssertion;

let toContainElement = (element, expected) =>
  ContainElement(mapMod(exp => (exp, element), expected))
  ->affirm
  ->toJestAssertion;

let toContainHTML = (html, expected) =>
  ContainHTML(mapMod(exp => (exp, html), expected))
  ->affirm
  ->toJestAssertion;

let toHaveAttribute = (attribute, ~value=?, expected) =>
  HaveAttribute(mapMod(exp => (exp, attribute, value), expected))
  ->affirm
  ->toJestAssertion;

let toHaveClass = (class_, expected) =>
  HaveClass(
    mapMod(
      exp => (
        exp,
        switch (class_) {
        | `Str(s) => s
        | `Lst(lst) => lst->joinList
        },
      ),
      expected,
    ),
  )
  ->toJestAssertion;

let toHaveFocus = expected =>
  HaveFocus((expected :> modifier(_)))->affirm->toJestAssertion;

let toHaveFormValues = (values, expected) =>
  HaveFormValues(mapMod(exp => (exp, values), expected))
  ->affirm
  ->toJestAssertion;

let toHaveStyle = (style, expected) =>
  HaveStyle(mapMod(exp => (exp, style), expected))->affirm->toJestAssertion;

let toHaveTextContent = (content, ~options=?, expected) =>
  (
    switch (content) {
    | `RegExp(re) =>
      HaveTextContentRe(mapMod(exp => (exp, re, options), expected))
    | `Str(text) =>
      HaveTextContent(mapMod(exp => (exp, text, options), expected))
    }
  )
  ->affirm
  ->toJestAssertion;

let toHaveValue = (value, expected) =>
  (
    switch (value) {
    | `Lst(lst) =>
      HaveValueMany(mapMod(exp => (exp, lst->Array.of_list), expected))
    | `Num(num) =>
      HaveValueInt(mapMod(exp => (exp, num), expected))
    | `Str(text) =>
      HaveValue(mapMod(exp => (exp, text), expected))
    }
  )
  ->affirm
  ->toJestAssertion;

let toHaveDisplayValue = (value, expected) =>
  (
    switch (value) {
    | `Lst(lst) =>
      HaveDisplayValueMany(mapMod(exp => (exp, lst->Array.of_list), expected))
    | `Str(text) =>
      HaveDisplayValue(mapMod(exp => (exp, text), expected))
    }
  )
  ->affirm
  ->toJestAssertion;

let toBeChecked = expected =>
  BeChecked((expected :> modifier(_)))->affirm->toJestAssertion;
