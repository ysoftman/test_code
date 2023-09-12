let debug = ""

function plus_a_b(a, b) {
    return a + b
}

// bind 로 첫번째 인자는 고정시켜 놓는다. ==> partial 함수 myplus 를 생성 (부분적용)
// 함수.bind(context, arg1, arg2 ...)
let myplus = plus_a_b.bind(null, 3)
debug += "let myplus = plus_a_b.bind(null, 3)\n"
// 아직 설정되지 않는 2번째 인자 값만 넣어주어 계산한다. 
debug += "myplus(7)=" + myplus(7)

console.log(debug)
