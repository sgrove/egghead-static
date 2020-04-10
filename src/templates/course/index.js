import { jsx } from 'theme-ui'
import Course from '../../components/course'
import RelayCourseEditor from '../../components/RelayCourseEditor.bs.js'

export default props => {
  return jsx(RelayCourseEditor, { course: props.data.course })
}
