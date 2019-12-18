<template>
  <v-container fluid>
    <div id="customtag1">
      arr = {{ arr }}
      <br />
    </div>

    <b-form-group id label="insert value" label-for="Input1">
      <b-form-input
        id="Input1"
        type="text"
        v-model="form.val1"
        required
        placeholder="추가할 값을 입력해주세요."
      ></b-form-input>
    </b-form-group>

    <b-btn @click="pushElement(form.val1)" variant="info">추가</b-btn>
    <!-- m-1 모든 지만 1 설정, ml-10 왼쪽 마진 10으로 설정 -->
    <b-btn @click="popElement" variant="info" class="ml-10">삭제</b-btn>
  </v-container>
</template>

<script>
export default {
  data() {
    return {
      form: {
        va1: "",
        va2: ""
      },
      arr: []
    };
  },
  methods: {
    pushElement(ele) {
      this.arr.push(ele);
    },
    popElement() {
      this.arr.pop();
    }
  }
};
</script>

<style>
#customtag1 {
  color: red;
  font-size: 100%;
}
</style>
