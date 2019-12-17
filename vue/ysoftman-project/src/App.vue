<template>
  <!-- v-app 은 항상 포함돼야 한다. -->
  <v-app>
    <v-container fluid ma-0 pa-0>
      <toolbar flat height="80px"></toolbar>
      <v-card>
        <v-img src="./assets/logo.png" aspect-ratio="1" center max-width="300" max-height="300"></v-img>
      </v-card>
      <router-view></router-view>
    </v-container>
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
