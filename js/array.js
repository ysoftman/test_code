// 배열은 중복된 값을 허용한다.
let arr = [1, 1, 2, 3, 4, "a", "abc"];
let debug = "arr=" + arr + " arr.length=" + arr.length;
debug += "\n";
// 기본 쉼표(,) 를 구분자로 스트링으로 변환
debug += "arr.join()=" + arr.join();
debug += "\n";
debug += "arr.join(-)=" + arr.join("-");
debug += "\n";
debug += "arr.indexOf(3)=" + arr.indexOf(3);
debug += "\n";
// find 는 찾는 조건이 있는 콜백함수 구현(찾은 요소를 리턴)
debug +=
  "arr.find((item) => {...})=" +
  arr.find((item) => {
    return item == "a";
  });
debug += "\n";
debug += "arr.reverse()=" + arr.reverse();
debug += "\n";
// 배열 처음에 원소 추가
debug +=
  "arr.unshift('first_element')=" +
  arr.unshift("first_element") +
  " arr=" +
  arr;
debug += "\n";
// 배열 처음에 원소 삭제
debug += "arr.shift()=" + arr.shift() + " arr=" + arr;
debug += "\n";
// 배열 끝에 원소 추가
debug += 'arr.push("ysoftman")=' + arr.push("ysoftman") + " arr=" + arr;
debug += "\n";
// 배열 끝에서 원소 삭제
debug += "arr.pop()=" + arr.pop() + " arr=" + arr;
debug += "\n";
// 배열을 이어 붙일때
debug += "arr.concat([99,aaa])=" + arr.concat([99, "aaa"]);
debug += "\n";
debug += "arr.slice(3,5)=" + arr.slice(3, 5);
debug += "\n";
// 1번 인텍스부터 2개 원소 삭제
debug += "arr.splice(1,2)=" + arr.splice(1, 2) + " arr=" + arr;
debug += "\n";
// 원소값 삭제시 해당 값만 undefined 되고 배열의 크기는 변화가 없다.
debug +=
  "delete arr[3]=" +
  delete arr[3] +
  "  arr=" +
  arr +
  "  arr[3]=" +
  arr[3] +
  " arr.length=" +
  arr.length;
debug += "\n";
console.log(debug);

// 기본 , 구분자로 스트링을 배열로 변환
let arrstr = "1,2,3,a,b,c";
debug = "arrstr.split()=" + arrstr.split();
debug += "\n";
console.log(debug);

// 빈 배열 생성 방법1
let myarr1 = [];
// 빈 배열 생성 방법2
let myarr2 = new Array();
debug = "";
debug += "myarr1=" + myarr1 + "\n";
debug += "myarr2=" + myarr2 + "\n";

// 배열에는 서로 다른 타입의 데이터를 저장할 수 있다.
myarr1.push("apple");
// 따옴표 내부에 다른 따옴표를 사용하면 escapge(\)를 사용하지 않아도 된다.
debug += "myarr1.push('apple')=" + myarr1 + "\n";
myarr1.push("banana");
debug += "myarr1.push('banana')=" + myarr1 + "\n";
// ture/false 도 추가 가능
myarr1.push(true);
debug += "myarr1.push(true)=" + myarr1 + "\n";
// key,value
myarr1.push({
  first: "lemon",
  second: "orange",
});
debug += "myarr1.push({first:'lemon', second:'orange'})=" + myarr1 + "\n";
// 함수도 추가할 수 있다.
myarr1.push(function () {
  console.log("function in array");
});
// 스트링을 멀티 라은으로 표시할때는 ` (backtick/backquote/grave) 을 사용하자.
debug +=
  `myarr1.push(function() {
		console.log("function in array")
	})=` +
  myarr1 +
  "\n";

console.log(debug);

debug = "";
debug += "myarr1[0]=" + myarr1[0] + "\n";
debug += "myarr1[1]=" + myarr1[1] + "\n";
debug += "myarr1[2]=" + myarr1[2] + "\n";
debug += "myarr1[3].first=" + myarr1[3].first + "\n";
debug += "myarr1[3].second=" + myarr1[3].second + "\n";
// 배열내의 함수 호출
debug += "myarr1[4]()=" + myarr1[4]() + "\n";
console.log(debug);

// 다차원 배열
let arr2d = [
  [1, 2, 3],
  [4, 5, 6],
];

debug = "";
debug += "arr2d=" + arr2d + "\n";
debug += "arr2d[1][1]=" + arr2d[1][1] + "\n";
// strict equality(===) 는 타입이 다르면 바로 false 를 리턴하는 엄격한 비교 연사자
debug +=
  "String(arr2d)==='1,2,3,4,5,6' --> " +
  (String(arr2d) === "1,2,3,4,5,6") +
  "\n";
console.log(debug);
