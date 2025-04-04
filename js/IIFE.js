// 다음 mydata 는 크롬 console 에서 mydata 로 접근해서 수정할 수 있다.
var mydata = ["lemon", "apple"];
console.log(mydata);
// mydata
// (2) ["lemon", "apple"]
// mydata.push("orange")
// 3
// mydata
// (3) ["lemon", "apple", "orange"]

function myfunc() {
  var mydata1 = ["lemon", "apple"];
  console.log(mydata1);
}
myfunc();
// myfunc() 호출로 mydata1 내용을 알아 볼 수 있다.
// myfunc();
// IIFE.html:9 (2) ["lemon", "apple"]

// IIFE(Immediately Invoked Function Expression) 즉시실행함수
(function () {
  // 이 함수내에 있는 데이터들은 외부에서 접근할 수 없다.
  const mydata2 = ["lemon", "apple"];
  console.log(mydata2);
})();
// mydata2
// VM121:1 Uncaught ReferenceError: mydata2 is not defined at <anonymous>:1:1
