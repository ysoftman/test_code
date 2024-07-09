# webpack 으로 번들링 테스트

```bash
# 현재 디렉토리를 npm 초기화(package.json 생성된다.)
npm init -y

# webpack, babel-core, babel-loader 등 설치
# package-lock.json(package.json 보다 우선해서 dependency 체크) node_modules 생성된다.
# --save 는 dependency object 를 --save-dev 는 devdendency object 를 package.json 를 추가한다.
npm install webpack babel-core babel-loader babel-preset-es2015 extract-text-webpack-plugin --save-dev

# 정적 리소스 디렉토리 생성
mkdir -p src

# 테스트를 위한 정적 리소스 생성
# webpack 이 번들링(패키징)한 bundle.js 파일을 사용하도록 한다.
echo '
<html>
    <head>
        <title>ysoftamn</title>
    </head>
    <body>
        <div class="container">
            <p id="my_text" class="text"></p>
        </div>
        <script src="dist/bundle.js"></script>
    </body>
</html>
' >! index.html

# 실제 js 소스
echo 'document.getElementById("my_text").innerHTML = "Hello World<br /><p>ysoftman</p>";' >! src/app.js

# .js 들을 번들링하여 dist/bundle.js 을 생성하게 한다.
echo "const webpack = require('webpack')
const path = require('path')
const extractCommons = new webpack.optimize.CommonsChunkPlugin({
  name: 'commons',
  filename: 'common.js'
})
const ExtractTextPlugin = require('extract-text-webpack-plugin')
const extractCSS = new ExtractTextPlugin('[name].bundle.css')
const config = {
  context: path.resolve(__dirname, 'src'),
  entry: './app.js',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js'
  },
  module: {
    rules: [{
      test: /\.js$/,
      include: path.resolve(__dirname, 'src'),
      use: [{
        loader: 'babel-loader',
        options: {
          presets: [
            ['es2015', {modules: false}]
          ]
        }
      }]
    }]
  }
}
module.exports = config" >! webpack.config.js

# package.json scripts 에 다음 추가
  "start": "webpack --watch",
  "build": "webpack -p"

# npm 으로 webpack --watch 실행
# js 가 변경되면 bundle.js 파일이 새로 만들어 진다.
npm start


# index.html 파일을 열어보면 bundle.js 를 사용하여 작동하고 있다.
```
