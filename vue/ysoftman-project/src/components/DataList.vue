<template>
  <v-container fluid>
    <!-- 반복문과 조건문 테스트 -->
    <h3 v-for="aaa in aaa_list" :key="aaa.a">
      <div id="customtag1" v-if="aaa.a === 111">
        첫번째 조건 {{ aaa.a }} {{ aaa.b }}
        <br />
      </div>
      <div id="customtag2" v-if="aaa.a === 222">
        두번째 조건 {{ aaa.a }} {{ aaa.b }}
        <br />
      </div>
      <div id="customtag3" v-if="aaa.a === 333">
        세번째 조건 {{ aaa.a }} {{ aaa.b }}
      </div>
    </h3>
  </v-container>
</template>

<script setup>
import { ref } from "vue";

const msg = ref("Welcome to Your Vue.js App");
const aaa_list = ref([
    { a: 111, b: "aaa" },
    { a: 222, b: "bbb" },
    { a: 333, b: "ddd" },
]);
</script>

<style scoped>
#customtag1 {
  color: red;
  font-family: verdana;
  font-size: 100%;
}
#customtag2 {
  color: green;
  font-family: verdana;
  font-size: 200%;
}
#customtag3 {
  color: blue;
  font-family: verdana;
  font-size: 300%;
}
</style>

