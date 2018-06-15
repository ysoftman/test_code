<template>
<div id="datalist">
  <!-- 반복문과 조건문 테스트 -->
  <!-- vue 2.2.0 이상에서는 v-bind:key 로 키를 명시해햐 한다. -->
  <h3 v-for="aaa in aaa_list" :key="aaa.a">
    <customtag1 v-if="aaa.a == 111">
      첫번째 조건 {{ aaa.a }} {{ aaa.b }} <br>
    </customtag1>
    <customtag2 v-if="aaa.a == 222">
      두번째 조건 {{ aaa.a }} {{ aaa.b }} <br>
    </customtag2>
    <customtag3 v-if="aaa.a == 333">
      세번째 조건 {{ aaa.a }} {{ aaa.b }} <br>
    </customtag3>
  </h3>
</div>
</template>

<script>
/* eslint-disable */
export default {
  name: "DataList",
  data() {
    return {
      msg: "Welcome to Your Vue.js App",
      aaa_list: [
        { a: 111, b: "aaa" },
        { a: 222, b: "bbb" },
        { a: 333, b: "ddd" }
      ]
    };
  }
};
</script>

<style>
customtag1 {
    color: red;
    font-family: verdana;
    font-size: 100%;
}
customtag2 {
    color: green;
    font-family: verdana;
    font-size: 200%;
}
customtag3 {
    color: blue;
    font-family: verdana;
    font-size: 300%;
}
</style>
