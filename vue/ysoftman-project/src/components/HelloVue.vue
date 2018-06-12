<!--html file-->
<template>
<div id="hellovue">
  <p>{{ message }}</p>
</div>
</template>

<!--script file-->
<script>
/* eslint-disable */
// Vue.js는 렌더링 된 DOM을 기본 Vue 인스턴스의 데이터에 선언적으로 바인딩 할 수있는 HTML 기반 템플릿 구문을 사용합니다
export default {
  name: "HelloVue",
  data() {
    return {
      message: "hello Vue.js!, i'm ysoftman!"
    };
  }
};
</script>
