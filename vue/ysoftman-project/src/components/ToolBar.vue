<template>
  <v-toolbar color="light-blue lighten-1">
    <v-app-bar-nav-icon @click.stop="linkItem('Main')"></v-app-bar-nav-icon>
    <v-toolbar-title>vue test toolbar</v-toolbar-title>
    <v-spacer></v-spacer>
    <v-toolbar-items class="hidden-sm-and-down">
      <!-- <v-btn :to="'/helloworld'" flat>HelloWorld</v-btn>
      <v-btn :to="'/alert'" flat>Alert</v-btn>
      <v-btn :to="'/bindmessage'" flat>BindMessage</v-btn>
      <v-btn :to="'/mycomponent'" flat>MyComponent</v-btn>
      <v-btn :to="'/datalist'" flat>DataList</v-btn>
      <v-btn :to="'/modifyarray'" flat>ModifyArray</v-btn>
      <v-btn :to="'/draggable'" flat>Draggable</v-btn>
      <v-btn :to="'/vuetifydark'" flat>VuetifyDark</v-btn>
      <v-btn :to="'/notfound'" flat>NotFound</v-btn>-->

      <!-- v-menu 컴포넌트 이용해서 드롭다운 메뉴  -->
      <v-menu :nudge-width="200" left offset-y>
        <template v-slot:activator="{ on }">
          <v-btn text v-on="on">
            drop down menu
            <v-icon dark>arrow_drop_down</v-icon>
          </v-btn>
        </template>
        <v-list>
          <v-list-item v-for="item in examples" :key="item" @click="linkItem(item)">
            <v-list-item-title>{{item}}</v-list-item-title>
          </v-list-item>
        </v-list>
      </v-menu>
    </v-toolbar-items>
  </v-toolbar>
</template>

<script>
export default {
  name: "ToolBar",
  props: {
    msg: String
  },
  data() {
    return {
      examples: [
        "HelloWorld",
        "Alert",
        "BindMessage",
        "MyComponent",
        "DataList",
        "DataTable",
        "ModifyArray",
        "Draggable",
        "VuetifyDark"
      ]
    };
  },
  methods: {
    linkItem(iname) {
      this.$router.push({ name: iname }).catch(err => {});
    }
  }
};
</script>

