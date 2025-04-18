let now = new Date();
// Tue May 14 2019 17:08:44 GMT+0900 (한국 표준시)
console.log("now:", now);

let Jan01_1970 = new Date(0);
console.log(Jan01_1970);

let Jan02_1970 = new Date(24 * 3600 * 1000);
console.log(Jan02_1970);

let date = new Date("2017-01-26");
console.log(date);

// 2011년 1월(0) 1일 2시 3분 4초 5밀리초
date = new Date(2011, 0, 1, 14, 3, 4, 5);
console.log(date);
// 0~59 초
console.log(date.getSeconds());
// 0~59 분
console.log(date.getMinutes());
// 0~23 시
console.log(date.getHours());
// 1~31 일
console.log(date.getDate());
// 0(Jan)~11(Dec) 월
console.log(date.getMonth() + 1);
// YYYY 년
console.log(date.getFullYear());
// 1293858184005 ms(the number of milliseconds since 1970/01/01)
console.log(date.getTime());
// date -> unix time
// 1293858184.005
console.log(date.getTime() / 1000);

let tempDate = new Date();
// +1시간 뒤 시간
tempDate.setHours(date.getHours() + 1);
console.log("+1 hours :", tempDate);
// +50일 뒤 시간
tempDate.setDate(date.getDate() + 50);
console.log("+50 Days :", tempDate);

// unix time -> date
date = new Date(date.getTime());
// Sat Jan 01 2011 14:03:04 GMT+0900 (Korean Standard Time)
console.log(date);
// 2011-01-01T05:03:04.005Z
console.log(date.toISOString());
// 2011-01-01T05:03:04.005Z
console.log(date.toJSON());
// Sat, 01 Jan 2011 05:03:04 GMT
console.log(date.toGMTString());
// Sat, 01 Jan 2011 05:03:04 GMT
console.log(date.toUTCString());
// Sat Jan 01 2011 14:03:04 GMT+0900 (Korean Standard Time)
console.log(date.toString());
// Sat Jan 01 2011
console.log(date.toDateString());
// 1/1/2011, 2:03:04 PM
console.log(date.toLocaleString());
// 2:03:04 PM
console.log(date.toLocaleTimeString());

let t =
  date.getFullYear().toString() +
  (date.getMonth() + 1 > 9 ? "" : "0") +
  (date.getMonth() + 1).toString() +
  (date.getDate() > 9 ? "" : "0") +
  date.getDate().toString() +
  (date.getHours() > 9 ? "" : "0") +
  date.getHours().toString() +
  (date.getMinutes() > 9 ? "" : "0") +
  date.getMinutes().toString();
// 201101011403
console.log(t);
