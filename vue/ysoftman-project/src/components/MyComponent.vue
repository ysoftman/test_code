<template>
  <div id="aaa">
    {{ name }}
    <ol>
      <!-- app 인스턴스 데이터를 fruitCom 컴포넌트를 사용하여 출력 -->
      <!-- vue 2.2.0 이상에서는 v-bind:key 로 키를 명시해햐 한다. -->
      <!-- <fruitCom v-for="it in fruitList" v-bind:key="it.name" v-bind:item="it"></fruitCom> -->
      <!-- v-bind 축약표현 -->
      <!-- v-on 축약표현 @ -->
      <fruitCom v-for="it in fruitList" :key="it.name" :item="it"></fruitCom>
    </ol>
  </div>
</template>

<script>
// 컴포넌트를 전역으로 등록해서 사용할때
// import Vue from "vue";
// // 전역 컴포넌트를 먼저 선언(등록)
// Vue.component("fruitCom", {
//   // props 으로 선언된 키값으로 component 객체의 데이터를 전달 받는다.
//   props: ["item"],
//   template: "<li> {{ item.index }} {{ item.name }} </li>"
// });

import FruitCom from "@/components/FruitCom.vue";
export default {
  // 컴포넌트 네임은 파스칼(MyComponent)나 케밥(kebab, my-component)로 만들어야 한다. 케밥스타일 지향
  // 숫자가 포함되면 name 으로 컴포넌트를 찾을때 에러 발생
  // https://github.com/vuejs/vue/issues/7344
  name: "MyComponent",
  components: {
    FruitCom
  },
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
Î