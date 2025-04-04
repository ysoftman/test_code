let debug = "";
// single, double 따옴표 둘다 스트링을 표시하는 것으로 같다.
let str1 = "yoon";
let str2 = "byoung";
// backtick(grave or backquote)으로도 스트링을 표시할 수 있지만
//  embed 표현식으로 확장 할 수 있다.
// 멀티라인을 사용할 수 있다.
let str3 = `hoon 
    ${str1}
    ${str2}
    `;

debug += "str1=" + str1 + "\tstr1.length=" + str1.length + "\n";
debug += "str2=" + str2 + "\tstr2.length=" + str2.length + "\n";
debug += "str3=" + str3 + "\tstr3.length=" + str3.length + "\n";

// 유니코드(최대 4바이트) 표현
debug += "unicode \u{1f60d}";
debug += "\n";

// 스트링에서 문자 하나 액세스
debug += "str1[1]=" + str1[1];
debug += "\n";
debug += "str1.charAt(1)=" + str1.charAt(1);
debug += "\n";

console.log(debug);
