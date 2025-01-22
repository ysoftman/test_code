let debug = "";

// map 생성
let map = new Map();
debug += "map=" + map + "\n";
// key,value 추가
map.set("name", "ysoftman");
map.set(1, "numberKey_stringValue");
map.set(true, "booleanKey_stringValue");
// debug += "map.set(name, 'ysoftman')=" + map + "\n"
// 맵 전체 내용 출력 방법1
debug += "-----\n";
map.forEach((value, key) => {
  debug += key + ":" + value + "\n";
});
debug += "-----\n";
// 맵 전체 내용 출력 방법2
for (let data of map) {
  debug += data + "\n";
}
debug += "-----\n";
// 맵의 키만 뽑아 보기
for (let key of map.keys()) {
  debug += key + "\n";
}
debug += "-----\n";
// 맵의 밸류만 뽑아 보기
for (let value of map.values()) {
  debug += value + "\n";
}
debug += "-----\n";

// 키로 값 가져오기
debug += "map.get('name')=" + map.get("name") + "\n";
// 삭제
debug += "map.delete(true)=" + map.delete(true) + "\n";
debug += "map.has('name')=" + map.has("name") + "\n";
debug += "map.size=" + map.size + "\n";

//alert(debug)
console.log(debug);

const array1 = [1, 2, 3, 4, 5];
// 배열을 값에 변경해서 새로운 배열 생성
/*
    [
    0: 2
    1: 4
    2: 6
    3: 8
    4: 10
    ]
    */
const map1 = array1.map((x) => x * 2);
console.log(map1);

var KeyValue = [
  {
    key: 1,
    value: 10,
  },
  {
    key: 2,
    value: 20,
  },
  {
    key: 3,
    value: 30,
  },
];
/*
    [
    0: {1: 10}
    1: {2: 20}
    2: {3: 30}
    ]
    */
const map2 = KeyValue.map((obj) => {
  let newObj = {};
  newObj[obj.key] = obj.value;
  return newObj;
});
console.log(map2);
