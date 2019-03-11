# bs-jest-dom &middot; [![Build Status][circleci-image]][circleci-url] [![npm][npm-image]][npm-url] [![Coveralls][coveralls-image]][coveralls-url]

> [BuckleScript](//github.com/BuckleScript/bucklescript) bindings for [jest-dom](//github.com/gnapse/jest-dom).

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
  let component = ReasonReact.statelessComponent("Heading");

  let make = (~text, _children) => {
    ...component,
    render: _self =>
      <h1> {ReasonReact.string(text)} </h1>,
  };
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

### [v2.0.0](https://github.com/wyze/bs-jest-dom/releases/tag/v2.0.0) (2019-03-11)

* Rewrite to better interface with bs-jest ([@wyze](https://github.com/wyze) in [010b440](https://github.com/wyze/bs-jest-dom/commit/010b440))
* Meta file updates ([@wyze](https://github.com/wyze) in [3484f0d](https://github.com/wyze/bs-jest-dom/commit/3484f0d))
* Upgrade dependencies ([@wyze](https://github.com/wyze) in [0323b1a](https://github.com/wyze/bs-jest-dom/commit/0323b1a))
* Update yarn lock with integrity hashes ([@caulagi](https://github.com/caulagi) in [#1](https://github.com/wyze/bs-jest-dom/pull/1))

## License

MIT © [Neil Kistner](https://neilkistner.com)

[circleci-image]: https://img.shields.io/circleci/project/github/wyze/bs-jest-dom.svg?style=flat-square
[circleci-url]: https://circleci.com/gh/wyze/bs-jest-dom

[npm-image]: https://img.shields.io/npm/v/bs-jest-dom.svg?style=flat-square
[npm-url]: https://npm.im/bs-jest-dom

[coveralls-image]: https://img.shields.io/coveralls/github/wyze/bs-jest-dom.svg?style=flat-square
[coveralls-url]: https://coveralls.io/github/wyze/bs-jest-dom
