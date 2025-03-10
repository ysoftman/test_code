let debug = "";
let myobj = {
  name: "ysoftman",
  age: 12,
  fruites: ["lemon", "appel", "orange"],

  // toString() 으로 스트링으로 출력한 포맷을 만들수 있다.
  toString() {
    return `myobject content = {name:${this.name}, age:${this.age}}\n`;
  },
};
// toString()을 사용
debug += "myobj.toString()=" + myobj;

let jsonstr = JSON.stringify(myobj);
// JSON stringify 를 사용할 수도 도있다.
debug += "JSON.stringify(myobj)=" + jsonstr + "\n";
debug += "---------------\n";
// json 스트링 파싱
debug += "parse stringified json\n";
let json = JSON.parse(jsonstr);
debug += "json.name=" + json.name + "\n";
debug += "json.age=" + json.age + "\n";
debug += "json.fruites=" + json.fruites + "\n";
console.log(debug);

debug = "";
// `` 로 jsonstring 바로 표현
jsonstr = `{
		"a": "aaaa",
		"b": 123.456,
		"c": [1, 2, 3, "a", "b", "c"],
		"d": {
			"member1" : "string",
			"member2" : 99999
		}
	}`;
json = JSON.parse(jsonstr);
debug += "jsonstr=" + jsonstr + "\n";
debug += "---------------\n";
debug += "json=" + json + "\n";
debug += "json.a=" + json.a + "\n";
debug += "json.b=" + json.b + "\n";
debug += "json.c=" + json.c + "\n";
debug += "json.d=" + json.d + "\n";
debug += "json.d.member1=" + json.d.member1 + "\n";
debug += "json.d.member2=" + json.d.member2 + "\n";
console.log(debug);

//console.log("checkJSON('a') ==> " + checkJSON('a'));
console.log("checkJSON('{\"a\":123}') ==> " + checkJSON('{\"a\":123}'));

function checkJSON(str) {
  let ret = "";
  try {
    JSON.parse(str);
    console.log("valid JSON");
    ret = "valid json";
  } catch (e) {
    console.log("invalid JSON, error:", e);
    ret = "invalid json";
  }
  return ret;
}
