import React from 'react'
import { ThemeProvider, Styled } from 'theme-ui'
import './lib/reset.css'

export const wrapRootElement = ({ element }) => (
  <Styled.root>{element}</Styled.root>
)
