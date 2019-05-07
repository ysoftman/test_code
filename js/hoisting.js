// javascript 는 함수,변수 선언부분을 hoisting(끌어올린다.)한다.

// 함수 선언으로 함수 작성
// 함수 선언언 이전에 함수를 호출해도 수행된다.
// 함수 선언부가 맨위로 끌여올려지기 때문이다.
aaa()
function aaa() {
    document.getElementById('resultbox1').innerHTML = "aaa";
    console.log("aaa")
}

// 함수 표현식으로 함수 작성
// bbb 함수 표현식은 다음과 같이 var bbb 부분만 위로 hoisting 된다.
// var bbb 
// bbb = function () {
//     document.getElementById('resultbox2').innerHTML = "bbb";
//     console.log("bbb")
// 따라서 함수표현식은 hoisting 되지 않아, bbb()를 함수 선언 이후에 호출해야 된다.
// bbb()
var bbb = function () {
    document.getElementById('resultbox2').innerHTML = "bbb";
    console.log("bbb")
}
bbb()