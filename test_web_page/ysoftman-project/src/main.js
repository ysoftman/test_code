/* eslint-disable */

import { createApp } from "vue";
import App from "./App.vue";
import router from "./router";
import { createPinia } from "pinia";
import { vuetify } from "./plugins/vuetify";
import mitt from "mitt";
const app = createApp(App);

export const eventBus = mitt();

app.use(createPinia());
app.use(router);
app.use(vuetify);
app.mount("#app");
