let debug = "";
let sum = 0;

// 반복문1
sum = 0;
for (let i = 1; i <= 100; i++) {
  sum += i;
}
debug += "loop1) " + sum + "\n";

// 반복문2
let inputlist = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
sum = 0;
for (let i of inputlist) {
  sum += i;
}
debug += "loop2) " + sum + "\n";

console.log(debug);
