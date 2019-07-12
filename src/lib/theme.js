export default {
  useCustomProperties: true,
  breakpoints: ['540px', '768px', '992px', '1200px', '1920px'],
  space: [0, 4, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 128, 256, 512],
  fontSizes: [12, 14, 16, 18, 20, 22, 24, 32, 40, 48, 64],
  fonts: {
    body: "'Helvetica Neue','Segoe UI','Helvetica','Arial',sans-serif",
    monospace: 'Menlo, monospace',
  },
  fontWeights: {
    body: 400,
    heading: 700,
  },
  lineHeights: {
    body: 1.5,
    heading: 1.125,
  },
  colors: {
    text: '#131415',
    background: '#fff',
    primary: '#5348ff',
  },
  headings: {
    reset: {
      fontWeight: 'heading',
    },
  },
  styles: {
    root: {
      fontFamily: 'body',
      fontWeight: 'body',
      lineHeight: 'body',
      '*': {
        fontSize: 3,
      },
      'h1, h2, h3, h4, h5': {
        variant: 'headings.reset',
      },
      h1: {
        fontSize: 9,
      },
      h2: {
        fontSize: 8,
      },
      h3: {
        fontSize: 7,
      },
      h4: {
        fontSize: 6,
      },
      h5: {
        fontSize: 4,
      },
    },
  },
}