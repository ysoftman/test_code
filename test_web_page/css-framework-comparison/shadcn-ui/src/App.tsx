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
import twPkg from "tailwindcss/package.json";
import { StressTest } from "./StressTest";

// 모든 프레임워크가 공유하는 데모 사양:
// 1) 다크모드 토글  2) 버튼 변형  3) 카드  4) 폼(입력 -> 제출 결과 표시)

const ROLES = ["Frontend", "Backend", "Designer", "PM"];

// 모든 프레임워크 공통 테마 토글 아이콘 (라이브러리 없이 인라인 SVG, Material 아이콘 path)
const MOON_PATH =
  "M12 3c-4.97 0-9 4.03-9 9s4.03 9 9 9 9-4.03 9-9c0-.46-.04-.92-.1-1.36-.98 1.37-2.58 2.26-4.4 2.26-2.98 0-5.4-2.42-5.4-5.4 0-1.81.89-3.42 2.26-4.4-.44-.06-.9-.1-1.36-.1z";
const SUN_PATH =
  "M12 7c-2.76 0-5 2.24-5 5s2.24 5 5 5 5-2.24 5-5-2.24-5-5-5zM2 13h2c.55 0 1-.45 1-1s-.45-1-1-1H2c-.55 0-1 .45-1 1s.45 1 1 1zm18 0h2c.55 0 1-.45 1-1s-.45-1-1-1h-2c-.55 0-1 .45-1 1s.45 1 1 1zM11 2v2c0 .55.45 1 1 1s1-.45 1-1V2c0-.55-.45-1-1-1s-1 .45-1 1zm0 18v2c0 .55.45 1 1 1s1-.45 1-1v-2c0-.55-.45-1-1-1s-1 .45-1 1zM5.99 4.58c-.39-.39-1.03-.39-1.41 0-.39.39-.39 1.03 0 1.41l1.06 1.06c.39.39 1.03.39 1.41 0s.39-1.03 0-1.41L5.99 4.58zm12.37 12.37c-.39-.39-1.03-.39-1.41 0-.39.39-.39 1.03 0 1.41l1.06 1.06c.39.39 1.03.39 1.41 0 .39-.39.39-1.03 0-1.41l-1.06-1.06zm1.06-10.96c.39-.39.39-1.03 0-1.41-.39-.39-1.03-.39-1.41 0l-1.06 1.06c-.39.39-.39 1.03 0 1.41s1.03.39 1.41 0l1.06-1.06zM7.05 18.36c.39-.39.39-1.03 0-1.41-.39-.39-1.03-.39-1.41 0l-1.06 1.06c-.39.39-.39 1.03 0 1.41s1.03.39 1.41 0l1.06-1.06z";

function ThemeIcon({ dark }: { dark: boolean }) {
  return (
    <svg
      width="18"
      height="18"
      viewBox="0 0 24 24"
      fill="currentColor"
      aria-hidden="true"
      style={{ display: "block" }}
    >
      <path d={dark ? SUN_PATH : MOON_PATH} />
    </svg>
  );
}

const HEART_PATH =
  "M12 21.35l-1.45-1.32C5.4 15.36 2 12.28 2 8.5 2 5.42 4.42 3 7.5 3c1.74 0 3.41.81 4.5 2.09C13.09 3.81 14.76 3 16.5 3 19.58 3 22 5.42 22 8.5c0 3.78-3.4 6.86-8.55 11.54L12 21.35z";

function HeartIcon() {
  return (
    <svg
      width="16"
      height="16"
      viewBox="0 0 24 24"
      fill="currentColor"
      aria-hidden="true"
      style={{ display: "block" }}
    >
      <path d={HEART_PATH} />
    </svg>
  );
}

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

  // 렌더 테스트 아이템: shadcn Button(CVA) + 유틸리티 클래스, 동적 색은 inline style
  const renderStressItem = (i: number, tick: number) => {
    const hue = (i * 37 + tick * 90) % 360;
    return (
      <div
        className="rounded-md border bg-card p-2 text-xs text-card-foreground"
        style={{ borderTop: `3px solid hsl(${hue} 70% 50%)` }}
      >
        <div>Item {i}</div>
        <Button
          className="mt-1 inline-flex h-[26px] items-center rounded px-2.5 py-0 text-xs font-semibold leading-none text-white"
          style={{ background: `hsl(${hue} 65% 45%)` }}
        >
          Go
        </Button>
      </div>
    );
  };

  return (
    <div className={dark ? "dark" : ""}>
      <StressTest name="shadcn/ui" renderItem={renderStressItem} />
      <div className="min-h-screen bg-background text-foreground">
        {/* Header */}
        <header className="flex items-center gap-3 border-b px-6 py-3">
          <h1 className="text-lg font-semibold">shadcn/ui</h1>
          <span className="text-sm text-muted-foreground">
            shadcn/ui · 유틸리티 CSS · Tailwind v{twPkg.version} + Radix
          </span>
          <Button
            variant="outline"
            size="sm"
            className="ml-auto"
            onClick={() => setDark((d) => !d)}
            aria-label="toggle dark mode"
          >
            <ThemeIcon dark={dark} />
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
              <Button>
                <HeartIcon /> With Icon
              </Button>
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
