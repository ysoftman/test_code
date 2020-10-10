<template>
  <!-- 레이아웃 구조 v-container > v-layout > v-flex 순이다. -->
  <v-container fluid>
    <b-alert show>Default Alert</b-alert>
    <b-alert variant="success" show>Success Alert</b-alert>
    <b-alert
      variant="danger"
      dismissible
      :show="showDismissibleAlert"
      @dismissed="showDismissibleAlert=false"
    >Dismissible Alert!</b-alert>

    <b-alert
      :show="dismissCountDown"
      dismissible
      variant="warning"
      @dismissed="dismissCountDown=0"
      @dismiss-count-down="countDownChanged"
    >
      <p>This alert will dismiss after {{dismissCountDown}} seconds...</p>
      <b-progress variant="warning" :max="dismissSecs" :value="dismissCountDown" height="4px"></b-progress>
    </b-alert>

    <b-btn @click="showAlert" variant="info">Show alert with count-down timer</b-btn>
    <!-- m-1 모든 지만 1 설정, ml-10 왼쪽 마진 10으로 설정 -->
    <b-btn
      @click="showDismissibleAlert=true"
      variant="info"
      class="ml-10"
    >Show dismissible alert ({{showDismissibleAlert?'visible':'hidden'}})</b-btn>
  </v-container>
</template>

<script>
import Vue from "vue";
// bootstrap-vue 사용을 위해 패키지와 css 임포트
import BootstrapVue from "bootstrap-vue";
import "bootstrap/dist/css/bootstrap.css";
import "bootstrap-vue/dist/bootstrap-vue.css";

Vue.use(BootstrapVue);

export default {
  data() {
    return {
      dismissSecs: 10,
      dismissCountDown: 0,
      showDismissibleAlert: false
    };
  },
  methods: {
    countDownChanged(dismissCountDown) {
      this.dismissCountDown = dismissCountDown;
    },
    showAlert() {
      this.dismissCountDown = this.dismissSecs;
    }
  }
};
</script>
