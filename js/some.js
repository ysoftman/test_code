let arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
console.log(arr);

// 배열.some(콜백)
// 배열 요소 중 %2 == 0 인것인 하나라도 있으면 true
const checkHasEven = (num) => num % 2 === 0;
console.log(arr.some(checkHasEven));

// 배열 요소 중 10 이 하나라도 있으면 true
const checkHas10 = (num) => num === 11;
console.log(arr.some(checkHas10));

let a = "apple";
let b = "";
let c = "carrot";
arr = [a, b, c];

// 배열 요소 중 빈값이 하나라도 있으면 true
const checkEmpty = (num) => num === "";
console.log(arr.some(checkEmpty));
