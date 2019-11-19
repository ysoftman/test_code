<template>
  <v-data-table :headers="headers" :items="desserts" :items-per-page="-1" class="elevation-2"></v-data-table>
</template>

<script>
export default {
  name: "DataTable",
  data() {
    return {
      headers: [
        { text: "ID", align: "left", value: "id", sortable: true },
        { text: "이름", align: "left", value: "name", sortable: true },
        { text: "과일", align: "left", value: "fruite", sortable: true }
      ],
      desserts: [
        { id: "1", name: "bill", fruite: "lemon" },
        { id: "2", name: "yoon", fruite: "apple" },
        { id: "3", name: "ysoftman", fruite: "orange" },
        { id: "4", name: "aaa", fruite: "banana" },
        { id: "5", name: "bbb", fruite: "grape" }
      ]
    };
  }
};
</script>
