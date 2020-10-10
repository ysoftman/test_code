<template>
  <v-container fluid>
    <div id="bindmessage">
      <!--message 속성을 title 속성과 바인딩-->
      <h3 :title="message">이 글자에 마우스를 올려 보면 마우스 포인터에 현재 시간이 보입니다.</h3>
    </div>
  </v-container>
</template>

<!--scrit file-->
<script>
/* eslint-disable */
export default {
  name: "BindMessage",
  data() {
    return {
      message: "동적으로 생성되는 메시지\n현재 시간: " + new Date()
    };
  }
};
</script>
