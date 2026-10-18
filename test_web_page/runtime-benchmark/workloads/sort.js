// 100만 객체 비교 함수 정렬 + 30만 문자열 기본 정렬 (xorshift 로 결정적 입력)
let s = 42;
const rand = () => {
  s ^= s << 13;
  s ^= s >>> 17;
  s ^= s << 5;
  return (s >>> 0) / 4294967296;
};
const objs = Array.from({ length: 1_000_000 }, () => ({ k: rand() }));
objs.sort((a, b) => a.k - b.k);
const strs = Array.from({ length: 300_000 }, () =>
  Math.floor(rand() * 1e9).toString(36),
);
strs.sort();
console.log(objs[500_000].k, strs[150_000]);
