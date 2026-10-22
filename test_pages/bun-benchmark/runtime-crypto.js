// node:crypto sha256 으로 512 MB 해시 — 네이티브 바인딩 성능
import { createHash } from "node:crypto";

const chunk = new Uint8Array(1 << 20).fill(7);
const hash = createHash("sha256");
for (let i = 0; i < 512; i++) hash.update(chunk);
console.log(hash.digest("hex"));
