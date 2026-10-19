// 10만 객체 배열을 JSON.stringify → JSON.parse 10회
const data = Array.from({ length: 100_000 }, (_, i) => ({
  id: i,
  name: `user-${i}`,
  tags: ["a", "b", String(i % 7)],
  score: i / 4,
  active: i % 2 === 0,
}));
let bytes = 0;
for (let i = 0; i < 10; i++) {
  const s = JSON.stringify(data);
  bytes += s.length + JSON.parse(s).length;
}
console.log(bytes);
