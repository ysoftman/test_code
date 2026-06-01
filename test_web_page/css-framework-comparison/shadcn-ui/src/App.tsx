import { useEffect, useState } from "react";
import { Button } from "@/components/ui/button";
import {
  Card,
  CardHeader,
  CardTitle,
  CardDescription,
  CardFooter,
} from "@/components/ui/card";
import { Input } from "@/components/ui/input";
import { Label } from "@/components/ui/label";
import { Checkbox } from "@/components/ui/checkbox";
import { cn } from "@/lib/utils";

// 모든 프레임워크가 공유하는 데모 사양:
// 1) 다크모드 토글  2) 버튼 변형  3) 카드  4) 폼(입력 -> 제출 결과 표시)

const ROLES = ["Frontend", "Backend", "Designer", "PM"];

export default function App() {
  const [dark, setDark] = useState(false);

  const [name, setName] = useState("");
  const [role, setRole] = useState(ROLES[0]);
  const [agree, setAgree] = useState(false);
  const [submitted, setSubmitted] = useState<string | null>(null);

  // 부모(비교 페이지)에서 일괄 테마 적용 메시지를 받는다.
  useEffect(() => {
    const onMsg = (e: MessageEvent) => {
      if (e.data?.type === "setTheme") setDark(!!e.data.dark);
    };
    window.addEventListener("message", onMsg);
    return () => window.removeEventListener("message", onMsg);
  }, []);

  return (
    <div className={dark ? "dark" : ""}>
      <div className="min-h-screen bg-background text-foreground">
        {/* Header */}
        <header className="flex items-center gap-3 border-b px-6 py-3">
          <h1 className="text-lg font-semibold">shadcn/ui</h1>
          <span className="text-sm text-muted-foreground">
            복붙형 컴포넌트 · Tailwind + Radix
          </span>
          <Button
            variant="outline"
            size="sm"
            className="ml-auto"
            onClick={() => setDark((d) => !d)}
            aria-label="toggle dark mode"
          >
            {dark ? "☀️ Light" : "🌙 Dark"}
          </Button>
        </header>

        <main className="mx-auto flex max-w-3xl flex-col gap-8 px-6 py-8">
          {/* Buttons */}
          <section>
            <h2 className="mb-3 text-base font-semibold">Buttons</h2>
            <div className="flex flex-wrap gap-3">
              <Button>Contained</Button>
              <Button variant="outline">Outlined</Button>
              <Button variant="ghost">Text</Button>
              <Button>❤ With Icon</Button>
              <Button disabled>Disabled</Button>
            </div>
          </section>

          <hr />

          {/* Card */}
          <section>
            <h2 className="mb-3 text-base font-semibold">Card</h2>
            <Card className="max-w-sm">
              <CardHeader>
                <CardTitle>Card title</CardTitle>
                <CardDescription>
                  같은 카드 UI 를 각 프레임워크로 구현해 스타일링 방식을
                  비교합니다.
                </CardDescription>
              </CardHeader>
              <CardFooter>
                <Button variant="ghost" size="sm">
                  Share
                </Button>
                <Button variant="ghost" size="sm">
                  Learn more
                </Button>
              </CardFooter>
            </Card>
          </section>

          <hr />

          {/* Form */}
          <section>
            <h2 className="mb-3 text-base font-semibold">Form</h2>
            <form
              className="flex max-w-sm flex-col gap-4"
              onSubmit={(e) => {
                e.preventDefault();
                setSubmitted(JSON.stringify({ name, role, agree }, null, 2));
              }}
            >
              <div className="flex flex-col gap-1.5">
                <Label htmlFor="name">Name</Label>
                <Input
                  id="name"
                  value={name}
                  onChange={(e) => setName(e.target.value)}
                />
              </div>

              <div className="flex flex-col gap-1.5">
                <Label htmlFor="role">Role</Label>
                {/* shadcn Select 는 Radix 기반으로 장황 → 데모에선 input 스타일의 native select 사용 */}
                <select
                  id="role"
                  value={role}
                  onChange={(e) => setRole(e.target.value)}
                  className={cn(
                    "flex h-9 w-full rounded-md border border-input bg-transparent px-3 py-1 text-sm shadow-sm focus-visible:outline-none focus-visible:ring-1 focus-visible:ring-ring",
                  )}
                >
                  {ROLES.map((r) => (
                    <option key={r} value={r}>
                      {r}
                    </option>
                  ))}
                </select>
              </div>

              <div className="flex items-center gap-2">
                <Checkbox
                  id="agree"
                  checked={agree}
                  onCheckedChange={(v) => setAgree(v === true)}
                />
                <Label htmlFor="agree">I agree to the terms</Label>
              </div>

              <Button type="submit" disabled={!agree}>
                Submit
              </Button>
            </form>

            {submitted && (
              <pre className="mt-4 max-w-sm overflow-auto rounded-md bg-muted p-4 text-[13px]">
                {submitted}
              </pre>
            )}
          </section>
        </main>
      </div>
    </div>
  );
}
