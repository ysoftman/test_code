<template>

<draggable v-model="myArray" :options="{group:'people'}" @start="drag=true" @end="drag=false">
  {{msg}}
  <div id=mylist v-for="element in mylist" :key="element.id">
    {{element.id}} - {{element.name}}
  </div>
</draggable>

</template>

<script>
/* eslint-disable */
// Vue.js는 렌더링 된 DOM을 기본 Vue 인스턴스의 데이터에 선언적으로 바인딩 할 수있는 HTML 기반 템플릿 구문을 사용합니다
import Vue from "vue";

import draggable from "vuedraggable";

export default {
  name: "Draggable",
  components: {
    draggable
  },
  data() {
    return {
      msg: "draggable 리스트로 순서 바꾸기",
      mylist: [
        { id: 111, name: "사과" },
        { id: 222, name: "레몬" },
        { id: 333, name: "오렌지" }
      ]
    };
  },
  computed: {
    myList: {
      get() {
        return this.$store.state.myList;
      },
      set(value) {
        this.$store.commit("updateList", value);
      }
    }
  }
};
</script>

<style>
#mylist {
  color: cornflowerblue;
  outline-style: solid;
  margin: 10px;
  /* width: fit-content; */
  width: 25%;
}
</style>
