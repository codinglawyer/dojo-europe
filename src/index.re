
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

module ZoomableGroup = {
  [@bs.deriving abstract]
  type jsProps = {
    center: array(int),
    disablePanning: bool,
  };
  [@bs.module "react-simple-maps"]
  external zoomableGroup : ReasonReact.reactClass = "ZoomableGroup";
  let make = (~center, ~disablePanning=false, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=zoomableGroup,
      ~props=jsProps(~center, ~disablePanning),
      children,
    );
};

module Geographies = {
  [@bs.deriving abstract]
  type jsProps = {geography: string};
  [@bs.module "react-simple-maps"]
  external geographies : ReasonReact.reactClass = "Geographies";
  let make = (~geography, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=geographies,
      ~props=jsProps(~geography),
      children,
    );
};

module Geography = {
  [@bs.deriving abstract]
  type geographyT = {id: string};
  type projectionT;
  [@bs.deriving abstract]
  type styleT = {
    default: ReactDOMRe.Style.t,
    hover: ReactDOMRe.Style.t,
    pressed: ReactDOMRe.Style.t,
  };
  [@bs.deriving abstract]
  type jsProps = {
    geography: geographyT,
    projection: projectionT,
    style: styleT,
  };
  [@bs.module "react-simple-maps"]
  external geographyComponent : ReasonReact.reactClass = "Geography";
  let make = (~geography, ~projection, ~style, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=geographyComponent,
      ~props=jsProps(~geography, ~projection, ~style),
      children,
    );
};

module Markers = {
  [@bs.module "react-simple-maps"]
  external markersComponent : ReasonReact.reactClass = "Markers";
  let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=markersComponent,
      ~props=(),
      children,
    );
};

module Marker = {
  [@bs.deriving abstract]
  type markerT = {
    markerOffset: int,
    coordinates: array(float),
    name: string,
  };
  [@bs.deriving abstract]
  type styleT = {
    default: ReactDOMRe.Style.t,
    hover: ReactDOMRe.Style.t,
    pressed: ReactDOMRe.Style.t,
  };
  [@bs.deriving abstract]
  type jsProps = {
    style: styleT,
    marker: markerT,
  };
  [@bs.module "react-simple-maps"]
  external markerComponent : ReasonReact.reactClass = "Marker";
  let make = (~style, ~marker, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=markerComponent,
      ~props=jsProps(~style, ~marker),
      children,
    );
};

module App = {
  let component = ReasonReact.statelessComponent("App");
  let styleC =
    Geography.styleT(
      ~default=
        ReactDOMRe.Style.make(
          ~fill="#ECEFF1",
          ~stroke="#607D8B",
          ~strokeWidth="0.75",
          ~outline="none",
          (),
        ),
      ~hover=
        ReactDOMRe.Style.make(
          ~fill="#607D8B",
          ~stroke="#607D8B",
          ~strokeWidth="0.75",
          ~outline="none",
          (),
        ),
      ~pressed=
        ReactDOMRe.Style.make(
          ~fill="#FF5722",
          ~stroke="#607D8B",
          ~strokeWidth="0.75",
          ~outline="none",
          (),
        ),
    );
  let make = _children => {
    ...component,
    render: _self =>
      <div className="title">
        <ComposableMap
          projectionConfig=(
            ComposableMap.projectionConfigT(
              ~scale=205,
              ~rotation=[|(-11), 0, 0|],
            )
          )
          width=980
          height=551
          style=(ReactDOMRe.Style.make(~width="100%", ~height="auto", ()))>
          <ZoomableGroup center=[|0, 20|] disablePanning=false>
            <Geographies geography="world-50m.json">
              ...(
                   (geographies, projection) =>
                     Array.mapi(
                       (i, geography) =>
                         if (Geography.id(geography) !== "ATA") {
                           <Geography
                             key=(string_of_int(i))
                             geography
                             projection
                             style=styleC
                           />;
                         } else {
                           <div key=(string_of_int(i)) />;
                         },
                       geographies,
                     )
                 )
            </Geographies>
            <Markers>
              <Marker
                marker=(
                  Marker.markerT(
                    ~markerOffset=35,
                    ~name="Santiago",
                    ~coordinates=[|(-70.6693), (-33.4489)|],
                  )
                )
                style=(
                  Marker.styleT(
                    ~default=ReactDOMRe.Style.make(~fill="#FF5722", ()),
                    ~hover=ReactDOMRe.Style.make(~fill="#FFFFFF", ()),
                    ~pressed=ReactDOMRe.Style.make(~fill="#FF5722", ()),
                  )
                )>
                <circle
                  cx="0"
                  cy="0"
                  r="6px"
                  style=(
                    ReactDOMRe.Style.make(
                      ~stroke="#FF5722",
                      ~strokeWidth="3px",
                      ~opacity="0.9",
                      (),
                    )
                  )
                />
              </Marker>
            </Markers>
          </ZoomableGroup>
        </ComposableMap>
      </div>,
  };
};

ReactDOMRe.renderToElementWithId(<App />, "main");