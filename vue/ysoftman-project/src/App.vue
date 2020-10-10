<template>
  <!-- v-app 은 항상 포함돼야 한다. -->
  <v-app>
    <v-card tile class="elevation-0">
      <toolbar flat height="80px"></toolbar>
      <v-row align="center" justify="center">
        <v-img src="./assets/logo.png" aspect-ratio="1" max-width="300" max-height="300"></v-img>
      </v-row>
      <router-view></router-view>
    </v-card>
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
