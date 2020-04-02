[@react.component]
let make = (~course: CourseEditor.Egghead.courseWithNullableLessons) => {
  <ReasonRelay.Context.Provider environment=RelayEnv.environment>
    <CourseEditor course />
  </ReasonRelay.Context.Provider>;
};

let default = make;
