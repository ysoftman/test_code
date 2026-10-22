<template>
  <v-container fluid>
    <div id="customtag1">
      arr = {{ arrayStore.arr }}
      <br />
    </div>

    <v-text-field
      v-model="form.val1"
      label="Insert value"
      placeholder="추가할 값을 입력해주세요."
    ></v-text-field>

    <v-btn @click="pushElement(form.val1)" color="info">추가</v-btn>
    <v-btn @click="popElement" color="info" class="ml-4">삭제</v-btn>
  </v-container>
</template>

<script setup>
import { reactive } from "vue";
import { useArrayStore } from "@/store";

// Pinia store 가져오기
const arrayStore = useArrayStore();

// 폼 데이터
const form = reactive({
    val1: "",
});

// 배열에 추가
const pushElement = (ele) => {
    if (ele) {
        arrayStore.pushArray(ele);
        form.val1 = ""; // 입력 초기화
    }
};

// 배열에서 제거
const popElement = () => {
    arrayStore.popArray();
};
</script>

<style scoped>
#customtag1 {
  color: red;
  font-size: 100%;
}
.ml-4 {
  margin-left: 16px;
}
</style>

