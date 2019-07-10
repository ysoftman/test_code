<template>
  <div>
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
    <b-btn @click="pushElement(form.val1)" variant="info" class="m-1">추가</b-btn>
    <b-btn @click="popElement" variant="info" class="m-1">삭제</b-btn>
  </div>
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
