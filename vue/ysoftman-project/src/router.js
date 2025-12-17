/* eslint-disable */
import { createRouter, createWebHistory } from "vue-router";

import HelloWorld from "@/components/HelloWorld.vue";
import Alert from "@/components/Alert.vue";
import BindMessage from "@/components/BindMessage.vue";
import DataTable from "@/components/DataTable.vue";
import DataList from "@/components/DataList.vue";
import MyComponent from "@/components/MyComponent.vue";
import ModifyArray from "@/components/ModifyArray.vue";
import Draggable from "@/components/Draggable.vue";
import VuetifyDark from "@/components/VuetifyDark.vue";
import NotFound from "@/components/NotFound.vue";

const routes = [
  {
    path: "/",
    name: "Main",
    component: HelloWorld, // 또는 별도 Main 컴포넌트
  },
  {
    path: "/helloworld",
    name: "HelloWorld",
    component: HelloWorld,
  },
  {
    path: "/alert",
    name: "Alert",
    component: Alert,
  },
  {
    path: "/modifyarray",
    name: "ModifyArray",
    component: ModifyArray,
  },
  {
    path: "/bindmessage",
    name: "BindMessage",
    component: BindMessage,
  },
  {
    path: "/datalist",
    name: "DataList",
    component: DataList,
  },
  {
    path: "/datatable",
    name: "DataTable",
    component: DataTable,
  },
  {
    path: "/mycomponent",
    name: "MyComponent",
    component: MyComponent,
  },
  {
    path: "/draggable",
    name: "Draggable",
    component: Draggable,
  },
  {
    path: "/vuetifydark",
    name: "VuetifyDark",
    component: VuetifyDark,
  },
  {
    path: "/:pathMatch(.*)*",
    name: "NotFound",
    component: NotFound,
  },
];

const router = createRouter({
  history: createWebHistory(),
  routes,
});

export default router;
