// ysoftman
// 클로져 테스트
function sum(num) {
  var temp = num;
  console.log(num, temp);
  // 내부함수에서는 외부함수의 temp 변수를 사용할 수 있다.
  // 외부의 temp 변수를 num 값으로 유지된다.
  function sumclosure() {
    // 클로저는 외부 함수가 종료되어도 유지되는 내부함수이다.
    // 클로저로 private 한 변수를 구현할 수 있다.
    // 클로저에서의 temp 값은 전역변수 처럼 계속 유지된다.
    return temp++;
  }
  // sumclosure 호출하지 않고 함수 이름을 리턴 한다.
  return sumclosure;
}

// 클로저 함수를 사용시 test_sum 호출하여 사용해야 한다.
// test_sum 은 sum() 함수를 호출하고 sum() 이 리턴한 sumclosure() 를 가르키게 되고
// sum() 는 이제 종료되어 호출할 수 없다.
// 하지만 sumclosure() 클로저 함수는 test_sum 이 참조 중이라 계속 유지된다.
let test_sum = sum(1);

// 지금부터는 test_sum 호출하게 되면 sumclosure()를 호출하게 된다.(콘솔 로그 확인)
let r = test_sum();
let out = "first call result : " + r + "\n";

r = test_sum();
out += "second call result : " + r + "\n";

r = test_sum();
out += "third call result : " + r + "\n";
console.log(out);
