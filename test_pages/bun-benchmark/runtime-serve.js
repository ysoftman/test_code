// HTTP 서버 — HTTP_API=native 면 런타임 기본 API, node 면 node:http
import process from "node:process";

const port = Number(process.env.PORT ?? 3000);
const native = process.env.HTTP_API !== "node";
const body = "hello";

if (native && globalThis.Bun) {
  Bun.serve({ port, fetch: () => new Response(body) });
} else if (native && globalThis.Deno) {
  Deno.serve({ port, onListen() {} }, () => new Response(body));
} else {
  const { createServer } = await import("node:http");
  createServer((_, res) => res.end(body)).listen(port);
}
