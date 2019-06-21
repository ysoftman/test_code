<template>
  <div id="app">
    <img src="./assets/logo.png">
    <ul>
    <li><router-link to = "/">HelloWorld</router-link></li>
    <li><router-link to = "/Alert">Alert</router-link></li>
    <li><router-link to = "/BindMessage">BindMessage</router-link></li>
    <li><router-link to = "/MyComponent">MyComponent</router-link></li>
    <li><router-link to = "/DataList">DataList</router-link></li>
    <li><router-link to = "/ModifyArray">ModifyArray</router-link></li>
    <li><router-link to = "/Draggable">Draggable</router-link></li>
    <li><router-link to = "/VuetifyDark">VuetifyDark</router-link></li>
    <li><router-link to = "*">NotFound</router-link></li>
    </ul>
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
  height: 200px;
}

</style>
