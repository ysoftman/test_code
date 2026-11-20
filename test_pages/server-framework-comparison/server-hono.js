// Bun 에서는 Bun.serve, Node.js 에서는 @hono/node-server 로 띄운다
import { Hono } from "hono";

const app = new Hono();
app.get("/", (c) => c.text("Hello World"));
app.get("/json", (c) => c.json({ message: "Hello World" }));
app.get("/health", (c) => c.text("ok"));
app.get("/posts", (c) => c.json([]));
app.get("/posts/:id", (c) => c.json({ id: c.req.param("id") }));
app.get("/user/:id", (c) => c.json({ id: c.req.param("id") }));
app.get("/user/:id/posts/:postId", (c) =>
	c.json({ id: c.req.param("id"), postId: c.req.param("postId") }),
);
app.post("/user", (c) => c.json({ ok: true }));

const port = Number(process.env.PORT);
if (globalThis.Bun) {
	Bun.serve({ port, fetch: app.fetch });
} else {
	const { serve } = await import("@hono/node-server");
	serve({ fetch: app.fetch, port });
}
