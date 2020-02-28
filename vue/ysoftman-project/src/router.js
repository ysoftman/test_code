/* eslint-disable */
import Vue from 'vue'
import Router from 'vue-router'
import HelloWorld from '@/components/HelloWorld'
import Alert from '@/components/Alert'
import BindMessage from '@/components/BindMessage'
import DataTable from '@/components/DataTable'
import DataList from '@/components/DataList'
import MyComponent from '@/components/MyComponent'
import ModifyArray from '@/components/ModifyArray'
import Draggable from '@/components/Draggable'
import NotFound from '@/components/NotFound'
// import ToolBar from '@/components/ToolBar'
import VuetifyDark from '@/components/VuetifyDark'

Vue.use(Router)

export default new Router({
  // 디폴트 hash mode ;  http://localhost:8080/# 와 같이 hash 가 붙는다.
  // HTML5 history mode : http://localhost:8080/ 와 같이 hash 가 붙지 않는다.
  // 히스토리 모드에서는 # 없는 path 를 사용하기 때문에 브라우저 refresh 시 서버에 해당 path 로 요청해 서버에서도 각 path 마다 처리를 해주지 않으면 404 에러가 발생한다.
  // vue 의 컴포넌트 path, 백엔드 서버의 path 가 다를 경우 hash 모드를 사용하자.
  // mode: 'history',
  // 라우팅 정보
  routes: [{
    path: '/',
    name: "Main",
    default: true,
  },
  {
    path: '/helloworld',
    default: true,
    name: 'HelloWorld',
    component: HelloWorld
  },
  {
    path: '/alert',
    name: 'Alert',
    component: Alert
  },
  {
    path: '/modifyarray',
    name: 'ModifyArray',
    component: ModifyArray
  },
  {
    path: '/bindmessage',
    name: 'BindMessage',
    component: BindMessage
  },
  {
    path: '/datalist',
    name: 'DataList',
    component: DataList
  },
  {
    path: '/datatable',
    name: 'DataTable',
    component: DataTable
  },  
  {
    path: '/mycomponent',
    name: 'MyComponent',
    component: MyComponent
  },
  {
    path: '/draggable',
    name: 'Draggable',
    component: Draggable
  },
  {
    path: '/vuetifydark',
    name: 'VuetifyDark',
    component: VuetifyDark
  },
  {
    path: '*',
    name: 'NotFound',
    component: NotFound
  }]
})
