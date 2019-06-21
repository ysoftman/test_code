<template>
  <div id="aaa">
    {{ name }}
    <ol>
      <!-- app 인스턴스 데이터를 fruitCom 컴포넌트를 사용하여 출력 -->
      <!-- vue 2.2.0 이상에서는 v-bind:key 로 키를 명시해햐 한다. -->
      <fruitCom v-for="it in fruitList" v-bind:key="it.name" v-bind:item="it"></fruitCom>
    </ol>
  </div>
</template>

<script>
/* eslint-disable */
import Vue from "vue";
import BootstrapVue from "bootstrap-vue";
import "bootstrap/dist/css/bootstrap.css";
import "bootstrap-vue/dist/bootstrap-vue.css";

Vue.use(BootstrapVue);

// 전역 컴포넌트를 먼저 선언(등록)
Vue.component("fruitCom", {
  // props 으로 선언된 키값으로 component 객체의 데이터를 전달 받는다.
  props: ["item"],
  template: "<li> {{ item.index }} {{ item.name }} </li>"
});

export default {
  name: "MyComponent",
  data() {
    return {
      fruitList: [
        { index: 1, name: "apple" },
        { index: 2, name: "banana" },
        { index: 3, name: "lemon" }
      ],
      name: "fruitList"
    };
  }
};
</script>
