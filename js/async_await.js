// javascript async,await 패턴 방식 테스트
// promise 는 비동기 처리가 완료된후 결과를 주겠다는 약속이다.
// async,await 를 사용하면 promise 를 좀더 간단하게 사용할 수 있다.


function umm(param) {
    // promise 는 pending(진행중), fulfilled(수행완료/성공), rejected(수행실패) 상태가 있다.
    return new Promise(function (success, fail) {
        // 비동기처리를 되고 있음을 가정하기 위해 setTimeout 사용
        // 1초 후
        // param 이 있으면 success 함수 호출하고 fulfilled 상태가 되고
        // param 이 없으면 fail 함수 호출하고 rejected 상태가 된다.
        window.setTimeout(function () {
            if (param) {
                success(param + "_ok")
            }
            else {
                fail("fail")
            }
        }, 1000)
    });
}

// async 를 붙이면 비동기 함수로 정의되며 promise 를 리턴받을 수 있다.
async function getSomething() {
    // await 는 async 함수내에서만 사용할 수 있다.
    // await 은 promise 리턴하는 함수에서만 사용할 수 있다.
    // await 이 붙인 함수가 종료될때까지 기다린다.
    document.getElementById("resultbox1").innerHTML = await umm("lemon")
    document.getElementById("resultbox2").innerHTML = await umm("banana")

    let mapFruite = new Map()
    mapFruite.set("resultbox3", "ornage")
    mapFruite.set("resultbox4", "apple")
    // 다음과 같은 forEach 내에서는 익명함수에 async를 추가해도 순차 실행이 안된다.
    // mapFruite.forEach(async (value, key) => {
    //     document.getElementById(key).innerHTML = await umm(value)
    // });
    // 다음과 같이 for 로 순차실행 할 수 있다.
    for (const item of mapFruite) {
        document.getElementById(item[0]).innerHTML = await umm(item[1])
    }
};

getSomething();