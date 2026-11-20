import { Elysia } from "elysia";

new Elysia()
	.get("/", () => "Hello World")
	.get("/json", () => ({ message: "Hello World" }))
	.get("/health", () => "ok")
	.get("/posts", () => [])
	.get("/posts/:id", ({ params }) => ({ id: params.id }))
	.get("/user/:id", ({ params }) => ({ id: params.id }))
	.get("/user/:id/posts/:postId", ({ params }) => ({
		id: params.id,
		postId: params.postId,
	}))
	.post("/user", () => ({ ok: true }))
	.listen(Number(process.env.PORT));
