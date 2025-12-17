<template>
  <v-container fluid>
    <v-switch
      label="dark / light"
      v-model="enableDark"
      @change="toggleTheme"
    />

    <v-btn>Default</v-btn>
    <v-btn color="green">Green</v-btn>
    <v-btn color="red">Red</v-btn>
    <v-btn color="blue">Blue</v-btn>

    <br /><br />

    <v-btn disabled>Disabled</v-btn>

    <br /><br />

    <v-btn color="success">Success</v-btn>
    <v-btn color="error">Error</v-btn>
    <v-btn color="warning">Warning</v-btn>
    <v-btn color="info">Info</v-btn>
  </v-container>
</template>

<script setup>
import { ref, onMounted } from "vue";
import { useTheme } from "vuetify";

const theme = useTheme();
const enableDark = ref(false);

const toggleTheme = () => {
    theme.change(enableDark.value ? "dark" : "light");
    localStorage.setItem("dark_theme", enableDark.value.toString());
};

onMounted(() => {
    const saved = localStorage.getItem("dark_theme");
    if (saved === "true") {
        enableDark.value = true;
        theme.change("dark");
    }
});
</script>

