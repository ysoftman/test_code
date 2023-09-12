let str = "ysoftmanLemonAppleOragne."
console.log("str:", str)

// slice(시작인덱스, 끝인덱스)
console.log("str.slice(0, 8):", str.slice(0, 8)) // ==> ysoftman
console.log("str.slice(8, 8 + \"lemon\".length):", str.slice(8, 8 + "lemon".length)) // ==> Lemon
// 끝이 없으면 끝까지
console.log("str.slice(8 + \"lemon\".length, ):", str.slice(8 + "lemon".length, )) // ==> AppleOrange.

let arr = ["Lemon", "Apple", "Oragne"]
console.log("arr:", arr)
console.log("arr.slice(0, 2):", arr.slice(0, 2)) // ==> ["Lemon", "Apple"]
console.log("arr.slice(1,):", arr.slice(1, )) // ==> ["Apple", "Oragne"]
