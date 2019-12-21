let isSsr: bool = [%bs.raw {|typeof window === "undefined"|}];

let appId = "f1b8d65a-c97c-43c3-ac72-9a289de3c257";

let oneGraphUrl = {j|https://serve.onegraph.com/graphql?app_id=$appId|j};

let authConfig =
  OneGraphAuth.createOptions(
    ~appId,
    ~oneGraphOrigin="https://serve.onegraph.com",
    (),
  );

let auth = isSsr ? None : Some(OneGraphAuth.create(authConfig));
