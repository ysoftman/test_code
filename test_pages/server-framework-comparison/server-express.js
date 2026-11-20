import express from "express";

const app = express();
app.get("/", (_, res) => res.send("Hello World"));
app.get("/json", (_, res) => res.json({ message: "Hello World" }));
app.get("/health", (_, res) => res.send("ok"));
app.get("/posts", (_, res) => res.json([]));
app.get("/posts/:id", (req, res) => res.json({ id: req.params.id }));
app.get("/user/:id", (req, res) => res.json({ id: req.params.id }));
app.get("/user/:id/posts/:postId", (req, res) =>
	res.json({ id: req.params.id, postId: req.params.postId }),
);
app.post("/user", (_, res) => res.json({ ok: true }));
app.listen(Number(process.env.PORT));
