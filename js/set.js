let debug = "";
// array 와 같이 다양한 값을 순서대로 저장하지만 array 와는 다리게 중복값은 허용하지 않는다.
let set = new Set();
// 원소 추가
set.add("a");
set.add(123);
set.add({
  name: "ysoftman",
});
debug += "set=" + printSet(set);
// 원소 삭제
set.delete(123);
debug += "set.delete(123)=" + printSet(set) + "\n";

console.log(debug);

// 각 원소 데이터 출력
function printSet(set) {
  let debug = "";
  for (let d of set) {
    if (typeof d["name"] != "undefined") {
      debug += d["name"] + "\n";
    } else {
      debug += d + "\n";
    }
  }
  return debug;
}
