<template>
  <!-- template 안에는 하나의 root element 만 있어야 한다. -->
  <v-container fluid>
    <v-switch :label="`dark/light`" v-model="enable_dark"></v-switch>
    <v-btn :dark="enable_dark">Success</v-btn>
    <v-btn color="green" :dark="enable_dark">Error</v-btn>
    <v-btn color="red" :dark="enable_dark">Warning</v-btn>
    <v-btn color="blue" :dark="enable_dark">Info</v-btn>
    <br />
    <!-- disabled 버튼은 dark 모드가 되면 안보인다. -->
    <v-btn :dark="enable_dark" disabled>Success</v-btn>
    <br />
    <!-- 아래 컬럭들은 dark 모드를 적용해도 변경되지 않는다. -->
    <v-btn color="success" :dark="enable_dark">Success</v-btn>
    <v-btn color="error" :dark="enable_dark">Error</v-btn>
    <v-btn color="warning" :dark="enable_dark">Warning</v-btn>
    <v-btn color="info" :dark="enable_dark">Info</v-btn>
  </v-container>
</template>

<script>
export default {
  name: "VuetifyDark",
  data() {
    return { enable_dark: true };
  }
};
</script>
