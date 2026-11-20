import { resolve, sep } from "node:path";

const root = resolve(import.meta.dir);
// 페이지가 ../common/doc.css 를 참조하므로 /common/ 요청만 test_pages/common 에서 서빙한다
const commonRoot = resolve(root, "../common");
const commonPrefix = "/common/";
const port = Number(Bun.env.PORT ?? 3000);

Bun.serve({
  port,
  async fetch(request) {
    const pathname = new URL(request.url).pathname;

    const routeAliases: Record<string, string> = {
      "/formatter": "/formatter.html",
      "/lint": "/lint.html",
      "/runtime": "/runtime.html",
      "/test": "/test.html",
      "/bundler": "/bundler.html",
    };
    const resolvedPathname =
      pathname === "/" ? "/index.html" : (routeAliases[pathname] ?? pathname);

    let decodedPath: string;
    try {
      decodedPath = decodeURIComponent(resolvedPathname);
    } catch {
      return new Response("Bad Request", { status: 400 });
    }

    const [base, relativePath] = decodedPath.startsWith(commonPrefix)
      ? [commonRoot, decodedPath.slice(commonPrefix.length - 1)]
      : [root, decodedPath];
    const filePath = resolve(base, `.${relativePath}`);
    if (!filePath.startsWith(`${base}${sep}`)) {
      return new Response("Not Found", { status: 404 });
    }

    const file = Bun.file(filePath);
    if (!(await file.exists())) {
      return new Response("Not Found", { status: 404 });
    }

    return new Response(file);
  },
});

console.log(`Bun Benchmark: http://localhost:${port}/`);
