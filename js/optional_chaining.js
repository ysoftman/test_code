let user = {
  name: "ysoftman",
  age: 10,
};
console.log(user.age);
console.log(user.name);
// phonenumer 가 undefined 라 .mobile 접근하면 에러 발생
//console.log(user.phonenumer.mobile)

// && 로 user.phonenumer 이 true 일때만 접근하도록 할 수 있다.
console.log(user.phonenumer && user.phonenumer.mobile);

// optional chaining 으로 ?. 의 앞에 있는 대상이 undefined 나 null 이면 평가(접근)를 멈춘다.
console.log(user.phonenumer?.mobile);
