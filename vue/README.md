# Vue.js 테스트

## 초기 환경 설정

```bash
# vue-cli 등 필요 패키 설치
npm install -g @vue/cli vuetify bootstrap-vue bootstrap vuedraggable

# webpack (번들러, 의존성을 가진 모듈들을 묶어 정적인 asset 생성) template 를 이용해 프로젝트 생성
vue create ysoftman-project
cd ysoftman-project
```

## ysoftman-project Build Setup

``` bash
# package.json 에 명시된 패키지 최신으로 업데이트(사용안함)
# npm install npm-check-updates
# ncu -u

# install dependencies
# ysoftman-project 에서 npm_modules 용량이 너무 커서 커밋대상에서 제외하자.
# 패키지 설치
npm install

# serve with hot reload at localhost:8080
npm run serve

# build for production with minification
npm run build

# build for production and view the bundle analyzer report
npm run build --report
```

For a detailed explanation on how things work, check out the [guide](http://vuejs-templates.github.io/webpack/) and [docs for vue-loader](http://vuejs.github.io/vue-loader).

## troubleshooting

- npm run dev 실행 후 ysoftman-project/src 소스 수정 후 저장하면 바로 컴파일되어 오류 또는 결과를 볼 수 있다.

- ESLint 를 설치한 경우 vscode 로 auto formatting 시 vue 문법에 맞지 않게 ; 이나 공백이 사리져 에러 발생 다음 구문을 명시해 비활성화 할 수 있다.

  ```javascript
  <script>
  /* eslint-disable */
  </script>
  ```

- npm run serve 에서 component 관련 콘솔에 다음 경고가 발생하는 경우는 런타임용 파일(vue.runtime.esm.js)을 사용하기 때문이다.

  ```text
  [Vue warn]: You are using the runtime-only build of Vue where the template compiler is not available. Either pre-compile the templates into render functions, or use the compiler-included build.
  ```

  - npm run build 빌드 후 vue.esm.js 파일을 webpack 같은 번들러에서 [alias 설정](https://kr.vuejs.org/v2/guide/installation.html#%EA%B0%81-%EB%8B%A4%EB%A5%B8-%EB%B9%8C%EB%93%9C%EA%B0%84-%EC%B0%A8%EC%9D%B4%EC%A0%90)

## references

- vue : https://kr.vuejs.org/
- webpack : https://webpack.js.org/
- vue-router : https://github.com/vuejs/vue-router/tree/dev/examples
- vue-router history mode : https://router.vuejs.org/guide/essentials/history-mode.html#example-server-configuration
- vue-component : https://bootstrap-vue.js.org/docs/components
- vue examples : https://vuejsexamples.com/
- vuetifyjs : https://vuetifyjs.com
- eslint : https://eslint.org/docs/rules/space-before-function-paren
