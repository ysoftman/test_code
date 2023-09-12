// null, undefined, boolean, number, string, symbol(ECMAscript6) 기본(primitive) 타입이 있고
// boolean, number, string, symbol 는 object wrapper 로 사용된다.
// null, undefined 는 object wrapper 가 아니기 때문에 method 를 제공하지 않는다.
// string 기본 타입의 변수이지만
let str = "ysoftman"

let debug = "str=" + str
debug += "\n"
// 오브젝트로 string 메소드를 사용할 수 있다.
debug += "str.substr(1,4)=" + str.substr(1, 4)
debug += "\n"
debug += "str.bold()=" + str.bold()
debug += "\n"
debug += "str.fixed()=" + str.fixed()
debug += "\n"
debug += "str.length=" + str.length
debug += "\n"
debug += "str.toUpperCase()=" + str.toUpperCase()
debug += "\n"
// undefined 에러발생,, 속성을 추가할 수 없다.j
//str.customproerty = 1
debug += "str.customproerty=" + str.customproerty
debug += "\n"
debug += "\n"


let num = 123456789
debug += "num=" + num
debug += "\n"
// 소수접 2 째자리 까지 표기
debug += "num.toFixed(2)=" + num.toFixed(2)
debug += "\n"
debug += "num.toString()=" + num.toString()
debug += "\n"
debug += "num.toExponential(10)=" + num.toExponential(10)
debug += "\n"
debug += "\n"

let bool = true
debug += "bool=" + bool
debug += "\n"
debug += "bool.valueOf()=" + bool.valueOf()
debug += "\n"

console.log(debug)
