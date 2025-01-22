// type coercion(강요,강제) 로 type conversion 의미로
// js 는 다른 타임의 데이터 연산을 가능하게 해준다.

// 문자와 숫자를 더할 수 없으니 1숫자를 1문자로 취급해서 더한다.
console.log("ysoftman" + 1);
// 1+2 을 숫자로 더하고 ysoftman 문자와 합친다.
console.log(1 + 2 + "ysoftman");

// 1 + true(숫자 1로 취급 더한다) 그리괴 문자와 합치기 위해서 3(숫자) 3(문자로) conversion 한다.
console.log(1 + true + "ysoftman");
