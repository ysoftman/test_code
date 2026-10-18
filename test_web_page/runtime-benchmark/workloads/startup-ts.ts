// 타입 주석이 있는 .ts 를 변환 도구 없이 바로 실행 (node 는 type stripping)
interface Greeting {
  text: string;
  count: number;
}
const greeting: Greeting = { text: "hello", count: 1 };
console.log(greeting.text);
