// javascript promise 패턴 방식 테스트
// promise 는 비동기 처리가 완료된후 결과를 주겠다는 약속이다.
// pt 는 파라미터에 따라 1초후 성공, 실패 결과가 된다.
var pt = function (param) {
    // promise 는 pending(진행중), fulfilled(수행완료/성공), rejected(수행실패) 상태가 있다.
    return new Promise(function (success, fail) {
        // 비동기처리를 되고 있음을 가정하기 위해 setTimeout 사용
        // 1초 후
        // param 이 있으면 success 함수 호출하고 fulfilled 상태가 되고
        // param 이 없으면 fail 함수 호출하고 rejected 상태가 되고
        window.setTimeout(function () {
            if (param) {
                success("000 - ok")
            }
            else {
                fail("fail")
            }
        }, 1000)
    });
};

// pt 실행하셔 1초후 비동기 처리가 완료되면 then 으로 선언한 함수들이 실행된다.
// 여기서도 promise 를 생성해 1초 후 다음 then 이 실행되도록 한다.(순서대로 실행 및 결과 보장)
// then 함수 수행시 예외(에러가) 발생하면 catch() 를 실행한다.
pt(true).then(function (param) {
    return new Promise((success) => {
        setTimeout(() => {
            document.getElementById('resultbox1').innerHTML = param;
            success("111 - ok");
        }, 1000)
    });
}).then(function (param) {
    return new Promise((success) => {
        setTimeout(() => {
            document.getElementById('resultbox2').innerHTML = param;
            success("222 - ok")
        }, 1000)
    });
}).then(function (param) {
    return new Promise((success) => {
        setTimeout(() => {
            document.getElementById('resultbox3').innerHTML = param;
            success("333 - ok")
        }, 1000)
    });
}).then(function () {
    JSON.parse("a") // 에러 발생
    // console.log("aaa")
    document.getElementById('resultbox4').innerHTML = "aaa";
}).catch(function () {
    document.getElementById('resultbox4').innerHTML = "error";
});
