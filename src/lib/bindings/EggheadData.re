type transcript = {
  enhanced: bool,
  text: string,
};

type lesson = {
  id: int,
  duration: int,
  enhanced_transcript_url: string,
  slug: string,
  title: string,
  transcript_url: string,
};

type editableLesson = {
  id: int,
  slug: string,
  transcript: string,
  editedTranscript: string,
  existingSha: string,
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

/* Fix this name, it's terrible! */
type editPayload = {
  transcript: string,
  sha: string,
  edited: string,
};

let courseSlug = (course: course) =>
  course.title
  ->Js.String2.replaceByRe([%bs.re "/\\W+/g"], "-")
  ->Js.String2.toLocaleLowerCase;

type repo = {
  owner: string,
  name: string,
};

type lessonsMap = Belt.Map.Int.t(lesson);
let emptyLessonsMap = Belt.Map.Int.empty;

type editableLessonsMap = Belt.Map.Int.t(editableLesson);
let emptyEditableLessonsMap = Belt.Map.Int.empty;

let filepathOfEditableLesson = (course: course, lesson: editableLesson) => {
  let lessonSlug = lesson.slug;
  let courseSlug = courseSlug(course);
  let filePath = {j|$courseSlug/lessons/$lessonSlug.md|j};
  filePath;
};
