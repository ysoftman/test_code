import Router from "@koa/router";
import Koa from "koa";

const router = new Router();
router.get("/", (ctx) => {
	ctx.body = "Hello World";
});
router.get("/json", (ctx) => {
	ctx.body = { message: "Hello World" };
});
router.get("/health", (ctx) => {
	ctx.body = "ok";
});
router.get("/posts", (ctx) => {
	ctx.body = [];
});
router.get("/posts/:id", (ctx) => {
	ctx.body = { id: ctx.params.id };
});
router.get("/user/:id", (ctx) => {
	ctx.body = { id: ctx.params.id };
});
router.get("/user/:id/posts/:postId", (ctx) => {
	ctx.body = { id: ctx.params.id, postId: ctx.params.postId };
});
router.post("/user", (ctx) => {
	ctx.body = { ok: true };
});
new Koa().use(router.routes()).listen(Number(process.env.PORT));
