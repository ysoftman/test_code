<!--html file-->
<template>
<div id="datalist">
  <!-- vue 2.2.0 이상에서는 v-bind:key 로 키를 명시해햐 한다. -->
  <h3 v-for="aaa in aaa_list" :key="aaa.a">
    {{ aaa.a }} {{ aaa.b }}
  </h3>
</div>
</template>

<!--script file-->
<script>
/* eslint-disable */
export default {
  name: "DataList",
  data() {
    return {
      msg: "Welcome to Your Vue.js App",
      aaa_list: [
        { a: 111, b: "첫번째 데이터" },
        { a: 222, b: "두번째 데이터" },
        { a: 333, b: "세번째 데이터" }
      ]
    };
  }
};
</script>
