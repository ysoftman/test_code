// ysoftman
// 인코딩 테스트
// 공백은 %20 으로 처리된다.
// 다른언어에서는 공백을 + 로도 인코딩 하지만, URI 스펙상으로는 + 는 예약어로 취급한다.
// https://tools.ietf.org/html/rfc3986#section-2.2
let inputstr = "http://ysoftman.com/query?key1=abc&key2=윤병훈 lemon apple orange";

// escape 알파벳,숫자 제외한 문자를 유니코드로 인코딩
// 한글과 같은 2바이트 문자는 %uxxxx 로 인코딩된다.
let enc = escape(inputstr);
let dec = (enc);
console.log("[escape()]" + enc + "\n" + "[unescape()]" + dec)

// encodeURI  알파벳,숫자 제외한 문자와 특수문자는 제외하고 인코딩
enc = encodeURI(inputstr);
dec = decodeURI(enc);
console.log( "[encodeURI()]" + enc + "\n" + "[decodeURI()]" + dec)

// encodeURIComponent 알파벳,숫자 제외하고 특수문자 포함하여 인코딩
enc = encodeURIComponent(inputstr);
dec = decodeURIComponent(enc);
console.log("[encodeURIComponent()]" + enc + "\n" + "[decodeURIComponent()]" + dec)

// base64 인코딩
// base64 인코딩을 위해선 한글이 있으면 안됨으로 URI 인코딩한후 사용한다
enc = btoa(encodeURIComponent(inputstr));
dec = (atob(enc));
console.log("[btoa(encodeURIComponent())]" + enc + "\n" + "[decodeURIComponent(atob())]" + dec)

enc = '\\u003cdiv\\u003ehello world\\u003c/div\\u003e';
dec = decodeURIComponent(JSON.parse('"' + enc + '"'));
let dec2 = dec.replace(/[<]/g, '&lt;');
console.log( "[unicode escape]" + enc + "\n" + "[decodeURIComponent(JSON.parse())]" + dec + "[dec.replace(/[<]/g,'&lt;')]" + dec2)

