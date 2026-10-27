import { resolve, sep } from "node:path";

const root = resolve(import.meta.dir);
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

    const filePath = resolve(root, `.${decodedPath}`);
    if (!filePath.startsWith(`${root}${sep}`)) {
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
