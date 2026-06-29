<script setup>
import logo from "@/assets/logo.png";
import ToolBar from "@/components/ToolBar.vue";
</script>

<template>
  <!-- Vuetify 3에서도 v-app은 필수 -->
  <v-app>
    <v-card flat>
      <!-- 컴포넌트 이름은 PascalCase 그대로 사용 -->
      <ToolBar height="80" />

      <v-row align="center" justify="center">
        <v-img
          :src="logo"
          aspect-ratio="1"
          max-width="300"
          max-height="300"
          contain
        />
      </v-row>

      <router-view />
    </v-card>
  </v-app>
</template>


<style>
.router-link-active {
  color: white;
  background-color: red;
}

.router-link-exact-active {
  color: white;
  background-color: green;
}
</style>

