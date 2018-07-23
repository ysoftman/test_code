<template>
  <div>
    <customtag1> arr = {{ arr }} <br> </customtag1>

  <b-form-group id=""
                label="insert value"
                label-for="Input1">
    <b-form-input id="Input1"
                  type="text"
                  v-model="form.val1"
                  required
                  placeholder="추가할 값을 입력해주세요.">
    </b-form-input>
  </b-form-group>
    <b-btn @click="pushElement(form.val1)" variant="info" class="m-1">
      추가
    </b-btn>
    <b-btn @click="popElement" variant="info" class="m-1">
      삭제
    </b-btn>
  </div>
</template>

<script>
/* eslint-disable */
// Vue.js는 렌더링 된 DOM을 기본 Vue 인스턴스의 데이터에 선언적으로 바인딩 할 수있는 HTML 기반 템플릿 구문을 사용합니다
import Vue from "vue";
import BootstrapVue from "bootstrap-vue";
import "bootstrap/dist/css/bootstrap.css";
import "bootstrap-vue/dist/bootstrap-vue.css";

Vue.use(BootstrapVue);

export default {
  data() {
    return {
      form: {
        va1: "",
        va2: "",
      },
      arr: []
    };
  },
  methods: {
    pushElement(ele) {
      this.arr.push(ele);
    },
    popElement() {
      this.arr.pop();
    }
  }
};
</script>

<style>
customtag1 {
  color: red;
  font-size: 100%;
}
</style>
