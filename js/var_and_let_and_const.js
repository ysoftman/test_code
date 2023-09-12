// 전역 변수
var a = "(var) global variable"
// ES6 에 추가된 let, 전역 변수
let aa = "(let) global variable"

// var 는 재선언 가능
var a = "(var) global variable"
// let 은 재선언(redeclare)할수 없다.
// 선은은 했지만 값은 undefined
let aaa

//let aa = "(let) global variable" // Uncaught SyntaxError

function func1() {
    // 지역변수
    var a = "(var) local variable"

    // 지역 변수 사용
    printMessage("a:" + a)

    // var 의 경우 상위(글로벌 변수)를 사용하게 되지만 let 의 경우
    // func1 내에 let 으로 aa 가 선언되어 있으면 에러(Uncaught ReferenceError: aa is not defined)가 발생한다.
    // let aa 선언 이후에 사용해야 되서 변수 사용에 있어 실수를 방지할 수 있다.
    // printMessage("aa:" + aa)
    let aa = "(let) local variable"

    // var 를 명시 하지 않으면 전역변수
    // bun, deno 에선 에러 발생, node 에서만 실행가능
    b = "(var) global variable2"
}


function printMessage(msg) {
    //alert(msg)
    console.log(msg)
    return 0
}

// 전역 변수 사용
printMessage("aaa:" + aaa + "  aa:" + aa)
func1()
printMessage("aaa:" + aaa + "  aa:" + aa)
// 전역 변수 b 사용
printMessage("b:" + b)



// const 는 선언시 할당을 해야 한다.
//const constVal1
//constVal1 = "bbb" // Uncaught TypeError

const constVal1 = "aaa"
// const 은 재선언(redeclare)할수 없다.
//const constVal1 = "aaa" // Uncaught SyntaxError
printMessage("constVal1:" + constVal1)

