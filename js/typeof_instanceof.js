// primitive type 은 typeof 가 올바르게 작동한다.
console.log(typeof "ysoftman") // string
console.log(typeof 123) // number
console.log(typeof 1.23) // number
console.log(typeof null) // object
console.log(typeof [1, 2, 3]) // object
console.log(typeof {}) // object

console.log(123 instanceof Number) // false, primitive type 의 경우 instanceof 가 원하는대로 작동하지 않는다.

// array 경우 instanceof 로 체크할 수 있다.
console.log({} instanceof Object) // true
console.log({} instanceof Array) // false
console.log([1, 2, 3] instanceof Array) // false
