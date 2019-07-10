<template>
  <!-- v-app 은 항상 포함돼야 한다. -->
  <v-app>
    <div id="app">
      <toolbar></toolbar>
      <router-view />
      <div id="log_img">
        <img src="./assets/logo.png" />
      </div>
    </div>
  </v-app>
</template>

<script>
import ToolBar from "@/components/ToolBar";
/* eslint-disable */
export default {
  name: "App",
  components: {
    toolbar: ToolBar
  }
};
</script>


<style>
.router-link-active {
  color: white;
  background-color: red;
}

.router-link-exact-active {
  color: white;
  background-color: green;
}

#app {
  margin: 0px 0px 0px 0px;
  height: 0px;
}
</style>
