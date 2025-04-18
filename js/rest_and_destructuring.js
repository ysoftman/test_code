// ...(rest) 파라미터로 여러 인자를 표현한다.
// ES5 부터 구조분해(destructuring)로 array, object 의 값을 분해해서 할당 할 수 있다.
function test1() {
  // 2 를 건너뛰고 a=1, b=3 으로 할당, rest 4~끝까지 값이 배열로 할당
  let [a, , b, ...rest] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
  console.log(a);
  console.log(b);
  console.log(rest);
}

function test2() {
  let arr1 = ["lemon", "apple", "orange"];
  console.log(arr1);
  // arr1 의 두번재값은 건너뛰고 c='lemon' d='orange' 로 할당 할 수 있다.
  let [a, , b] = arr1;
  console.log(a);
  console.log(b);
}

function test3() {
  let lemon = {
    name: "lemon",
    cost: 100,
    country: "US",
  };
  // 오브젝트의 모든 필드를 명시하지 않고 ...(rest) 를 사용하면 된다.
  let my_lemon1 = {
    ...lemon,
    additional: "ysoftman", // 추가 필드
  };
  // 참고로 다음과 같이 사용하면 참조형식(주소공유)이라
  // lemon, my_lemon2 값을 서로 공유한다.
  let my_lemon2 = lemon;
  lemon.cost = 150; // lemon 값을 변경함녀 my_lemon2 에도 반영
  my_lemon2.year = 2010; // my_lemon2 에 추가하면 lemon 에도 반영
  console.log("lemon:", lemon);
  console.log("my_lemon1:", my_lemon1);
  console.log("my_lemon2:", my_lemon2);
}

function test4() {
  let obj1 = {
    name: "ysoftman",
    age: "99",
    innerobj: {
      innerField1: "a",
      innerField2: "b",
    },
  };
  console.log(obj1);
  // object 의 경우 {} 로 감싸주고 이름과 구조만 같으면 오브젝트내의 필드들을 할당할 수 있다.
  let {
    name,
    age,
    innerobj,
    zzz, // zzz 처럼 정의 되지 않으면 자동으로 undefined 로 할당된다.
  } = obj1;
  console.log(name); // ysoftman
  console.log(age); // 99
  console.log(innerobj); // object type
  console.log(zzz); // undefined
  // 함수에서 object 를 받을때도 destructure 할 수 있다.
  // destructure 한 innerobj 를 x 변수로 할당해서 사용할 수 도 있다.
  function f({ innerobj: x }) {
    console.log(x.innerField1);
    console.log(x.innerField2);
  }
  f(obj1);
}

test1();
test2();
test3();
test4();
