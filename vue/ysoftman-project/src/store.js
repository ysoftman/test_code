import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    arr: [],
  },
  mutations: {
    pushArray(state, payload) {
      state.arr.push(payload.element);
      console.log('pushArray()state.arr:', state.arr);
    },
    popArray(state, payload) {
      state.arr.pop(payload.element);
      console.log('popArray() state.arr:', state.arr);
    },
  },
  actions: {

  }
})
