<template>
  <v-container fluid>
    <h1>{{ msg }}</h1>
    <v-row>
      <v-col cols="4" class="elevation-0 pa-3 ma-2">
        <v-btn class="blue darken-1" @click="orderList1">정렬하기</v-btn>
        <draggable
          v-model="myList1"
          group="ysoftman-group"
          ghostClass="ghost"
          :move="onMove"
          @start="isDragging = true"
          @end="isDragging = false"
          item-key="order"
        >
          <template #item="{ element }">
            <div class="list-group-item" :style="itemStyle">
              {{ element.order }}
              {{ element.mydata.name }},{{ element.mydata.desc }}
            </div>
          </template>
        </draggable>
        <h3>json 결과</h3>
        <pre class="list-group-json-result" :style="jsonResultStyle">{{ myListString1 }}</pre>
      </v-col>

      <v-col cols="4" class="elevation-0 pa-3 ma-2">
        <v-btn class="blue" @click="orderList2">정렬하기</v-btn>
        <draggable
          v-model="myList2"
          group="ysoftman-group"
          ghostClass="ghost"
          :move="onMove"
          @start="isDragging = true"
          @end="isDragging = false"
          item-key="order"
        >
          <template #item="{ element }">
            <div class="list-group-item" :style="itemStyle">
              {{ element.order }}
              {{ element.mydata.name }},{{ element.mydata.desc }}
            </div>
          </template>
        </draggable>
        <h3>json 결과</h3>
        <pre class="list-group-json-result" :style="jsonResultStyle">{{ myListString2 }}</pre>
      </v-col>
    </v-row>
  </v-container>
</template>

<script setup>
import { ref, computed, watch, onMounted, onUnmounted } from "vue";
import draggable from "vuedraggable";
import { useTheme } from "vuetify";
import { eventBus } from "../main";

const myData1 = [
  { id: 111, name: "사과", desc: "맛있다." },
  { id: 222, name: "레몬", desc: "시다." },
  { id: 333, name: "오렌지", desc: "달콤하다." },
];

const myData2 = [
  { id: 444, name: "바나나", desc: "무르다." },
  { id: 555, name: "딸기", desc: "상큼하다." },
];

const msg = ref("[draggable] 리스트내 순서, 리스트간 이동");

const myList1 = ref(
  myData1.map((mydata) => ({ mydata, order: mydata.id, fixed: false }))
);
const myList2 = ref(
  myData2.map((mydata) => ({ mydata, order: mydata.id, fixed: false }))
);

const isDragging = ref(false);

const orderList1 = () => {
  myList1.value = myList1.value.sort((one, two) => one.order - two.order);
};

const orderList2 = () => {
  myList2.value = myList2.value.sort((one, two) => one.order - two.order);
};

const onMove = ({ relatedContext, draggedContext }) => {
  const relatedElement = relatedContext.element;
  const draggedElement = draggedContext.element;
  return (!relatedElement || !relatedElement.fixed) && !draggedElement.fixed;
};

const myListString1 = computed(() => JSON.stringify(myList1.value, null, 2));
const myListString2 = computed(() => JSON.stringify(myList2.value, null, 2));

const theme = useTheme();

const itemStyle = computed(() => {
  if (theme.global.current.value.dark) {
    return {
      background: "#00ACC1",
      color: "black",
    };
  }
  return {
    background: "white",
    color: "initial",
  };
});
const jsonResultStyle = computed(() => {
    if (theme.global.current.value.dark) {
        return {
            background: "#d4edda",
            color: "black"
        };
    }
    return {
        background: "white",
        color: "initial"
    };
});


watch(isDragging, (newValue) => {
  // You can add logic here if needed when dragging starts or stops.
  // The color change is now handled reactively by computed properties.
});

const onThemeChange = (param) => {
  console.log("[event on changeDraggableColor] param:", param);
  // No need to manually change colors, computed properties will handle it.
};

onMounted(() => {
  eventBus.on("changeDraggableColor", onThemeChange);
});

onUnmounted(() => {
  eventBus.off("changeDraggableColor", onThemeChange);
});
</script>

<style>
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
.list-group-item {
  padding: 10px;
  border: 1px solid #ccc;
  margin: 5px 0;
  cursor: grab;
}
.list-group-json-result {
    padding: 10px;
    border: 1px solid #ccc;
}
</style>
