<template>
  <div id="app">
    <img src="./assets/logo.png">
    <router-link to = "/">HelloWorld</router-link>
    <router-link to = "/Alert">Alert</router-link>
    <router-link to = "/BindMessage">BindMessage</router-link>
    <router-link to = "/Component">Component</router-link>
    <router-link to = "/DataList">DataList</router-link>
    <router-link to = "/ModifyArray">ModifyArray</router-link>
    <router-link to = "/Draggable">Draggable</router-link>
    <router-link to = "*">NotFound</router-link>
    <router-view/>
  </div>
</template>

<script>
/* eslint-disable */
export default {
  name: 'App'
}
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
  margin: 10px 10px 10px 10px;
}

</style>
