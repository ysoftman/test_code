// javascript 모듈로 외부로 노출하기 위해 export 를 사용한다.
// 변수,함수 등을 노출하여 외부에서 import 해서 사용한다.
// import 시 {} 사용해야 한다.
export let fruits = ["lemon", "apple"];
export let myname = "ysoftman";
export let myfunc = () => {
  console.log("this is myfunc");
};

// export default 모듈당 하번만 사용 가능한다.
// import 시 {} 사용하지 않아야 한다.
export default function mydefaultfunc() {
  console.log("this is mydefaultfunc");
}
