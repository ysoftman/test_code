import fastify from "fastify";

const app = fastify();
app.get("/", () => "Hello World");
app.get("/json", () => ({ message: "Hello World" }));
app.get("/health", () => "ok");
app.get("/posts", () => []);
app.get("/posts/:id", (req) => ({ id: req.params.id }));
app.get("/user/:id", (req) => ({ id: req.params.id }));
app.get("/user/:id/posts/:postId", (req) => ({
	id: req.params.id,
	postId: req.params.postId,
}));
app.post("/user", () => ({ ok: true }));
await app.listen({ port: Number(process.env.PORT) });
