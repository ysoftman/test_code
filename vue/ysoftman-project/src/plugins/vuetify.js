import Vue from 'vue';
import Vuetify from 'vuetify/lib';

Vue.use(Vuetify);

export default new Vuetify({
  theme: {
    // 전역적으로 모든 vue 컴포넌트들에게 dark theme 를 적용한다.
    // dark theme 사용 여부를 localstorage 로 부터 파악한다.
    dark: function () {
      // value 는 스트링으로 저장되어 있다.
      let v = localStorage.getItem('dark_theme')
      console.log("dark_theme: ", v)
      if (v == 'true') {
        return true
      }
      else {
        return false
      }
      // localStorage.removeItem('dark_theme');
    }()
  }
});
