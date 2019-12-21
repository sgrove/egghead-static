import { wrapRootElement } from './src'
import ReactDOM from 'react-dom'

const loadableReady = require('@loadable/component').loadableReady

const replaceHydrateFunction = () => {
  return (element, container, callback) => {
    loadableReady(() => {
      console.log('He, I got called')
      ReactDOM.render(
        wrapRootElement({ element: element }),
        container,
        callback,
      )
    })
  }
}

export { replaceHydrateFunction }
