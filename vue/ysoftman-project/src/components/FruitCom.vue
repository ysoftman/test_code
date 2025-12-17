<template>
  <li>{{ item.index }} {{ item.name }}</li>
</template>

<script setup>
defineProps({
    item: Object,
});
</script>

