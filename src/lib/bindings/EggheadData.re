type transcript = {
  enhanced: bool,
  text: string,
};

type lesson = {
  title: string,
  duration: int,
  enhanced_transcript_url: string,
  id: int,
  slug: string,
  transcript_url: string,
};

type instructor = {
  avatar_32_url: string,
  full_name: string,
};

type course = {
  description: string,
  instructor,
  lessons: array(lesson),
  published_at: string,
  rating_count: int,
  rating_out_of_5: float,
  square_cover_480_url: string,
  summary: string,
  title: string,
};

type courseWithNullableLessons = {
  description: string,
  instructor,
  lessons: Js.Nullable.t(array(lesson)),
  published_at: string,
  rating_count: int,
  rating_out_of_5: float,
  square_cover_480_url: string,
  summary: string,
  title: string,
};

let courseSlug = (course: course) =>
  course.title
  ->Js.String2.replaceByRe([%bs.re "/\W+/g"], "-")
  ->Js.String2.toLocaleLowerCase;
