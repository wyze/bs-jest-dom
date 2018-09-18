# bs-jest-dom

[![Build Status][travis-image]][travis-url]
[![npm][npm-image]][npm-url]
[![Coveralls][coveralls-image]][coveralls-url]

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
  "bs-dev-dependencies": [
    "bs-jest-dom"
  ]
}
```

#### With [`bs-jest`](//github.com/glennsl/bs-jest) and [`bs-react-testing-library`](//github.com/wyze/bs-react-testing-library)

```ocaml
/* A_test.re */

open Jest;
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

test("renders with text", () =>
  <Heading text="Hello, World!" />
  |> render
  |> getByText(~matcher=`Str("Hello, World!"))
  |> expect
  |> toBeInTheDocument
);
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

## License

MIT © [Neil Kistner](https://neilkistner.com)

[travis-image]: https://img.shields.io/travis/wyze/bs-jest-dom.svg?style=flat-square
[travis-url]: https://travis-ci.org/wyze/bs-jest-dom

[npm-image]: https://img.shields.io/npm/v/bs-jest-dom.svg?style=flat-square
[npm-url]: https://npm.im/bs-jest-dom

[coveralls-image]: https://img.shields.io/coveralls/github/wyze/bs-jest-dom.svg?style=flat-square
[coveralls-url]: https://coveralls.io/github/wyze/bs-jest-dom
