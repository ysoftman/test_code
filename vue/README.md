# Vue.js 뷰 사용

## 설치 및 환경 설정

```bash
# vue-cli 설치
npm install -g vue-cli

# webpack (번들러, 의존성을 가진 모듈들을 묶어 정적인 asset 생성) template 를 이용해 프로젝트 생성
vue init webpack ysoftman-project
cd ysoftman-project

# 참고로 ysoftman-project 에서 npm_modules 용량이 너무 커서 삭제하고 커밋
# 따라서 최초 한번은 node_modules 를 설치해야한다.
# 설정된 패키지 설치
npm install

# bootstrap-vue 설치
npm install bootstrap-vue

# dev 로 실행(node_modules/.bin/webpack-dev-server 로 서비를 띄워준다.)
npm run dev

# src/compondnts/ vue 추가
# 빌드(dist 디렉토리에 번들링되어 배포시 사용)
npm run build
```

## 샘플 실행

- npm run dev 실행 후 ysoftman-project/src 소스 수정 후 저장하면 바로 컴파일되어 오류 또는 결과를 볼 수 있다.

- ESLint 를 설치한 경우 vscode 로 auto formatting 시 vue 문법에 맞지 않게 ; 이나 공백이 사리져 에러 발생 다음 구문을 명시해 비활성화 할 수 있다.

  ```javascript
  <script>
  /* eslint-disable */
  </script>
  ```

## 참고

- vue : https://kr.vuejs.org/
- webpack : https://webpack.js.org/
- vue-router : https://github.com/vuejs/vue-router/tree/dev/examples
- vue-router history mode : https://router.vuejs.org/guide/essentials/history-mode.html#example-server-configuration
- vue-component : https://bootstrap-vue.js.org/docs/components
- vue examples : https://vuejsexamples.com/
- eslint : https://eslint.org/docs/rules/space-before-function-paren
- npm 명령 : ./ysoftman-project/README.md
