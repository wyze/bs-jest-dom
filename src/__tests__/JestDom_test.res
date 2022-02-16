@@coverage(exclude_file)

open Jest
open JestDom
open Webapi.Dom
open Webapi.Dom.Element

let render = html => {
  let body = document->Document.createElement("body")

  body->setInnerHTML(html)

  document->Document.unsafeAsHtmlDocument->HtmlDocument.setBody(body)

  body
}

let queryByTestId = (element: Dom.element, id: string) =>
  switch element->querySelector(j`[data-testid="$(id)"]`) {
  | Some(el) => el
  | None => raise(Failure("Element not found"))
  }

afterAll(Bisect.Runtime.write_coverage_data)

afterEach(() =>
  switch document->Document.unsafeAsHtmlDocument->HtmlDocument.body {
  | Some(body) => body->setInnerHTML("")
  | None => raise(Failure("Not document body found"))
  }
)

test("toBeDisabled", () =>
  render(`<button disabled data-testid="button"></button>`)
  ->queryByTestId("button")
  ->expect
  ->toBeDisabled
)

test("not toBeDisabled", () =>
  render(`<button data-testid="button"></button>`)
  ->queryByTestId("button")
  ->expect
  ->not__
  ->toBeDisabled
)

test("toBeEnabled", () =>
  render(`<button data-testid="button"></button>`)->queryByTestId("button")->expect->toBeEnabled
)

test("not toBeEnabled", () =>
  render(`<button disabled data-testid="button"></button>`)
  ->queryByTestId("button")
  ->expect
  ->not__
  ->toBeEnabled
)

test("toBeEmptyDOMElement", () =>
  render(`<button data-testid="button"></button>`)
  ->queryByTestId("button")
  ->expect
  ->toBeEmptyDOMElement
)

test("not toBeEmptyDOMElement", () =>
  render(`<button disabled data-testid="button">Click me</button>`)
  ->queryByTestId("button")
  ->expect
  ->not__
  ->toBeEmptyDOMElement
)

test("toBeEmptyDOMElement", () =>
  render(`<button data-testid="button"></button>`)
  ->queryByTestId("button")
  ->expect
  ->toBeEmptyDOMElement
)

test("not toBeEmptyDOMElement", () =>
  render(`<button disabled data-testid="button">Click me</button>`)
  ->queryByTestId("button")
  ->expect
  ->not__
  ->toBeEmptyDOMElement
)

test("toBeInTheDocument", () =>
  render(`<button data-testid="button"></button>`)
  ->queryByTestId("button")
  ->expect
  ->toBeInTheDocument
)

test("not toBeInTheDocument", () =>
  render(`<button></button>`)->(
    _ => Document.createElement(document, "div")->expect->not__->toBeInTheDocument
  )
)

test("toBeInvalid", () =>
  render(`<input required data-testid="input" />`)->queryByTestId("input")->expect->toBeInvalid
)

test("not toBeInvalid", () =>
  render(`<input data-testid="input" />`)->queryByTestId("input")->expect->not__->toBeInvalid
)

test("toBeRequired", () =>
  render(`<input required data-testid="input" />`)->queryByTestId("input")->expect->toBeRequired
)

test("not toBeRequired", () =>
  render(`<input data-testid="input" />`)->queryByTestId("input")->expect->not__->toBeRequired
)

test("toBeValid", () =>
  render(`<input data-testid="input" />`)->queryByTestId("input")->expect->toBeValid
)

test("not toBeValid", () =>
  render(`<input required data-testid="input" />`)->queryByTestId("input")->expect->not__->toBeValid
)

test("toBeVisible", () =>
  render(`<button data-testid="button"></button>`)->queryByTestId("button")->expect->toBeVisible
)

test("not toBeVisible", () =>
  render(`<button style="display: none" data-testid="button"></button>`)
  ->queryByTestId("button")
  ->expect
  ->not__
  ->toBeVisible
)

test("toContainElement", () => {
  let element = render(`<span data-testid="span"><button></button></span>`)

  element
  ->queryByTestId("span")
  ->expect
  ->toContainElement(querySelector(document->Document.documentElement, "button"))
})

test("not toContainElement", () => {
  let element = render(`<span data-testid="span"></span>`)

  element
  ->queryByTestId("span")
  ->expect
  ->not__
  ->toContainElement(Document.createElement(document, "div")->Some)
})

test("toContainHTML", () =>
  render(`<span data-testid="span"><p></p></span>`)
  ->queryByTestId("span")
  ->expect
  ->toContainHTML("<p></p>")
)

test("not toContainHTML", () =>
  render(`<span data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->not__
  ->toContainHTML("<p></p>")
)

test("toHaveAttribute", () =>
  render(`<span class="empty" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->toHaveAttribute("class")
)

test("not toHaveAttribute", () =>
  render(`<span data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->not__
  ->toHaveAttribute("class")
)

test("toHaveAttribute with value", () =>
  render(`<span class="empty" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->toHaveAttribute("class", ~value="empty")
)

test("not toHaveAttribute with value", () =>
  render(`<span class="hidden" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->not__
  ->toHaveAttribute("class", ~value="empty")
)

test("toHaveClass (string)", () =>
  render(`<span class="empty" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->toHaveClass(#Str("empty"))
)

test("not toHaveClass (string)", () =>
  render(`<span data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->not__
  ->toHaveClass(#Str("empty"))
)

test("toHaveClass (list)", () =>
  render(`<span class="empty hidden" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->toHaveClass(#Lst(list{"empty", "hidden"}))
)

test("not toHaveClass (list)", () =>
  render(`<span class="hidden" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->not__
  ->toHaveClass(#Lst(list{"empty", "hidden"}))
)

test("toHaveClass (string) [exact]", () =>
  render(`<span class="empty hidden" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->toHaveClass(#Str("empty hidden"), ~options=HaveClass.makeOptions(~exact=true, ()))
)

test("not toHaveClass (string) [exact]", () =>
  render(`<span class="hidden" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->not__
  ->toHaveClass(#Str("empty"), ~options=HaveClass.makeOptions(~exact=true, ()))
)

test("toHaveFocus", () => {
  let element = render(`<span tabindex="1" data-testid="span"></span>`)

  queryByTestId(element, "span")->Element.unsafeAsHtmlElement->HtmlElement.focus

  element->queryByTestId("span")->expect->toHaveFocus
})

test("not toHaveFocus", () =>
  render(`<span data-testid="span"></span>`)->queryByTestId("span")->expect->not__->toHaveFocus
)

test("toHaveFormValues", () =>
  render(`<form data-testid="form"><label for="title">Job title</label><input type="text" id="title" name="title" value="CEO" /></form>`)
  ->queryByTestId("form")
  ->expect
  ->toHaveFormValues({"title": "CEO"})
)

test("not toHaveFormValues", () =>
  render(`<form data-testid="form"><label for="title">Job title</label><input type="text" id="title" name="title" value="CEO" /></form>`)
  ->queryByTestId("form")
  ->expect
  ->not__
  ->toHaveFormValues({"title": "CTO"})
)

test("toHaveStyle (string)", () =>
  render(`<span style="color: rebeccapurple" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->toHaveStyle(#Str("color: rebeccapurple"))
)

test("not toHaveStyle (string)", () =>
  render(`<span style="display: none" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->not__
  ->toHaveStyle(#Str("display: inline-block"))
)

test("toHaveStyle (object)", () =>
  render(`<span style="color: rebeccapurple" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->toHaveStyle(#Obj({"color": "rebeccapurple"}))
)

test("not toHaveStyle (object)", () =>
  render(`<span style="display: none" data-testid="span"></span>`)
  ->queryByTestId("span")
  ->expect
  ->not__
  ->toHaveStyle(#Obj({"display": "inline-block"}))
)

test("toHaveTextContent (string)", () =>
  render(`<span data-testid="span">Step 1 of 4</span>`)
  ->queryByTestId("span")
  ->expect
  ->toHaveTextContent(#Str("Step 1 of 4"))
)

test("not toHaveTextContent (string)", () =>
  render(`<span data-testid="span">Step 2 of 4</span>`)
  ->queryByTestId("span")
  ->expect
  ->not__
  ->toHaveTextContent(#Str("Step 1 of 4"))
)

test("toHaveTextContent (string) with options", () =>
  render(`<span data-testid="span">&nbsp;&nbsp;Step 1 of 4</span>`)
  ->queryByTestId("span")
  ->expect
  ->toHaveTextContent(
    #Str("  Step 1 of 4"),
    ~options=TextContent.makeOptions(~normalizeWhitespace=false, ()),
  )
)

test("toHaveTextContent (regex)", () =>
  render(`<span data-testid="span">Step 1 of 4</span>`)
  ->queryByTestId("span")
  ->expect
  ->toHaveTextContent(#RegExp(%re("/Step \\d of \\d/")))
)

test("not toHaveTextContent (regex)", () =>
  render(`<span data-testid="span">Step 2 of 4</span>`)
  ->queryByTestId("span")
  ->expect
  ->not__
  ->toHaveTextContent(#RegExp(%re("/^\\d of 4$/")))
)

test("toHaveValue (string)", () =>
  render(`<input data-testid="input" value="5" />`)
  ->queryByTestId("input")
  ->expect
  ->toHaveValue(#Str("5"))
)

test("not toHaveValue (string)", () =>
  render(`<input data-testid="input" />`)
  ->queryByTestId("input")
  ->expect
  ->not__
  ->toHaveValue(#Str("5"))
)

test("toHaveValue (num)", () =>
  render(`<input type="number" data-testid="input" value="5" />`)
  ->queryByTestId("input")
  ->expect
  ->toHaveValue(#Num(5))
)

test("not toHaveValue (num)", () =>
  render(`<input type="number" data-testid="input" />`)
  ->queryByTestId("input")
  ->expect
  ->not__
  ->toHaveValue(#Num(5))
)

test("toHaveValue (array)", () =>
  render(`<select data-testid="select" multiple><option value=""></option><option value="apple" selected>Apple</option><option value="peach">Peach</option><option value="orange" selected>Orange</option></select>`)
  ->queryByTestId("select")
  ->expect
  ->toHaveValue(#Arr(["apple", "orange"]))
)

test("not toHaveValue (list)", () =>
  render(`<select data-testid="select" multiple><option value=""></option><option value="apple" selected>Apple</option><option value="peach">Peach</option><option value="orange" selected>Orange</option></select>`)
  ->queryByTestId("select")
  ->expect
  ->not__
  ->toHaveValue(#Arr(["apple", "peach"]))
)

test("toHaveDisplayValue (string)", () =>
  render(`<input data-testid="input" value="Test" />`)
  ->queryByTestId("input")
  ->expect
  ->toHaveDisplayValue(#Str("Test"))
)

test("not toHaveDisplayValue (string)", () =>
  render(`<input data-testid="input" />`)
  ->queryByTestId("input")
  ->expect
  ->not__
  ->toHaveDisplayValue(#Str("Test"))
)

test("toHaveDisplayValue (regex)", () =>
  render(`<input data-testid="input" value="Test" />`)
  ->queryByTestId("input")
  ->expect
  ->toHaveDisplayValue(#RegExp(%re("/^Te/")))
)

test("not toHaveDisplayValue (regex)", () =>
  render(`<input data-testid="input" />`)
  ->queryByTestId("input")
  ->expect
  ->not__
  ->toHaveDisplayValue(#RegExp(%re("/Tt/")))
)

test("toHaveDisplayValue (array)", () =>
  render(`<select data-testid="select" multiple><option value=""></option><option value="apple" selected>Apple</option><option value="peach">Peach</option><option value="orange" selected>Orange</option></select>`)
  ->queryByTestId("select")
  ->expect
  ->toHaveDisplayValue(#Arr(["Apple", "Orange"]))
)

test("not toHaveDisplayValue (array)", () =>
  render(`<select data-testid="select" multiple><option value=""></option><option value="apple" selected>Apple</option><option value="peach">Peach</option><option value="orange" selected>Orange</option></select>`)
  ->queryByTestId("select")
  ->expect
  ->not__
  ->toHaveDisplayValue(#Arr(["Apple", "Peach"]))
)

test("toBeChecked", () =>
  render(`<input type="checkbox" checked data-testid="input" />`)
  ->queryByTestId("input")
  ->expect
  ->toBeChecked
)

test("not toBeChecked", () =>
  render(`<input type="checkbox" data-testid="input" />`)
  ->queryByTestId("input")
  ->expect
  ->not__
  ->toBeChecked
)

test("toBePartiallyChecked", () =>
  render(`<input type="checkbox" aria-checked="mixed" data-testid="input" />`)
  ->queryByTestId("input")
  ->expect
  ->toBePartiallyChecked
)

test("not toBePartiallyChecked", () =>
  render(`<input type="checkbox" checked data-testid="input" />`)
  ->queryByTestId("input")
  ->expect
  ->not__
  ->toBePartiallyChecked
)

test("toHaveDescription (string)", () =>
  render(`<span><button data-testid="button" aria-label="Close" aria-describedby="description-close">X</button><div id="description-close">Closing will discard any changes</div></span>`)
  ->queryByTestId("button")
  ->expect
  ->toHaveDescription(#Str("Closing will discard any changes"))
)

test("not toHaveDescription (string)", () =>
  render(`<span><button data-testid="button" aria-label="Close" aria-describedby="description-close">X</button><div id="description-close">Closing will discard any changes</div></span>`)
  ->queryByTestId("button")
  ->expect
  ->not__
  ->toHaveDescription(#Str("Other description"))
)

test("toHaveDescription (regex)", () =>
  render(`<span><button data-testid="button" aria-label="Close" aria-describedby="description-close">X</button><div id="description-close">Closing will discard any changes</div></span>`)
  ->queryByTestId("button")
  ->expect
  ->toHaveDescription(#RegExp(%re("/will discard/")))
)

test("not toHaveDescription (regex)", () =>
  render(`<span><button data-testid="button" aria-label="Close" aria-describedby="description-close">X</button><div id="description-close">Closing will discard any changes</div></span>`)
  ->queryByTestId("button")
  ->expect
  ->not__
  ->toHaveDescription(#RegExp(%re("/^Other/")))
)
