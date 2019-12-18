<template>
  <v-container fluid>
    <h1>{{msg}}</h1>
    <v-row>
      <v-col xs4 class="elevation-0 pa-3 ma-2">
        <v-btn class="blue darken-1" @click="orderList1">정렬하기</v-btn>
        <draggable
          v-model="myList1"
          group="ysoftman-group"
          ghostClass="ghost"
          :move="onMove"
          @start="isDragging=true"
          @end="isDragging=false"
        >
          <div class="list-group-item" v-for="element in myList1" :key="element.order">
            <!-- {{element}} -->
            <!-- {{ Element2JsonString(element) }} -->
            {{element.order}}
            {{element.mydata.name}},{{element.mydata.desc}}
          </div>
        </draggable>
        <h3>json 결과</h3>
        <pre class="list-group-json-result">{{myListString1}}</pre>
      </v-col>

      <v-col xs4 class="elevation-0 pa-3 ma-2">
        <v-btn class="blue" @click="orderList2">정렬하기</v-btn>
        <draggable
          v-model="myList2"
          group="ysoftman-group"
          ghostClass="ghost"
          :move="onMove"
          @start="isDragging=true"
          @end="isDragging=false"
        >
          <div class="list-group-item" v-for="element in myList2" :key="element.order">
            <!-- {{element}} -->
            <!-- {{ Element2JsonString(element) }} -->
            {{element.order}}
            {{element.mydata.name}},{{element.mydata.desc}}
          </div>
        </draggable>
        <h3>json 결과</h3>
        <pre class="list-group-json-result">{{myListString2}}</pre>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
/* eslint-disable */
// Vue.js는 렌더링 된 DOM을 기본 Vue 인스턴스의 데이터에 선언적으로 바인딩 할 수있는 HTML 기반 템플릿 구문을 사용합니다
import draggable from "vuedraggable";

const myData1 = [
  { id: 111, name: "사과", desc: "맛있다." },
  { id: 222, name: "레몬", desc: "시다." },
  { id: 333, name: "오렌지", desc: "달콤하다." }
];

const myData2 = [
  { id: 444, name: "바나나", desc: "무르다." },
  { id: 555, name: "딸기", desc: "상큼하다." }
];

export default {
  name: "Draggable",
  components: {
    draggable
  },
  data() {
    return {
      msg: "[draggable] 리스트내 순서, 리스트간 이동",
      // myData 를 맵형태로 생성
      myList1: myData1.map((mydata, index) => {
        return { mydata, order: mydata.id, fixed: false };
      }),

      myList2: myData2.map((mydata, index) => {
        return { mydata, order: mydata.id, fixed: false };
      }),

      isDragging: false,
      delayedDragging: false
    };
  },
  methods: {
    orderList1() {
      this.myList1 = this.myList1.sort((one, two) => {
        return one.order - two.order;
      });
    },
    orderList2() {
      this.myList2 = this.myList2.sort((one, two) => {
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
    myListString1() {
      return JSON.stringify(this.myList1, null, 2);
    },
    myListString2() {
      return JSON.stringify(this.myList2, null, 2);
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
  },
  mounted() {
    // draggable list-group-item , list-group-json-result 가 dark theme 에서 숫자가 보이지 않아
    // dark theme 일때 background 색상 조정
    // let lgitem = document.querySelector(".list-group-item");
    let lgitem = document.querySelectorAll(".list-group-item");
    for (let i = 0; i < lgitem.length; i++) {
      if (this.$vuetify.theme.dark === true) {
        lgitem[i].style.background = "#d4edda";
        lgitem[i].style.color = "black";
      } else {
        lgitem[i].style.background = "white";
      }
    }
    // let lgjsonresult = document.querySelector(".list-group-json-result");
    let lgjsonresult = document.querySelectorAll(".list-group-json-result");
    for (let i = 0; i < lgjsonresult.length; i++) {
      if (this.$vuetify.theme.dark === true) {
        lgjsonresult[i].style.background = "#d4edda";
        lgjsonresult[i].style.color = "black";
      } else {
        lgjsonresult[i].style.background = "white";
      }
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
</style>
