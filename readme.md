# bs-jest-dom &middot; [![Build Status][actions-image]][actions-url] [![npm][npm-image]][npm-url] [![Codecov][codecov-image]][codecov-url]

> [BuckleScript](//github.com/BuckleScript/bucklescript) bindings for [jest-dom](//github.com/testing-library/jest-dom).

## Installation

```sh
$ yarn add --dev bs-jest-dom

# or..

$ npm install --save-dev bs-jest-dom
```

## Usage

#### Add to `bsconfig.json`

```json
{
  "bs-dev-dependencies": ["bs-jest-dom"]
}
```

#### With [`bs-jest`](//github.com/glennsl/bs-jest) and [`bs-react-testing-library`](//github.com/wyze/bs-react-testing-library)

```ocaml
/* Heading_test.re */

open Jest;
open Expect;
open JestDom;
open ReactTestingLibrary;

module Heading = {
  [@react.component]
  let make = (~text) => <h1> {ReasonReact.string(text)} </h1>;
};

test("renders in the document", () =>
  <Heading text="Hello, World!" />
  |> render
  |> getByText(~matcher=`Str("Hello, World!"))
  |> expect
  |> toBeInTheDocument
);
```

#### With [`bs-jest`](//github.com/glennsl/bs-jest) and [`bs-webapi`](//github.com/reasonml-community/bs-webapi-incubator)

```ocaml
/* Heading_test.re */

open Jest;
open Expect;
open JestDom;
open Webapi.Dom;
open Webapi.Dom.Element;

test("heading is visible", () => {
  let div = Document.createElement("div", document);

  div->setInnerHTML("<h1>Hello, World!</h1>");

  div
  |> querySelector("h1")
  |> expect
  |> toBeVisible;
});
```

## Examples

See [`src/__tests__`](src/__tests__) for some examples.

## Development

```sh
$ git clone https://github.com/wyze/bs-jest-dom.git
$ cd bs-jest-dom
$ yarn # or `npm install`
```

## Build

```sh
$ yarn build
```

## Test

```sh
$ yarn test
```

## Change Log

> [Full Change Log](changelog.md)

### [v3.0.0](https://github.com/wyze/bs-jest-dom/releases/tag/v3.0.0) (2020-04-18)

* Add bisect_ppx to bs-dev-deps ([@wyze](https://github.com/wyze) in [#16](https://github.com/wyze/bs-jest-dom/pull/16))
* Run refmt (again) on the project ([@wyze](https://github.com/wyze) in [1ae8ee4](https://github.com/wyze/bs-jest-dom/commit/1ae8ee4))
* Upgrade to jest-dom v5.5.0 ([@wyze](https://github.com/wyze) in [#15](https://github.com/wyze/bs-jest-dom/pull/15))
* Update toHaveClass/toHaveTextContent method signatures ([@wyze](https://github.com/wyze) in [#14](https://github.com/wyze/bs-jest-dom/pull/14))
* Fix GitHub security alerts ([@wyze](https://github.com/wyze) in [d2594c2](https://github.com/wyze/bs-jest-dom/commit/d2594c2))
* Switch to GitHub actions ([@wyze](https://github.com/wyze) in [#13](https://github.com/wyze/bs-jest-dom/pull/13))

## License

MIT © [Neil Kistner](https://neilkistner.com)

[actions-image]: https://img.shields.io/github/workflow/status/wyze/bs-jest-dom/CI.svg?style=flat-square
[actions-url]: https://github.com/wyze/bs-jest-dom/actions

[npm-image]: https://img.shields.io/npm/v/bs-jest-dom.svg?style=flat-square
[npm-url]: https://npm.im/bs-jest-dom

[codecov-image]: https://img.shields.io/codecov/c/github/wyze/bs-jest-dom.svg?style=flat-square
[codecov-url]: https://codecov.io/github/wyze/bs-jest-dom
