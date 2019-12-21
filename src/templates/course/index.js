/** @jsx jsx */
// eslint-disable-next-line
import { useEffect, useState } from 'react'
// eslint-disable-next-line
import { graphql } from 'gatsby'
import { jsx, Container, Flex } from 'theme-ui'
import Layout from 'components/layout'
import Markdown from 'react-markdown'
import LessonEditor from '../../components/LessonEditor.bs.js'
// eslint-disable-next-line
const axios = require('axios')
// const ReactMarkdown = require('react-markdown')

const _data = {
  enhanced: true,
  text:
    "After you create an account in Figma, you'll see this screen called Drafts. We're going to click on \"New file.\" In here, you're going to navigate to the top and select the frame tool.\n\n![image of selecting the Google Pixel 2](https://res.cloudinary.com/dg3gyk0gu/image/upload/v1548103539/transcript-images/egghead-create-a-mobile-tablet-and-desktop-frame-in-figma-mobile.jpg)\n\nOnce you select that, you'll see these predetermined sizes on the right side of your screen -- we have phone sizes, tablet, desktop, watch, paper, etc. We're going to select Google Pixel 2.\n\n![image of selecting the frame tool](https://res.cloudinary.com/dg3gyk0gu/image/upload/v1548103527/transcript-images/egghead-create-a-mobile-tablet-and-desktop-frame-in-figma-newfile.jpg)\n\n\n[00:28] We're going to go back and select the frame tool again and go down to tablet and select iPad Pro 10.5. \n\n![image of selecting the Macbook](https://res.cloudinary.com/dg3gyk0gu/image/upload/v1548103528/transcript-images/egghead-create-a-mobile-tablet-and-desktop-frame-in-figma-macbook.jpg)\n\nThen one more time select the frame tool, go down to desktop, and select MacBook Pro.\n\n![image of selecting the iPad](https://res.cloudinary.com/dg3gyk0gu/image/upload/v1548103525/transcript-images/egghead-create-a-mobile-tablet-and-desktop-frame-in-figma-ipad.jpg)\n\nNow we have three frames. We have our mobile version. We have the tablet version and then the desktop version. This makes the process a lot easier because now we don't have to go out and look up the different sizes for mobile, tablet, or desktop.\n",
}

const Lesson = ({ lesson }) => {
  // eslint-disable-next-line
  // const [transcript, setTranscript] = useState(_data)
  // eslint-disable-next-line
  const transcriptUrl = lesson.enhanced_transcript_url

  // useEffect(() => {
  //   // Update the document title using the browser API
  //   axios
  //     .get(transcriptUrl, {
  //       headers: {
  //         Authorization:
  //           'Bearer 50081877e4d3fde5c6d252c0de3f874c4918aec2ec19e264c0a5effbd5c9ab89',
  //       },
  //     })
  //     .then(({ data }) => {
  //       window.ts = data
  //       setTranscript(data)
  //     })
  // })

  const transcript = _data
  const child = transcript ? (
    <LessonEditor lesson={lesson} transcript={transcript} />
  ) : (
    <span>No transcript yet</span>
  )

  return <div>{child}</div>
}

const Course = ({ data: { course, site } }) => {
  return (
    <Layout site={site}>
      <Container>
        <img
          sx={{ maxWidth: 200, height: 200, mb: 5 }}
          src={course.square_cover_480_url}
          alt={course.title}
        />
        <h1>{course.title}</h1>
        <Flex
          sx={{
            mt: 2,
            alignItems: 'center',
            img: { mr: 2, width: 28, height: 28, borderRadius: '50%' },
          }}
        >
          <img
            src={course.instructor.avatar_32_url}
            alt={course.instructor.full_name}
          />
          <h4>{course.instructor.full_name}</h4>
        </Flex>
        <div sx={{ my: 2 }}>
          <b>{Math.ceil(course.rating_out_of_5)} / 5</b>,{' '}
          <b>{course.rating_count}</b> people rated, published{' '}
          <div>
            <b>{course.published_at}</b>
          </div>
        </div>
        <article>
          <Markdown sx={{ mt: 7, variant: 'text.reset' }}>
            {course.description}
          </Markdown>
        </article>
        <br />
        <h3>Lessons</h3>
        <ol sx={{ ml: 4 }}>
          {course.lessons &&
            [course.lessons[0]].map(lesson => {
              return (
                <li key={lesson.id} sx={{ mt: 2, h4: { fontSize: 2 } }}>
                  <Lesson lesson={lesson} />
                </li>
              )
            })}
        </ol>
      </Container>
    </Layout>
  )
}

export default Course
export const query = graphql`
  query CourseBySlug($slug: String!) {
    site {
      ...site
    }
    course(slug: { eq: $slug }) {
      title
      summary
      description
      square_cover_480_url
      rating_out_of_5
      published_at(fromNow: true)
      rating_count
      instructor {
        full_name
        avatar_32_url
      }
      lessons {
        id
        slug
        title
        transcript_url
        enhanced_transcript_url
        duration
      }
    }
  }
`
