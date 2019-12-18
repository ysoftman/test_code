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

      <!-- toolip 으로 mouse over 시 메시지 표시 -->
      <v-tooltip bottom>
        <template v-slot:activator="{ on }">
          <v-btn icon>
            <v-icon v-on="on" @click="toggleDark">mdi-brightness-4</v-icon>
          </v-btn>
        </template>
        <span>dark theme</span>
      </v-tooltip>
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
    },
    toggleDark() {
      if (this.$vuetify.theme.dark === true) {
        this.$vuetify.theme.dark = false;
        // localStorage value 는 스트링으로 저장된다.
        localStorage.setItem("dark_theme", "false");
      } else {
        this.$vuetify.theme.dark = true;
        localStorage.setItem("dark_theme", "true");
      }

      // draggable list-group-item , list-group-json-result 가 dark theme 에서 숫자가 보이지 않아
      // dark theme 일때 background 색상 조정
      // let lgitem = document.querySelector(".list-group-item");
      let lgitem = document.querySelectorAll(".list-group-item");
      for (let i = 0; i < lgitem.length; i++) {
        if (this.$vuetify.theme.dark === true) {
          lgitem[i].style.background = "#d4edda";
          lgitem[i].style.color = "black";
        } else {
          lgitem[i].style.background = "white";
        }
      }
      // let lgjsonresult = document.querySelector(".list-group-json-result");
      let lgjsonresult = document.querySelectorAll(".list-group-json-result");
      for (let i = 0; i < lgjsonresult.length; i++) {
        if (this.$vuetify.theme.dark === true) {
          lgjsonresult[i].style.background = "#d4edda";
          lgjsonresult[i].style.color = "black";
        } else {
          lgjsonresult[i].style.background = "white";
        }
      }
    }
  }
};
</script>

