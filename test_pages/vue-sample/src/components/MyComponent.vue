<template>
  <v-container fluid>
    {{ name }}
    <ol>
      <!-- FruitCom 컴포넌트를 v-for로 반복 -->
      <FruitCom v-for="it in fruitList" :key="it.name" :item="it" />
    </ol>
  </v-container>
</template>

<script setup>
import { ref } from "vue";
import FruitCom from "@/components/FruitCom.vue";

const name = ref("fruitList");
const fruitList = ref([
    { index: 1, name: "apple" },
    { index: 2, name: "banana" },
    { index: 3, name: "lemon" },
]);
</script>

