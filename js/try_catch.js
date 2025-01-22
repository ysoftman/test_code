// try catch test
try {
  alert_1123("ysoftman");
} catch (err) {
  // 에러 처리
  console.log("err ", err);
} finally {
  console.log("try cath 관계 없이 마지막에 실행되는 finally");
}

var v = "123";
try {
  if (v == "123") {
    // throw 커스텀 에러(err)를 만들 수 있다.
    throw "커스텀 에러 정의";
  }
} catch (err) {
  console.log("err ", err);
}
