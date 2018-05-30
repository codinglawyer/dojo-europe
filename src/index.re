let toString = ReasonReact.string;

module ComposableMap = {
  [@bs.deriving abstract]
  type projectionConfigT = {
    scale: int,
    rotation: array(int),
  };
  [@bs.deriving abstract]
  type jsProps = {
    projectionConfig: projectionConfigT,
    width: int,
    height: int,
    style: ReactDOMRe.Style.t,
  };
  [@bs.module "react-simple-maps"]
  external composableMap : ReasonReact.reactClass = "ComposableMap";
  let make = (~projectionConfig, ~width, ~height, ~style, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=composableMap,
      ~props=jsProps(~projectionConfig, ~width, ~height, ~style),
      children,
    );
};

module App = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {
    ...component,
    render: _self =>
      <div className="title">
        (toString("Hello wor"))
        <ComposableMap
          projectionConfig=(
            ComposableMap.projectionConfigT(
              ~scale=205,
              ~rotation=[|(-11), 0, 0|],
            )
          )
          width=980
          height=551
          style=(ReactDOMRe.Style.make(~width="100%", ~height="auto", ()))
        />
      </div>,
  };
};

ReactDOMRe.renderToElementWithId(<App />, "main");