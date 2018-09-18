type ex;
[@bs.val] external expect: Dom.element => ex = "";
[@bs.get] external not_: ex => ex = "not";

let toBeDisabled: ex => Jest.assertion;
let toBeEmpty: ex => Jest.assertion;
let toBeInTheDocument: ex => Jest.assertion;
let toBeVisible: ex => Jest.assertion;
let toContainElement: (ex, Js.Nullable.t(Dom.element)) => Jest.assertion;
let toContainHTML: (ex, string) => Jest.assertion;
let toHaveAttribute: (ex, string) => Jest.assertion;
let toHaveAttributeWithValue: (ex, string, string) => Jest.assertion;
let toHaveClass: (ex, string) => Jest.assertion;
let toHaveClass2: (ex, string, string) => Jest.assertion;
let toHaveFocus: ex => Jest.assertion;
let toHaveStyle: (ex, string) => Jest.assertion;
let toHaveTextContent:
  (ex, [ `RegExp(Js.Re.t) | `Str(string) ]) => Jest.assertion;
