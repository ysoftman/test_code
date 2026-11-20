// Bun.serve 기준선 — 내장 routes 사용
Bun.serve({
	port: Number(process.env.PORT),
	routes: {
		"/": () => new Response("Hello World"),
		"/json": () => Response.json({ message: "Hello World" }),
		"/health": () => new Response("ok"),
		"/posts": () => Response.json([]),
		"/posts/:id": (req) => Response.json({ id: req.params.id }),
		"/user/:id": (req) => Response.json({ id: req.params.id }),
		"/user/:id/posts/:postId": (req) =>
			Response.json({ id: req.params.id, postId: req.params.postId }),
		"/user": { POST: () => Response.json({ ok: true }) },
	},
	fetch: () => new Response(null, { status: 404 }),
});
