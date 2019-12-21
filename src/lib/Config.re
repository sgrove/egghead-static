let appId = "b36150b7-ce64-4a6c-a2af-fbe50da58552";

let authConfig =
  OneGraphAuth.createOptions(
    ~appId,
    ~oneGraphOrigin="https://serve.onegraph.io",
    (),
  );

let auth = OneGraphAuth.create(authConfig);
