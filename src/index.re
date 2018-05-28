let toString = ReasonReact.string;

module App = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {
    ...component,
    render: _self => <div className="title"> (toString("Hello world")) </div>,
  };
};

ReactDOMRe.renderToElementWithId(<App />, "main");