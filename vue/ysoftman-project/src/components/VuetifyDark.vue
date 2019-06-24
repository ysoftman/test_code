<template>
  <!-- template 안에는 하나의 root element 만 있어야 한다. -->
  <v-app :dark="enable_dark">
    <div>
      <v-switch :label="`dark/light`" v-model="enable_dark"></v-switch>
      <!-- v-app 을 주석처리하면 v-btn dark 를 적용할 수 있다. -->
      <v-btn color="success" :dark="enable_dark">Success</v-btn>
      <v-btn color="error" :dark="enable_dark">Error</v-btn>
      <v-btn color="warning" :dark="enable_dark">Warning</v-btn>
      <v-btn color="info" :dark="enable_dark">Info</v-btn>
    </div>
  </v-app>
</template>

<script>
/* eslint-disable */
// Vue.js는 렌더링 된 DOM을 기본 Vue 인스턴스의 데이터에 선언적으로 바인딩 할 수있는 HTML 기반 템플릿 구문을 사용합니다
import Vue from "vue";
// import BootstrapVue from "bootstrap-vue";
// import "bootstrap/dist/css/bootstrap.css";
// import "bootstrap-vue/dist/bootstrap-vue.css";
// Vue.use(BootstrapVue);
import Vuetify from "vuetify";
import "vuetify/dist/vuetify.min.css";

Vue.use(Vuetify);

export default {
  name: "VuetifyDark",
  data() {
    return { enable_dark: false };
  }
};
</script>
