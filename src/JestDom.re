/* Bring in all of the matchers. */
[%bs.raw {|require('jest-dom/extend-expect')|}];

type t = option(Dom.element);
type modifier('a) = [ | `Just('a) | `Not('a)];

module TextContent = {
  type options = {. "normalizeWhitespace": Js.undefined(bool)};

  [@bs.obj]
  external makeOptions: (~normalizeWhitespace: bool=?, unit) => options = "";
};

type assertion =
  | BeDisabled(modifier(t)): assertion
  | BeEnabled(modifier(t)): assertion
  | BeInTheDocument(modifier(t)): assertion
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
    : assertion;

[@bs.val] external expect: t => Js.t({..}) = "";

let joinList = lst => lst->Array.of_list |> Js.Array.joinWith(" ");

let mapMod = f =>
  fun
  | `Just(expected) => `Just(f(expected))
  | `Not(expected) => `Not(f(expected));

let toJestAssertion = expected =>
  Jest.Expect.((() => expected)->Jest.Expect.expect->not->toThrow);

let affirm =
  fun
  | BeDisabled(`Just(expected)) => expect(expected)##toBeDisabled()
  | BeDisabled(`Not(expected)) => expect(expected)##(!)##toBeDisabled()
  | BeEnabled(`Just(expected)) => expect(expected)##toBeEnabled()
  | BeEnabled(`Not(expected)) => expect(expected)##(!)##toBeEnabled()
  | BeInTheDocument(`Just(expected)) =>
    expect(expected)##toBeInTheDocument()
  | BeInTheDocument(`Not(expected)) =>
    expect(expected)##(!)##toBeInTheDocument()
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
  | HaveTextContent(`Not(expected, text, opts)) =>
    expect(expected)##(!)##toHaveTextContent(
      text,
      Js.Undefined.fromOption(opts),
    )
  | HaveTextContentRe(`Just(expected, text, opts)) =>
    expect(expected)##toHaveTextContent(text, Js.Undefined.fromOption(opts))
  | HaveTextContentRe(`Not(expected, text, opts)) =>
    expect(expected)##(!)##toHaveTextContent(
      text,
      Js.Undefined.fromOption(opts),
    );

let toBeDisabled = expected =>
  BeDisabled((expected :> modifier(_)))->affirm->toJestAssertion;

let toBeEnabled = expected =>
  BeEnabled((expected :> modifier(_)))->affirm->toJestAssertion;

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
  HaveClass(mapMod(exp => (exp, class_), expected))
  ->affirm
  ->toJestAssertion;

let toHaveClassMany = (classes, expected) =>
  HaveClass(mapMod(exp => (exp, classes->joinList), expected))
  ->affirm
  ->toJestAssertion;

let toHaveFocus = expected =>
  HaveFocus((expected :> modifier(_)))->affirm->toJestAssertion;

let toHaveFormValues = (values, expected) =>
  HaveFormValues(mapMod(exp => (exp, values), expected))
  ->affirm
  ->toJestAssertion;

let toHaveStyle = (style, expected) =>
  HaveStyle(mapMod(exp => (exp, style), expected))->affirm->toJestAssertion;

let toHaveTextContent = (text, ~options=?, expected) =>
  HaveTextContent(mapMod(exp => (exp, text, options), expected))
  ->affirm
  ->toJestAssertion;

let toHaveTextContentRe = (text, ~options=?, expected) =>
  HaveTextContentRe(mapMod(exp => (exp, text, options), expected))
  ->affirm
  ->toJestAssertion;
