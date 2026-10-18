// node:fs 동기 API 로 4 KB 파일 5000개 쓰기 → 읽기 → 삭제
import { mkdtempSync, readFileSync, rmSync, writeFileSync } from "node:fs";
import { tmpdir } from "node:os";
import { join } from "node:path";

const dir = mkdtempSync(join(tmpdir(), "runtime-bench-"));
const body = "x".repeat(4096);
let total = 0;
for (let i = 0; i < 5000; i++) writeFileSync(join(dir, `${i}.txt`), body);
for (let i = 0; i < 5000; i++)
  total += readFileSync(join(dir, `${i}.txt`), "utf8").length;
rmSync(dir, { recursive: true });
console.log(total);
