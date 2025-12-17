<template>
  <v-container fluid>
    <v-data-table
      :headers="headers"
      :items="desserts"
      :items-per-page="-1"
      class="elevation-2"
    >
      <template v-slot:item="{ item }">
        <tr>
          <td class="text-xs-right">{{ item.id }}</td>
          <td class="text-xs-right">{{ item.name }}</td>
          <td class="text-xs-right">{{ item.fruit }}</td>
        </tr>
      </template>
    </v-data-table>
  </v-container>
</template>

<script setup>
import { ref, onMounted } from "vue";
import { useArrayStore } from "@/store";

// Pinia store
const arrayStore = useArrayStore();

// 데이터
const desserts = ref([
    { id: "1", name: "bill", fruit: "lemon" },
    { id: "2", name: "yoon", fruit: "apple" },
]);

const headers = ref([
    {
        text: "ID",
        align: "left",
        value: "id",
        sortable: true,
        class: "subheading font-weight-bold red lighten-1 white--text",
    },
    {
        text: "이름",
        align: "left",
        value: "name",
        sortable: true,
        class: "subheading font-weight-bold green lighten-1 white--text",
    },
    {
        text: "과일",
        align: "left",
        value: "fruit",
        sortable: true,
        class: "subheading font-weight-bold blue lighten-1 white--text",
    },
]);

// 아이템 추가 함수
const createItems = () => {
    desserts.value.push({ id: "3", name: "ysoftman", fruit: "orange" });
    desserts.value.push({ id: "4", name: "aaa", fruit: "banana" });
    desserts.value.push({ id: "5", name: "bbb", fruit: "grape" });

    let addid = 6;
    arrayStore.arr.forEach((element, index) => {
        desserts.value.push({
            id: addid + index,
            name: element,
            fruit: "ModifyArray 컴포넌트",
        });
    });
};

// 컴포넌트 마운트 시 실행
onMounted(() => {
    createItems();
});
</script>

<style scoped>
.text-xs-right {
  text-align: right;
}
</style>

