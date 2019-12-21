let appId = "f1b8d65a-c97c-43c3-ac72-9a289de3c257";

let authConfig =
  OneGraphAuth.createOptions(
    ~appId,
    ~oneGraphOrigin="https://serve.onegraph.com",
    (),
  );

let auth = OneGraphAuth.create(authConfig);
