[@coverage exclude_file];

open Jest;
// open Expect;
open JestDom;
open Webapi.Dom;
open Webapi.Dom.Element;

let render = html => {
  let body = Document.createElement("body", document);

  body->setInnerHTML(html);

  document->Document.unsafeAsHtmlDocument->HtmlDocument.setBody(body);

  body;
};

let queryByTestId = (id: string, element: Dom.element) =>
  switch (element |> querySelector({j|[data-testid="$(id)"]|j})) {
  | Some(el) => el
  | None => raise(Failure("Element not found"))
  };

afterAll(Bisect.Runtime.write_coverage_data);

afterEach(() =>
  switch (document->Document.unsafeAsHtmlDocument->HtmlDocument.body) {
  | Some(body) => body->setInnerHTML("")
  | None => raise(Failure("Not document body found"))
  }
);

// test("toBeDisabled2", () =>
//   render({|<button disabled data-testid="button"></button>|})
//   |> queryByTestId("button")
//   |> expect2
//   |> toBeDisabled2
// );

// test("not toBeDisabled2", () =>
//   render({|<button data-testid="button"></button>|})
//   |> queryByTestId("button")
//   |> expect2
//   |> n
//   |> toBeDisabled2
// );

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
  |> not_
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
  |> not_
  |> toBeEnabled
);

test("toBeEmpty", () =>
  render({|<button data-testid="button"></button>|})
  |> queryByTestId("button")
  |> expect
  |> toBeEmpty
);

test("not toBeEmpty", () =>
  render({|<button disabled data-testid="button">Click me</button>|})
  |> queryByTestId("button")
  |> expect
  |> not_
  |> toBeEmpty
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
      Document.createElement("div", document)
      |> expect
      |> not_
      |> toBeInTheDocument
  )
);

test("toBeInvalid", () =>
  render({|<input required data-testid="input" />|})
  |> queryByTestId("input")
  |> expect
  |> toBeInvalid
);

test("not toBeInvalid", () =>
  render({|<input data-testid="input" />|})
  |> queryByTestId("input")
  |> expect
  |> not_
  |> toBeInvalid
);

test("toBeRequired", () =>
  render({|<input required data-testid="input" />|})
  |> queryByTestId("input")
  |> expect
  |> toBeRequired
);

test("not toBeRequired", () =>
  render({|<input data-testid="input" />|})
  |> queryByTestId("input")
  |> expect
  |> not_
  |> toBeRequired
);

test("toBeValid", () =>
  render({|<input data-testid="input" />|})
  |> queryByTestId("input")
  |> expect
  |> toBeValid
);

test("not toBeValid", () =>
  render({|<input required data-testid="input" />|})
  |> queryByTestId("input")
  |> expect
  |> not_
  |> toBeValid
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
  |> not_
  |> toBeVisible
);

test("toContainElement", () => {
  let element = render({|<span data-testid="span"><button></button></span>|});

  element
  |> queryByTestId("span")
  |> expect
  |> (
       switch (document->Document.documentElement |> querySelector("button")) {
       | Some(el) => el
       | None => raise(Failure("Element not found"))
       }
     )
     ->toContainElement;
});

test("not toContainElement", () => {
  let element = render({|<span data-testid="span"></span>|});

  element
  |> queryByTestId("span")
  |> expect
  |> not_
  |> Document.createElement("div", document)->toContainElement;
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
  |> not_
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
  |> not_
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
  |> not_
  |> toHaveAttribute("class", ~value="empty")
);

// test("toHaveClass (string)", () =>
//   render({|<span class="empty" data-testid="span"></span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> toHaveClass(`Str("empty"))
// );

// test("not toHaveClass (string)", () =>
//   render({|<span data-testid="span"></span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> not_
//   |> toHaveClass(`Str("empty"))
// );

// test("toHaveClass (list)", () =>
//   render({|<span class="empty hidden" data-testid="span"></span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> toHaveClass(`Lst(["empty", "hidden"]))
// );

// test("not toHaveClass (list)", () =>
//   render({|<span class="hidden" data-testid="span"></span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> not_
//   |> toHaveClass(`Lst(["empty", "hidden"]))
// );

// test("toHaveFocus", () => {
//   let element = render({|<span tabindex="1" data-testid="span"></span>|});

//   "span"
//   ->queryByTestId(element)
//   ->Element.unsafeAsHtmlElement
//   ->HtmlElement.focus;

//   element |> queryByTestId("span") |> expect |> toHaveFocus;
// });

// test("not toHaveFocus", () =>
//   render({|<span data-testid="span"></span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> not_
//   |> toHaveFocus
// );

// test("toHaveFormValues", () =>
//   render(
//     {|<form data-testid="form"><label for="title">Job title</label><input type="text" id="title" name="title" value="CEO" /></form>|},
//   )
//   |> queryByTestId("form")
//   |> expect
//   |> toHaveFormValues({"title": "CEO"})
// );

// test("not toHaveFormValues", () =>
//   render(
//     {|<form data-testid="form"><label for="title">Job title</label><input type="text" id="title" name="title" value="CEO" /></form>|},
//   )
//   |> queryByTestId("form")
//   |> expect
//   |> not_
//   |> toHaveFormValues({"title": "CTO"})
// );

// test("toHaveStyle", () =>
//   render({|<span style="color: rebeccapurple" data-testid="span"></span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> toHaveStyle("color: rebeccapurple")
// );

// test("not toHaveStyle", () =>
//   render({|<span style="display: none" data-testid="span"></span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> not_
//   |> toHaveStyle("display: inline-block")
// );

// test("toHaveTextContent (string)", () =>
//   render({|<span data-testid="span">Step 1 of 4</span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> toHaveTextContent(`Str("Step 1 of 4"))
// );

// test("not toHaveTextContent (string)", () =>
//   render({|<span data-testid="span">Step 2 of 4</span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> not_
//   |> toHaveTextContent(`Str("Step 1 of 4"))
// );

// test("toHaveTextContent (string) with options", () => {
//   let options = TextContent.makeOptions(~normalizeWhitespace=false, ());

//   render({|<span data-testid="span">&nbsp;&nbsp;Step 1 of 4</span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> toHaveTextContent(`Str("  Step 1 of 4"), ~options);
// });

// test("toHaveTextContent (regex)", () =>
//   render({|<span data-testid="span">Step 1 of 4</span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> toHaveTextContent(`RegExp([%bs.re "/Step \\d of \\d/"]))
// );

// test("not toHaveTextContent (regex)", () =>
//   render({|<span data-testid="span">Step 2 of 4</span>|})
//   |> queryByTestId("span")
//   |> expect
//   |> not_
//   |> toHaveTextContent(`RegExp([%bs.re "/^\\d of 4$/"]))
// );

// test("toHaveValue (string)", () =>
//   render({|<input data-testid="input" value="5" />|})
//   |> queryByTestId("input")
//   |> expect
//   |> toHaveValue(`Str("5"))
// );

// test("not toHaveValue (string)", () =>
//   render({|<input data-testid="input" />|})
//   |> queryByTestId("input")
//   |> expect
//   |> not_
//   |> toHaveValue(`Str("5"))
// );

// test("toHaveValue (num)", () =>
//   render({|<input type="number" data-testid="input" value="5" />|})
//   |> queryByTestId("input")
//   |> expect
//   |> toHaveValue(`Num(5))
// );

// test("not toHaveValue (num)", () =>
//   render({|<input type="number" data-testid="input" />|})
//   |> queryByTestId("input")
//   |> expect
//   |> not_
//   |> toHaveValue(`Num(5))
// );

// test("toHaveValue (list)", () =>
//   render(
//     {|<select data-testid="select" multiple><option value=""></option><option value="apple" selected>Apple</option><option value="peach">Peach</option><option value="orange" selected>Orange</option></select>|},
//   )
//   |> queryByTestId("select")
//   |> expect
//   |> toHaveValue(`Lst(["apple", "orange"]))
// );

// test("not toHaveValue (list)", () =>
//   render(
//     {|<select data-testid="select" multiple><option value=""></option><option value="apple" selected>Apple</option><option value="peach">Peach</option><option value="orange" selected>Orange</option></select>|},
//   )
//   |> queryByTestId("select")
//   |> expect
//   |> not_
//   |> toHaveValue(`Lst(["apple", "peach"]))
// );

// test("toHaveDisplayValue (string)", () =>
//   render({|<input data-testid="input" value="Test" />|})
//   |> queryByTestId("input")
//   |> expect
//   |> toHaveDisplayValue(`Str("Test"))
// );

// test("not toHaveDisplayValue (string)", () =>
//   render({|<input data-testid="input" />|})
//   |> queryByTestId("input")
//   |> expect
//   |> not_
//   |> toHaveDisplayValue(`Str("Test"))
// );

// test("toHaveDisplayValue (list)", () =>
//   render(
//     {|<select data-testid="select" multiple><option value=""></option><option value="apple" selected>Apple</option><option value="peach">Peach</option><option value="orange" selected>Orange</option></select>|},
//   )
//   |> queryByTestId("select")
//   |> expect
//   |> toHaveDisplayValue(`Lst(["Apple", "Orange"]))
// );

// test("not toHaveDisplayValue (list)", () =>
//   render(
//     {|<select data-testid="select" multiple><option value=""></option><option value="apple" selected>Apple</option><option value="peach">Peach</option><option value="orange" selected>Orange</option></select>|},
//   )
//   |> queryByTestId("select")
//   |> expect
//   |> not_
//   |> toHaveDisplayValue(`Lst(["Apple", "Peach"]))
// );

// test("toBeChecked", () =>
//   render({|<input type="checkbox" checked data-testid="input" />|})
//   |> queryByTestId("input")
//   |> expect
//   |> toBeChecked
// );

// test("not toBeChecked", () =>
//   render({|<input type="checkbox" data-testid="input" />|})
//   |> queryByTestId("input")
//   |> expect
//   |> not_
//   |> toBeChecked
// );
