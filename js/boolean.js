let name = "ysoftman"
console.log("typeof(name)=", typeof (name), " name=", name)
// !(not) -> 변수를 값 존재 여부 boolean 캐스팅
console.log("typeof(name)=", typeof (name), " !name=", !name)
// !!(not not)
console.log("typeof(name)=", typeof (name), " !!name=", !!name)

name = ""
console.log("typeof(name)=", typeof (name), " name=", name)
console.log("typeof(name)=", typeof (name), " !name=", !name)
console.log("typeof(name)=", typeof (name), " !!name=", !!name)

// name2 is boolean type
let name2 = !name
console.log("typeof(name2)=", typeof (name2), " name2=", !!name2)
