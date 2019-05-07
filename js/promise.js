// javascript promise 패턴 방식 테스트
// promise 는 비동기 처리가 완료된후 결과를 주겠다는 약속이다.
// pt 는 파라미터에 따라 5초후 성공, 실패 결과가 된다.
var pt = function (param) {
    return new Promise(function (success, fail) {
        // 비동기처리를 되고 있음을 가정하기 위해 setTimeout 사용
        window.setTimeout(function () {
            if (param) {
                success("success")
            }
            else {
                fail("fail")
            }
        }, 5000)
    });
};

// pt 실행하셔 5초후 비동기 처리가 완료되면 then 으로 선언한 함수들이 실행된다.
// then 함수 수행시 예외(에러가) 발생하면 catch() 를 실행한다.
pt(true).then(function (param) {
    console.log(param)
    document.getElementById('resultbox1').innerHTML = param;
}).then(function () {
    JSON.parse("a") // 에러 발생
    console.log("aaa")
    document.getElementById('resultbox2').innerHTML = "aaa";
}).catch(function () {
    console.log("error")
    document.getElementById('resultbox2').innerHTML = "error";
});