import Vue from 'vue';
import Vuetify from 'vuetify/lib';

Vue.use(Vuetify);

export default new Vuetify({
  theme: {
    // 전역적으로 모든 vue 컴포넌트들에게 dark theme 를 적용한다.
    // dark theme 사용 여부를 localstorage 로 부터 파악한다.
    dark: function () {
      if (localStorage.getItem('dark_theme')) {
        try {
          return (localStorage.getItem('dark_theme'));
        } catch (e) {
          localStorage.removeItem('dark_theme');
        }
      }
    },
  },
});
