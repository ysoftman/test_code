let debug = "";
let innerdebug = "";
// 팩토리얼 재귀함수
function factorial(n) {
  if (n <= 1) {
    return n;
  }
  innerdebug += n + "*" + (n - 1) + "\n";
  return n * factorial(n - 1);
}

debug += "factorial(6)=" + factorial(5) + "\n";
debug += innerdebug;
console.log(debug);
