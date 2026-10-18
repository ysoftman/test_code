// 재귀 함수 호출 — JIT 성능
const fib = (n) => (n < 2 ? n : fib(n - 1) + fib(n - 2));
console.log(fib(38));
