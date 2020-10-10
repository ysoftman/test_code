/* eslint-disable */
import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import './registerServiceWorker'
import "vuetify/dist/vuetify.min.css";
import vuetify from './plugins/vuetify';
Vue.use(vuetify);

Vue.config.productionTip = false


// silbling component 들간의 통신을 위한 이벤트 버스
export const eventBus = new Vue();

new Vue({
  router,
  store,
  vuetify,
  render: h => h(App)
}).$mount('#app')
