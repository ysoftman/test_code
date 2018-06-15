<template>
<div id="component">
  {{ name }}
  <ol>
    <!--app 인스턴의 데이터를 action-item 컴포넌트를 사용하여 출력-->
    <!-- vue 2.2.0 이상에서는 v-bind:key 로 키를 명시해햐 한다. -->
    <action-item v-for="item in fruiteList" v-bind:param="item" :key=item.message></action-item>
  </ol>
</div>
</template>

<script>
/* eslint-disable */
import Vue from "vue";

// 전역 컴포넌트를 먼저 선언(등록)
Vue.component("action-item", {
  // props 으로 선언된 키를 통해 component 객체의 데이터를 전달 받는다.
  props: ["param"],
  template: "<li>{{ param.message }}</li>"
});

export default {
  name: "Component",
  data() {
    return {
      fruiteList: [
        { message: "apple" },
        {
          message: "banana"
        },
        {
          message: "lemon"
        }
      ],
      name: "fruiteList"
    };
  }
};
</script>
