// node:http 기준선 — 라우터 없이 경로를 직접 나눈다
import { createServer } from "node:http";

const json = (res, body) => {
	res.setHeader("content-type", "application/json");
	res.end(JSON.stringify(body));
};
const notFound = (res) => {
	res.statusCode = 404;
	res.end();
};

createServer((req, res) => {
	const [, a, b, c, d, e] = req.url.split("/");
	if (e !== undefined) return notFound(res);
	if (req.method === "POST")
		return a === "user" && b === undefined
			? json(res, { ok: true })
			: notFound(res);
	if (req.method !== "GET") return notFound(res);
	if (b === undefined) {
		if (a === "") return res.end("Hello World");
		if (a === "json") return json(res, { message: "Hello World" });
		if (a === "health") return res.end("ok");
		if (a === "posts") return json(res, []);
		return notFound(res);
	}
	if (a === "posts" && c === undefined) return json(res, { id: b });
	if (a === "user" && c === undefined) return json(res, { id: b });
	if (a === "user" && c === "posts" && d !== undefined)
		return json(res, { id: b, postId: d });
	notFound(res);
}).listen(Number(process.env.PORT));
