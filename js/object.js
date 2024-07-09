// 오브젝트 생성 - 생성자 사용
// let myinfo = new object()
// 오브젝트 생성 - 리터럴 사용
// let myinfo = {}
let myinfo = {
  name: "ysoftman",
  age: 30,
  // 오브제트내의 함수(메소드)에서 오브젝트 변수에 접급하기 위해선 this 자시자를 사용해야 한다.
  // this 지시작 없으면 undefined 에러가 발생한다.
  add_age() {
    this.age += 10;
  },
};

let message = "";
// 오브젝트 내부 변수 접근
message += "myinfo.name: " + myinfo.name;
message += "\n";
message += 'myinfo["name"]: ' + myinfo["name"];
message += "\n";
message += "myinfo.age: " + myinfo.age;
message += "\n";

// 오브젝트내 함수 호출
myinfo.add_age();
message += "myinfo.age(add_age): " + myinfo.age;
message += "\n";

// 오브젝트내 변수 추가
myinfo.address = "seoul";
message += "myinfo.address: " + myinfo.address;
message += "\n";

// 공백이 포함된 변수는 bracket 사용해 read/write 한다.
myinfo["phone number"] = "123-456-789";
message += 'myinfo["phone number"]: ' + myinfo["phone number"];
message += "\n";

// 같은 오브젝트가 필요한 경우 function 을 만들고 new 로 오브젝트를 생성하자
function user(name, age) {
  this.name = name;
  this.age = age;
}

let user1 = new user("bill", 10);
message += "user1.name: " + user1.name;
message += "\nuser1.age: " + user1.age;
message += "\n";

let user2 = new user("yoon", 20);
message += "user2.name: " + user2.name;
message += "\nuser2.age: " + user2.age;
message += "\n";

console.log(message);
