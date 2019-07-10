<template>
  <li>{{ item.index }} {{ item.name }}</li>
</template>

<script>
export default {
  name: "FruitCom",
  props: ["item"],
  data() {
    return {};
  }
};
</script>
