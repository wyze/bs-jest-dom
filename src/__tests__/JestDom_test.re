[%bs.raw {|require('jest-dom/extend-expect')|}];

open Jest;
open Expect;
open JestDom;
open Webapi.Dom;
open Webapi.Dom.Element;

let render = html => {
  let body = Document.createElement("body", document);

  body->setInnerHTML(html);

  document->Document.unsafeAsHtmlDocument->HtmlDocument.setBody(body);

  body;
};

let queryByTestId = (id: string) =>
  querySelector({j|[data-testid="$(id)"]|j});

afterEach(() =>
  switch (document->Document.unsafeAsHtmlDocument->HtmlDocument.body) {
  | Some(body) => body->setInnerHTML("")
  | None => raise(Failure("Not document body found"))
  }
);

test("toBeDisabled", () =>
  render({|<button disabled data-testid="button"></button>|})
  |> queryByTestId("button")
  |> expect
  |> toBeDisabled
);

test("not toBeDisabled", () =>
  render({|<button data-testid="button"></button>|})
  |> queryByTestId("button")
  |> expect
  |> not
  |> toBeDisabled
);

test("toBeEnabled", () =>
  render({|<button data-testid="button"></button>|})
  |> queryByTestId("button")
  |> expect
  |> toBeEnabled
);

test("not toBeEnabled", () =>
  render({|<button disabled data-testid="button"></button>|})
  |> queryByTestId("button")
  |> expect
  |> not
  |> toBeEnabled
);

test("toBeInTheDocument", () =>
  render({|<button data-testid="button"></button>|})
  |> queryByTestId("button")
  |> expect
  |> toBeInTheDocument
);

test("not toBeInTheDocument", () =>
  render({|<button></button>|})
  |> (
    _ =>
      Document.createElement("div", document)->Some
      |> expect
      |> not
      |> toBeInTheDocument
  )
);

test("toBeVisible", () =>
  render({|<button data-testid="button"></button>|})
  |> queryByTestId("button")
  |> expect
  |> toBeVisible
);

test("not toBeVisible", () =>
  render({|<button style="display: none" data-testid="button"></button>|})
  |> queryByTestId("button")
  |> expect
  |> not
  |> toBeVisible
);

test("toContainElement", () => {
  let element = render({|<span data-testid="span"><button></button></span>|});

  element
  |> queryByTestId("span")
  |> expect
  |> (document->Document.documentElement |> querySelector("button"))
     ->toContainElement;
});

test("not toContainElement", () => {
  let element = render({|<span data-testid="span"></span>|});

  element
  |> queryByTestId("span")
  |> expect
  |> not
  |> Document.createElement("div", document)->Some->toContainElement;
});

test("toContainHTML", () =>
  render({|<span data-testid="span"><p></p></span>|})
  |> queryByTestId("span")
  |> expect
  |> toContainHTML("<p></p>")
);

test("not toContainHTML", () =>
  render({|<span data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> not
  |> toContainHTML("<p></p>")
);

test("toHaveAttribute", () =>
  render({|<span class="empty" data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> toHaveAttribute("class")
);

test("not toHaveAttribute", () =>
  render({|<span data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> not
  |> toHaveAttribute("class")
);

test("toHaveAttribute with value", () =>
  render({|<span class="empty" data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> toHaveAttribute("class", ~value="empty")
);

test("not toHaveAttribute with value", () =>
  render({|<span class="hidden" data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> not
  |> toHaveAttribute("class", ~value="empty")
);

test("toHaveClass", () =>
  render({|<span class="empty" data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> toHaveClass("empty")
);

test("not toHaveClass", () =>
  render({|<span data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> not
  |> toHaveClass("empty")
);

test("toHaveClassMany", () =>
  render({|<span class="empty hidden" data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> toHaveClassMany(["empty", "hidden"])
);

test("not toHaveClassMany", () =>
  render({|<span class="hidden" data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> not
  |> toHaveClassMany(["empty", "hidden"])
);

test("toHaveFocus", () => {
  let element = render({|<span tabindex="1" data-testid="span"></span>|});

  switch (element |> queryByTestId("span")) {
  | Some(el) => el->Element.unsafeAsHtmlElement->HtmlElement.focus
  | None => raise(Failure("Element not found"))
  };

  element |> queryByTestId("span") |> expect |> toHaveFocus;
});

test("not toHaveFocus", () =>
  render({|<span data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> not
  |> toHaveFocus
);

test("toHaveFormValues", () =>
  render(
    {|<form data-testid="form"><label for="title">Job title</label><input type="text" id="title" name="title" value="CEO" /></form>|},
  )
  |> queryByTestId("form")
  |> expect
  |> toHaveFormValues({"title": "CEO"})
);

test("not toHaveFormValues", () =>
  render(
    {|<form data-testid="form"><label for="title">Job title</label><input type="text" id="title" name="title" value="CEO" /></form>|},
  )
  |> queryByTestId("form")
  |> expect
  |> not
  |> toHaveFormValues({"title": "CTO"})
);

test("toHaveStyle", () =>
  render({|<span style="color: rebeccapurple" data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> toHaveStyle("color: rebeccapurple")
);

test("not toHaveStyle", () =>
  render({|<span style="display: none" data-testid="span"></span>|})
  |> queryByTestId("span")
  |> expect
  |> not
  |> toHaveStyle("display: inline-block")
);

test("toHaveTextContent", () =>
  render({|<span data-testid="span">Step 1 of 4</span>|})
  |> queryByTestId("span")
  |> expect
  |> toHaveTextContent("Step 1 of 4")
);

test("not toHaveTextContent", () =>
  render({|<span data-testid="span">Step 2 of 4</span>|})
  |> queryByTestId("span")
  |> expect
  |> not
  |> toHaveTextContent("Step 1 of 4")
);

test("toHaveTextContent with options", () => {
  let options = TextContent.makeOptions(~normalizeWhitespace=false, ());

  render({|<span data-testid="span">&nbsp;&nbsp;Step 1 of 4</span>|})
  |> queryByTestId("span")
  |> expect
  |> toHaveTextContent("  Step 1 of 4", ~options);
});

test("toHaveTextContentRe", () =>
  render({|<span data-testid="span">Step 1 of 4</span>|})
  |> queryByTestId("span")
  |> expect
  |> toHaveTextContentRe([%bs.re "/Step \\d of \\d/"])
);

test("not toHaveTextContentRe", () =>
  render({|<span data-testid="span">Step 2 of 4</span>|})
  |> queryByTestId("span")
  |> expect
  |> not
  |> toHaveTextContentRe([%bs.re "/^\\d of 4$/"])
);
