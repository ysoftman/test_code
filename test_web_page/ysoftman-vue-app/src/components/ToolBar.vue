<template>
  <v-app-bar color="light-blue" height="80">
    <!-- 네비게이션 아이콘 -->
    <v-app-bar-nav-icon @click="linkItem('Main')" />

    <v-app-bar-title>
      vue test toolbar
    </v-app-bar-title>

    <v-spacer />

    <div class="d-flex align-center hidden-sm-and-down">
      <!-- 🌙 다크모드 토글 -->
      <v-tooltip location="bottom">
        <template #activator="{ props }">
          <v-btn
            icon
            v-bind="props"
            @click="toggleDark"
          >
            <v-icon icon="mdi-brightness-4" />
          </v-btn>
        </template>
        <span>dark theme</span>
      </v-tooltip>

      <!-- 📂 드롭다운 메뉴 -->
      <v-menu location="bottom">
        <template #activator="{ props }">
          <v-btn
            variant="text"
            v-bind="props"
          >
            drop down menu
            <v-icon end icon="mdi-menu-down" />
          </v-btn>
        </template>

        <v-list>
          <v-list-item
            v-for="item in examples"
            :key="item"
            @click="linkItem(item)"
          >
            <v-list-item-title>
              {{ item }}
            </v-list-item-title>
          </v-list-item>
        </v-list>
      </v-menu>
    </div>
  </v-app-bar>
</template>

<script setup>
import { ref } from "vue";
import { useRouter } from "vue-router";
import { useTheme } from "vuetify";

const router = useRouter();
const theme = useTheme();

const examples = ref([
    "HelloWorld",
    "Alert",
    "BindMessage",
    "MyComponent",
    "DataList",
    "DataTable",
    "ModifyArray",
    "Draggable",
    "VuetifyDark",
]);

const linkItem = (name) => {
    router.push({ name }).catch(() => {});
};

const toggleDark = () => {
    const isDark = theme.global.current.value.dark;
    theme.change(isDark ? "light" : "dark");
    localStorage.setItem("dark_theme", (!isDark).toString());
};
</script>
