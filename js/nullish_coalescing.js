// nullish 병합 연산자 ?? (nullish coalescing operator)
// ?? 앞의 값이 null, undefined 가이면 값을 출력하고 아니면 ?? 뒤의 값 출력
// eslint 7.2.0 이하에선 ? ? 로 잘못 포맷팅 된다.

// lemon 에 값이 있이서 ?? || 둘다 결과는 1000
let lemon = 1000
console.log("lemon:", lemon)   
console.log(lemon ?? "ok")
console.log(lemon || "ok")

// lemon null 이라 ?? || 둘다 결과는 ok
lemon = null
console.log("lemon:", lemon)
console.log(lemon ?? "ok")
console.log(lemon || "ok")

// lemon = 0은 값은 있어 ?? 는 0을 출력하지만 ||에선 0이 false 로 취급되어 ok 출력
lemon = 0
console.log("lemon:", lemon)
console.log(lemon ?? "ok")
console.log(lemon || "ok")
