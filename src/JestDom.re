/* Bring in all of the matchers. */
[%bs.raw {|require('jest-dom/extend-expect')|}];

type ex;
[@bs.val] external expect: Dom.element => ex = "";

[@bs.get] external not_: ex => ex = "not";

[@bs.send.pipe: ex] external toBeDisabled_: unit = "toBeDisabled";

[@bs.send.pipe: ex] external toBeEmpty_: unit = "toBeEmpty";

[@bs.send.pipe: ex] external toBeInTheDocument_: unit = "toBeInTheDocument";

[@bs.send.pipe: ex] external toBeVisible_: unit = "toBeVisible";

[@bs.send.pipe: ex]
external toContainElement_: Js.Nullable.t(Dom.element) => unit =
  "toContainElement";

[@bs.send.pipe: ex] external toContainHTML_: string => unit = "toContainHTML";

[@bs.send.pipe: ex]
external toHaveAttribute_: string => unit = "toHaveAttribute";

[@bs.send.pipe: ex]
external toHaveAttributeWithValue_: (string, string) => unit =
  "toHaveAttribute";

[@bs.send.pipe: ex] external toHaveClass_: string => unit = "toHaveClass";

[@bs.send.pipe: ex]
external toHaveClass2_: (string, string) => unit = "toHaveClass";

[@bs.send.pipe: ex] external toHaveFocus_: unit = "toHaveFocus";

[@bs.send.pipe: ex] external toHaveStyle_: string => unit = "toHaveStyle";

[@bs.send.pipe: ex]
external toHaveTextContent_:
  ([@bs.unwrap] [ | `Str(string) | `RegExp(Js.Re.t)]) => unit =
  "toHaveTextContent";

let pass = _ => Jest.pass;

let toBeDisabled = ex => ex |> toBeDisabled_ |> pass;

let toBeEmpty = ex => ex |> toBeEmpty_ |> pass;

let toBeInTheDocument = ex => ex |> toBeInTheDocument_ |> pass;

let toBeVisible = ex => ex |> toBeVisible_ |> pass;

let toContainElement = (ex, el) => ex |> toContainElement_(el) |> pass;

let toContainHTML = (ex, html) => ex |> toContainHTML_(html) |> pass;

let toHaveAttribute = (ex, attribute) =>
  ex |> toHaveAttribute_(attribute) |> pass;

let toHaveAttributeWithValue = (ex, attribute, value) =>
  ex |> toHaveAttributeWithValue_(attribute, value) |> pass;

let toHaveClass = (ex, value) => ex |> toHaveClass_(value) |> pass;

let toHaveClass2 = (ex, value1, value2) =>
  ex |> toHaveClass2_(value1, value2) |> pass;

let toHaveFocus = ex => ex |> toHaveFocus_ |> pass;

let toHaveStyle = (ex, style) => ex |> toHaveStyle_(style) |> pass;

let toHaveTextContent = (ex, text) => ex |> toHaveTextContent_(text) |> pass;
