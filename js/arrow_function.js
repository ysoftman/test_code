// arrow 함수로 구현을 간결하게 할 수 있다.
// (파라미터) => { 함수내용 } 형식으로 사용한다.
let subFunc = (a, b) => {
  let result = a - b;
  return result;
};
// 함수 내용이 한줄이면 {} 를 생략 할 수 있고 암묵적으로 리턴된다.
let sumFunc = (a, b) => a + b;
// 파라미터가 1개이면 () 를 생략할 수 있다.
let squareFunc = (n) => n * n;
// 파라미터가 없으면 () 만 사용한다
let strFunc = () => "ysoftman";

console.log("(arrow function) sum(3, 4) = " + sumFunc(3, 4));
console.log("(arrow function) sub(3, 4) = " + subFunc(3, 4));
console.log("(arrow function) square(3) = " + squareFunc(3));
console.log("(arrow function) str() = " + strFunc());
