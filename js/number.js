let debug = "";

let bignum1 = 1200000000;
debug += "bignum1=" + bignum1;
debug += "\n";

// 지수로 표현할수도 있다.
let bignum2 = 1.2e9;
debug += "bignum2=" + bignum2;
debug += "\n";

let num1 = -123.456;
let num2 = 123.456;
debug += "num1=" + num1;
debug += "\n";
debug += "num2=" + num2;
debug += "\n";

// 10진수 기반으로 스트링으료 변환
debug +=
  "num1.toString()=" + num1.toString() + "\tnum2.toString()=" + num2.toString();
debug += "\n";

// 16진수 기반 스트링으로 변환
debug +=
  "num1.toString(16)=" +
  num1.toString(16) +
  "\tnum2.toString()=" +
  num2.toString(16);
debug += "\n";

// 소수접 1째자리까지만 (반올림) 표기
debug +=
  "num1.toFixed(1)=" + num1.toFixed(1) + "\tnum2.toFixed(1)=" + num2.toFixed(1);
debug += "\n";

// 절대값
debug +=
  "Math.abs(num1)=" + Math.abs(num1) + "\tMath.abs(num2)=" + Math.abs(num2);
debug += "\n";
// 버림(값이 작아지는 쪽으로 반올림)
debug +=
  "Math.floor(num1)=" +
  Math.floor(num1) +
  "\tMath.floor(num2)=" +
  Math.floor(num2);
debug += "\n";
// 올림(값이 커지는쪽으로 반올림)
debug +=
  "Math.ceil(num1)=" + Math.ceil(num1) + "\tMath.ceil(num2)=" + Math.ceil(num2);
debug += "\n";
// 반올림
debug +=
  "Math.round(num1)=" +
  Math.round(num1) +
  "\tMath.round(num2)=" +
  Math.round(num2);
debug += "\n";
debug +=
  "Math.round(num1-0.2)=" +
  Math.round(num1 - 0.2) +
  "\tMath.round(num2-0.2)=" +
  Math.round(num2 - 0.2);
debug += "\n";
console.log(debug);
