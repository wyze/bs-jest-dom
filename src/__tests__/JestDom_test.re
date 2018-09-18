open Jest;
open JestDom;

let (
  jestExpect,
  toBeDefined,
  toThrow
) = (
  Expect.expect,
  ExpectJs.toBeDefined,
  Expect.toThrow
);

let div = [%raw {|document.createElement('div')|}];

external convert: ex => Js.t({ .. }) = "%identity";

[@bs.send] external focus: Dom.element => unit = "";

type q = Js.t({
  .
  container: Dom.element,
  [@bs.meth] queryByTestId: string => Dom.element
});

let render: string => q = [%raw {|
  function(html) {
    const container = document.createElement('div')
    container.innerHTML = html
    const queryByTestId = testId =>
      container.querySelector(`[data-testid="${testId}"]`)
    return {container, queryByTestId}
  }
|}];

describe("JestDom", () => {
  let jsDomExpect = expect(div) |> convert;

  test("expect", () =>
    jsDomExpect |> Js.Undefined.return |> jestExpect |> toBeDefined
  );

  test("not_", () =>
    div
    |> expect
    |> not_
    |> convert
    |> Js.Undefined.return
    |> jestExpect
    |> toBeDefined
  );

  test("toBeDisabled", () => {
    let result = render({|<button disabled data-testid="button">x</button>|});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult |> toBeDisabled;
    let _ =
      (() => expectResult |> not_ |> toBeDisabled) |> jestExpect |> toThrow;

    pass;
  });

  test("not toBeDisabled", () => {
    let result = render({|<button data-testid="button">x</button>|});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult |> not_ |> toBeDisabled;
    let _ =
      (() => expectResult |> toBeDisabled) |> jestExpect |> toThrow;

    pass;
  });

  test("toBeEmpty", () => {
    let result = render({|<button data-testid="button"></button>|});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult |> toBeEmpty;
    let _ =
      (() => expectResult |> not_ |> toBeEmpty) |> jestExpect |> toThrow;

    pass;
  });

  test("not toBeEmpty", () => {
    let result = render({|<button data-testid="button">x</button>|});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult |> not_ |> toBeEmpty;
    let _ =
      (() => expectResult |> toBeEmpty) |> jestExpect |> toThrow;

    pass;
  });

  test("toBeInTheDocument", () => {
    let _ = [%bs.raw {|
      document.body.innerHTML = '<button data-testid="button"></button>'
    |}];

    let result: Dom.element =
      [%raw {|document.querySelector('[data-testid="button"]')|}];
    let expectResult = expect(result);

    let _ = expectResult |> toBeInTheDocument;
    let _ =
      (() => expectResult |> not_ |> toBeInTheDocument)
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("not toBeInTheDocument", () => {
    let _ = [%bs.raw {|
      document.body.innerHTML = '<button data-testid="button"></button>'
    |}];

    let result: Dom.element =
      [%raw {|document.querySelector('[data-testid="no-button"]')|}];
    let expectResult = expect(result);

    let _ = expectResult |> not_ |> toBeInTheDocument;
    let _ = (() => expectResult |> toBeInTheDocument) |> jestExpect |> toThrow;

    pass;
  });

  test("toBeVisible", () => {
    let result = render({|<button data-testid="button"></button>|});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult |> toBeVisible;
    let _ =
      (() => expectResult |> not_ |> toBeVisible) |> jestExpect |> toThrow;

    pass;
  });

  test("not toBeVisible", () => {
    let result = render({|
      <button style="display: none" data-testid="button">x</button>
    |});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult |> not_ |> toBeEmpty;
    let _ =
      (() => expectResult |> toBeEmpty) |> jestExpect |> toThrow;

    pass;
  });

  test("toContainElement", () => {
    let result = render({|
      <button data-testid="button"><span data-testid="element"></span></button>
    |});
    let expectResult = expect(result##queryByTestId("button"));
    let element = Js.Nullable.return(result##queryByTestId("element"));

    let _ = expectResult->toContainElement(element);
    let _ =
      (() => (expectResult |> not_)->toContainElement(element))
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("not toContainElement", () => {
    let result = render({|<button data-testid="button"></button>|});
    let expectResult = expect(result##queryByTestId("button"));
    let element = Js.Nullable.return(result##queryByTestId("element"));

    let _ = (expectResult |> not_)->toContainElement(element);
    let _ =
      (() => expectResult->toContainElement(element)) |> jestExpect |> toThrow;

    pass;
  });

  test("toContainHTML", () => {
    let result = render({|
      <button data-testid="button"><span data-testid="element"></span></button>
    |});
    let expectResult = expect(result##queryByTestId("button"));
    let html = {|<span data-testid="element"></span>|};

    let _ = expectResult->toContainHTML(html);
    let _ =
      (() => (expectResult |> not_)->toContainHTML(html))
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("not toContainHTML", () => {
    let result = render({|<button data-testid="button"></button>|});
    let expectResult = expect(result##queryByTestId("button"));
    let html = {|<span data-testid="element"></span>|};

    let _ = (expectResult |> not_)->toContainHTML(html);
    let _ = (() => expectResult->toContainHTML(html)) |> jestExpect |> toThrow;

    pass;
  });

  test("toHaveAttribute", () => {
    let result = render({|
      <button data-testid="button" type="submit"></button>
    |});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult->toHaveAttribute("type");
    let _ =
      (() => (expectResult |> not_)->toHaveAttribute("type"))
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("not toHaveAttribute", () => {
    let result = render({|<button data-testid="button"></button>|});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = (expectResult |> not_)->toHaveAttribute("type");
    let _ =
      (() => expectResult->toHaveAttribute("type")) |> jestExpect |> toThrow;

    pass;
  });

  test("toHaveAttributeWithValue", () => {
    let result = render({|
      <button data-testid="button" type="submit"></button>
    |});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult->toHaveAttributeWithValue("type", "submit");
    let _ =
      (() => (expectResult |> not_)->toHaveAttributeWithValue("type", "submit"))
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("not toHaveAttributeWithValue", () => {
    let result = render({|
      <button data-testid="button" type="button"></button>
    |});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = (expectResult |> not_)->toHaveAttributeWithValue("type", "submit");
    let _ =
      (() => expectResult->toHaveAttributeWithValue("type", "submit"))
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("toHaveClass", () => {
    let result = render({|<button class="btn" data-testid="button"></button>|});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult->toHaveClass("btn");
    let _ =
      (() => (expectResult |> not_)->toHaveClass("btn"))
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("not toHaveClass", () => {
    let result = render({|<button class="btn" data-testid="button"></button>|});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = (expectResult |> not_)->toHaveClass("not-btn");
    let _ =
      (() => expectResult->toHaveClass("not-btn")) |> jestExpect |> toThrow;

    pass;
  });

  test("toHaveClass2", () => {
    let result = render({|
      <button class="btn active" data-testid="button"></button>
    |});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult->toHaveClass2("btn", "active");
    let _ =
      (() => (expectResult |> not_)->toHaveClass2("btn", "active"))
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("not toHaveClass2", () => {
    let result = render({|
      <button class="btn secondary" data-testid="button"></button>
    |});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = (expectResult |> not_)->toHaveClass2("not-btn", "secondary");
    let _ =
      (() => expectResult->toHaveClass2("not-btn", "secondary"))
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("toHaveFocus", () => {
    let result = render({|<button data-testid="button"></button>|});
    let element = result##queryByTestId("button");
    let expectResult = expect(element);

    element |> focus;

    let _ = expectResult |> toHaveFocus;
    let _ =
      (() => expectResult |> not_ |> toHaveFocus) |> jestExpect |> toThrow;

    pass;
  });

  test("not toHaveFocus", () => {
    let result = render({|<button data-testid="button"></button>|});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult |> not_ |> toHaveFocus;
    let _ = (() => expectResult |> toHaveFocus) |> jestExpect |> toThrow;

    pass;
  });

  test("toHaveStyle", () => {
    let result = render({|
      <button data-testid="button" style="cursor: pointer"></button>
    |});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult->toHaveStyle("cursor: pointer");
    let _ =
      (() => (expectResult |> not_)->toHaveStyle("cursor: pointer"))
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("not toHaveStyle", () => {
    let result = render({|
      <button data-testid="button" style="cursor: pointer"></button>
    |});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = (expectResult |> not_)->toHaveStyle("color: rebeccapurple");
    let _ =
      (() => expectResult->toHaveStyle("color: rebeccapurple"))
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("toHaveTextContent", () => {
    let result = render({|<button data-testid="button">Submit</button>|});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = expectResult->toHaveTextContent(`Str("Submit"));
    let _ = expectResult->toHaveTextContent(`RegExp([%re "/Submit/"]));
    let _ =
      (() => (expectResult |> not_)->toHaveTextContent(`Str("Close")))
      |> jestExpect
      |> toThrow;
    let _ =
      (() => (expectResult |> not_)->toHaveTextContent(`RegExp([%re "/Close/"])))
      |> jestExpect
      |> toThrow;

    pass;
  });

  test("not toHaveTextContent", () => {
    let result = render({|<button data-testid="button">Submit</button>|});
    let expectResult = expect(result##queryByTestId("button"));

    let _ = (expectResult |> not_)->toHaveTextContent(`Str("Close"));
    let _ = (expectResult |> not_)->toHaveTextContent(`RegExp([%re "/Close/"]));
    let _ =
      (() => expectResult->toHaveTextContent(`Str("Submit")))
      |> jestExpect
      |> toThrow;
    let _ =
      (() => expectResult->toHaveTextContent(`RegExp([%re "/Submit/"])))
      |> jestExpect
      |> toThrow;

    pass;
  });
});
