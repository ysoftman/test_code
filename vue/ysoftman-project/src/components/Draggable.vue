<template>
  <b-container  class="fluid container">

  <h1>{{msg}}</h1>

  <div class="form-group form-group-lg panel panel-default">
    <div class="panel-body">
      <div class = "checkbox">
        <label><input type = "checkbox" v-model="editable">드레그 활성화</label>
      </div>
      <button type="button" class="btn btn-primary" @click="orderList">원래 순서로 되돌리기</button>
    </div>
  </div>

    <b-row>

      <div class="col-md-3">
          <draggable class="list-group" element="ul" v-model="myList" :options="dragOptions" :move="onMove" @start="isDragging=true" @end="isDragging=false">
            <transition-group type="transition" :name="'flip-list'">
              <li class="list-group-item" v-for="element in myList" :key="element.order">
                <!-- {{element}} -->
                <!-- {{ Element2JsonString(element) }} -->
                {{element.order}}
                {{element.mydata.name}},{{element.mydata.desc}}
              </li>
            </transition-group>
        </draggable>
      </div>

      <div class="list-group col-md-3">
        <h3>json 결과</h3>
        <pre>{{myListString}}</pre>
      </div>

    </b-row>

  </b-container >
</template>

<script>
/* eslint-disable */
// Vue.js는 렌더링 된 DOM을 기본 Vue 인스턴스의 데이터에 선언적으로 바인딩 할 수있는 HTML 기반 템플릿 구문을 사용합니다
import Vue from "vue";

import draggable from "vuedraggable";
import BootstrapVue from "bootstrap-vue";
import "bootstrap/dist/css/bootstrap.css";
import "bootstrap-vue/dist/bootstrap-vue.css";

Vue.use(BootstrapVue);

const myData = [
  { id: 111, name: "사과", desc: "맛있다." },
  { id: 222, name: "레몬", desc: "시다." },
  { id: 333, name: "오렌지", desc: "달콤하다." }
];

export default {
  name: "Draggable",
  components: {
    draggable
  },
  data() {
    return {
      msg: "draggable 순서 바꾸기",
      // myData 를 맵형태로 생성
      myList: myData.map((mydata, index) => {
        return { mydata, order: index + 1, fixed: false };
      }),
      editable: true,
      isDragging: false,
      delayedDragging: false
    };
  },
  methods: {
    orderList() {
      this.myList = this.myList.sort((one, two) => {
        return one.order - two.order;
      });
    },
    onMove({ relatedContext, draggedContext }) {
      const relatedElement = relatedContext.element;
      const draggedElement = draggedContext.element;
      return (
        (!relatedElement || !relatedElement.fixed) && !draggedElement.fixed
      );
    },
    Element2JsonString(ele) {
      return JSON.stringify(ele, null, 2);
    }
  },
  computed: {
    // 드래그 중인 요소는 ghost css 적용
    dragOptions() {
      return {
        animation: 0,
        group: "description",
        disabled: !this.editable,
        ghostClass: "ghost"
      };
    },
    myListString() {
      return JSON.stringify(this.myList, null, 2);
    }
  },
  watch: {
    isDragging(newValue) {
      if (newValue) {
        this.delayedDragging = true;
        return;
      }
      this.$nextTick(() => {
        this.delayedDragging = false;
      });
    }
  }
};
</script>

<style>
#myList {
  color: cornflowerblue;
  outline-style: solid;
  margin: 10px;
  /* width: fit-content; */
  width: 25%;
}

.flip-list-move {
  transition: transform 0.5s;
}
.no-move {
  transition: transform 0s;
}
.ghost {
  opacity: 0.5;
  background: #0066ff;
}
.list-group {
  min-height: 20px;
}
.list-group-item {
  cursor: move;
}
.list-group-item i {
  cursor: pointer;
}
</style>
