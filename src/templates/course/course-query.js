import { graphql } from 'gatsby'
import CoursePage from '.'

export default CoursePage

export const query = graphql`
  query CourseBySlug($slug: String!) {
    site {
      siteMetadata {
        title
      }
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
