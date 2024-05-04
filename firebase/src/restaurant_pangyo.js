
import "./bootstrap.scss"
import {readRestaurantAll,updateRestaurantAll} from "./common.js"
const coll = "restaurant";
window.onload = function () {
    readRestaurantAll(coll);

    //컬렉션: restaurant 문서 추가 및 업데이트(db export 기능이 있지만 결재가 필요함)
    //localhost:5002/restaurant_pangyo.html 접속
    //구글 로그인 후 강제 refresh(ctrl+shift+r)
    //식당리스트가 firestore 에 자동 추가되어 보인다.
    //updateRestaurantAll();
}
