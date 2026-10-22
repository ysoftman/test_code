import { defineStore } from "pinia";

export const useArrayStore = defineStore("array", {
  state: () => ({
    arr: [],
  }),
  actions: {
    pushArray(element) {
      this.arr.push(element);
      console.log("pushArray():", this.arr);
    },
    popArray() {
      this.arr.pop();
      console.log("popArray():", this.arr);
    },
  },
});
