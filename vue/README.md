# Vue.js 테스트

## 초기 환경 설정

```bash
# vue-cli(vue 자동 설치)등 필요 패키 설치(vue-cli 유지보수로 업데이트가 되지 않는다.)
# npm install -g @vue/cli vuetify eslint eslint-plugin-vue

# webpack (번들러, 의존성을 가진 모듈들을 묶어 정적인 asset 생성) template 를 이용해 프로젝트 생성
# vue create ysoftman-project
# cd ysoftman-project

# vue-cli 대신 create-vue(vue+vite)을 사용한다.
bun create vue@latest ysoftman-project

# .eslintrc 설정 파일 생성
bun install -g eslint
eslinit --init
```

## ysoftman-project Build Setup

```bash
# package.json 에 명시된 패키지 최신으로 업데이트(사용안함)
# npm install npm-check-updates
# ncu -u
# package.json
bun add bootstrap fsevents minimist loader-utils thenify shell-quote elliptic node-fetch @babel/traverse eventsource json-schema handlebars archive body-parser vuedraggable

# install dependencies
# ysoftman-project 에서 npm_modules 용량이 너무 커서 커밋대상에서 제외하자.
# 패키지 설치
#npm install
bun install

# serve with hot reload at localhost:8080
# 'ERR_OSSL_EVP_UNSUPPORTED' 발생시
export NODE_OPTIONS=--openssl-legacy-provider
bun run dev

# build for production with minification
# npm run build
bun run build

# build for production and view the bundle analyzer report
# npm run build --report
bun run build --report
```

For a detailed explanation on how things work, check out the [guide](http://vuejs-templates.github.io/webpack/) and [docs for vue-loader](http://vuejs.github.io/vue-loader).

## troubleshooting

- npm run dev 실행 후 ysoftman-project/src 소스 수정 후 저장하면 바로 컴파일되어 오류 또는 결과를 볼 수 있다.
- ESLint 를 설치한 경우 vscode 로 auto formatting 시 vue 문법에 맞지 않게 ; 이나 공백이 사리져 에러 발생 다음 구문을 명시해 비활성화 할 수 있다.

  ```javascript
  <script>/* eslint-disable */</script>
  ```

- npm run serve 에서 component 관련 콘솔에 다음 경고가 발생하는 경우는 런타임용 파일(vue.runtime.esm.js)을 사용하기 때문이다.

  ```text
  [Vue warn]: You are using the runtime-only build of Vue where the template compiler is not available. Either pre-compile the templates into render functions, or use the compiler-included build.
  ```

  - npm run build 빌드 후 vue.esm.js 파일을 webpack 같은 번들러에서 [alias 설정](https://kr.vuejs.org/v2/guide/installation.html#Runtime-Compiler-vs-Runtime-only)
  - vue-cli3의 프로젝트를 생성한 경우 webpack 설정 파일이 없어 프로젝트 루트 에서 다음처럼 만들어 준다.

  ```bash
  cat > vue.config.js << 'zzz'
  module.exports = {
    configureWebpack: {
      resolve: {
        alias: {
          'vue$': 'vue/dist/vue.esm.js'
        }
      }
    }
  }
  zzz
  ```

## 업데이트 사항

```bash

# 2019-11-20
# vuetify 버전 2 업그레이드
vue upgrade vuetify
# 기타 업그레이드
vue upgrade

# 2025-03-06
# lockfile 버전으로 업그레이드
npm i --lockfile-version 3 --frozen-lockfile
# npm -> 속도 빠른 bun 을 사용하자
bun install
bun update
# vue/cli 5.08 으로 업데이트
bun update -g @vue/cli

# 2025-12-17
# vue-cli/webpack 관련 패키지 제거, 대신 vite 사용
cd ysoftman-project
bun remove vue-cli-plugin-vuetify vuetify-loader \
  @vue/cli-service \
  @vue/cli-plugin-babel \
  @vue/cli-plugin-e2e-cypress \
  @vue/cli-plugin-pwa \
  @vue/cli-plugin-unit-jest \
  core-js \
  register-service-worker \
  loader-utils \
  @babel/traverse \
  babel-core \
  babel-jest \
  @vue/test-utils \
  bootstrap-vue
rm -f babel.config.js jest.config.js cypress.json postcss.config.js
bun remove vuedraggable
bun install vuedraggable@next
bun install -D vite @vitejs/plugin-vue
bun install vuetify
# Vue 2 코드 → 전부 제거, Vue 3 으로 대체
# Vue CLI → 전부 제거
# Vite + Vue 3 + Vuetify 3 조합
# vuex → pinia(앞으로 vue 에선 pinia 가 표준) 대체
```
