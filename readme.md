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

### [v4.1.0](https://github.com/wyze/bs-jest-dom/releases/tag/v4.1.0) (2020-06-13)

* Add toBeEmptyDOMElement in favor of toBeEmpty ([@wyze](https://github.com/wyze) in [456326f](https://github.com/wyze/bs-jest-dom/commit/456326f))
* Add toBePartiallyChecked matcher ([@wyze](https://github.com/wyze) in [688dbbc](https://github.com/wyze/bs-jest-dom/commit/688dbbc))
* Allow regex in toHaveDisplayValue matcher ([@wyze](https://github.com/wyze) in [7bfdbbf](https://github.com/wyze/bs-jest-dom/commit/7bfdbbf))
* Add toHaveDescription matcher ([@wyze](https://github.com/wyze) in [3049f11](https://github.com/wyze/bs-jest-dom/commit/3049f11))
* Upgrade dependencies ([@wyze](https://github.com/wyze) in [9c564df](https://github.com/wyze/bs-jest-dom/commit/9c564df))
* Update peerDependency for @glennsl/bs-jest ([@wyze](https://github.com/wyze) in [af104b7](https://github.com/wyze/bs-jest-dom/commit/af104b7))

## License

MIT © [Neil Kistner](https://neilkistner.com)

[actions-image]: https://img.shields.io/github/workflow/status/wyze/bs-jest-dom/CI.svg?style=flat-square
[actions-url]: https://github.com/wyze/bs-jest-dom/actions

[npm-image]: https://img.shields.io/npm/v/bs-jest-dom.svg?style=flat-square
[npm-url]: https://npm.im/bs-jest-dom

[codecov-image]: https://img.shields.io/codecov/c/github/wyze/bs-jest-dom.svg?style=flat-square
[codecov-url]: https://codecov.io/github/wyze/bs-jest-dom
