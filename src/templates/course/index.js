/** @jsx jsx */
// eslint-disable-next-line
import { useEffect, useState } from 'react'
// eslint-disable-next-line
import { graphql } from 'gatsby'
import { jsx, Container } from 'theme-ui'
import Layout from 'components/layout'
import RelayCourseEditor from '../../components/RelayCourseEditor.bs.js'
// eslint-disable-next-line
const axios = require('axios')
// const ReactMarkdown = require('react-markdown')

const Course = ({ data: { course, site } }) => {
  return (
    <Layout site={site}>
      <Container>
        <RelayCourseEditor course={course} />
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
