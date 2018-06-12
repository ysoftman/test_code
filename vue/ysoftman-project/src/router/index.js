/* eslint-disable */
import Vue from 'vue'
import Router from 'vue-router'
import HelloWorld from '@/components/HelloWorld'
import Alert from '@/components/Alert'
import BindMessage from '@/components/BindMessage'
import DataList from '@/components/DataList'
import Component from '@/components/Component'
import HelloVue from '@/components/HelloVue'

Vue.use(Router)

const NotFound = {
  template: '<div>Not Found</div>'
}

export default new Router({
  // 디폴트 hash mode ;  http://localhost:8080/# 와 같이 hash 가 붙는다.
  // HTML5 history mode : http://localhost:8080/ 와 같이 hash 가 붙지 않는다.
  mode: 'history',
  // 라우팅 정보
  routes: [{
    path: '/',
    default: true,
    name: 'HelloWorld',
    component: HelloWorld
  }, {
    path: '/alert',
    name: 'Alert',
    component: Alert
  }, {
    path: '/hellovue',
    name: 'HelloVue',
    component: HelloVue
  }, {
    path: '/bindmessage',
    name: 'BindMessage',
    component: BindMessage
  }, {
    path: '/datalist',
    name: 'DataList',
    component: DataList
  }, {
    path: '/component',
    name: 'Component',
    component: Component
  }, {
    path: '*',
    name: 'NotFound',
    component: NotFound
  }]
})
