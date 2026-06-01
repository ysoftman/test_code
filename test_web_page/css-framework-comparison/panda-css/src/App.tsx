import { useEffect, useState, type CSSProperties } from "react";
import { css, cx } from "../styled-system/css";
import pandaPkg from "@pandacss/dev/package.json";
import { StressTest } from "./StressTest";

// 모든 프레임워크가 공유하는 데모 사양:
// 1) 다크모드 토글  2) 버튼 변형  3) 카드  4) 폼(입력 -> 제출 결과 표시)
//
// Panda 는 빌드 타임 정적 추출이라 css() 인자는 모두 정적 리터럴이어야 한다.
// 다크모드는 추출과 충돌하지 않도록 CSS 변수를 inline style 로 교체하는 방식.

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

const lightVars = {
  "--bg": "#ffffff",
  "--fg": "#111827",
  "--muted": "#6b7280",
  "--border": "#e5e7eb",
  "--card": "#ffffff",
  "--surface": "#f3f4f6",
} as CSSProperties;

const darkVars = {
  "--bg": "#0a0a0a",
  "--fg": "#f3f4f6",
  "--muted": "#9ca3af",
  "--border": "#1f2937",
  "--card": "#111827",
  "--surface": "#1f2937",
} as CSSProperties;

const btnBase = css({
  display: "inline-flex",
  alignItems: "center",
  gap: "2",
  rounded: "md",
  px: "4",
  py: "2",
  fontSize: "sm",
  fontWeight: "medium",
  cursor: "pointer",
  transition: "background 0.15s, opacity 0.15s",
  _disabled: { opacity: 0.5, cursor: "not-allowed" },
});
const btnContained = css({
  background: "#2563eb",
  color: "white",
  border: "1px solid transparent",
  _hover: { background: "#1d4ed8" },
});
const btnOutlined = css({
  background: "transparent",
  color: "#2563eb",
  border: "1px solid #2563eb",
  _hover: { background: "rgba(37,99,235,0.08)" },
});
const btnText = css({
  background: "transparent",
  color: "#2563eb",
  border: "1px solid transparent",
  _hover: { background: "rgba(37,99,235,0.08)" },
});

const field = css({
  rounded: "md",
  border: "1px solid var(--border)",
  background: "transparent",
  color: "var(--fg)",
  px: "3",
  py: "2",
  fontSize: "sm",
  outline: "none",
  _focus: { borderColor: "#2563eb", boxShadow: "0 0 0 1px #2563eb" },
});

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

  // 렌더 테스트 아이템: 구조는 빌드타임 css(), 동적 색은 inline style (zero runtime)
  const renderStressItem = (i: number, tick: number) => {
    const hue = (i * 37 + tick * 90) % 360;
    return (
      <div
        className={css({
          rounded: "md",
          border: "1px solid var(--border)",
          background: "var(--card)",
          color: "var(--fg)",
          p: "2",
          fontSize: "xs",
        })}
        style={{ borderTop: `3px solid hsl(${hue} 70% 50%)` }}
      >
        <div>Item {i}</div>
        <button
          className={css({
            mt: "1",
            display: "inline-flex",
            alignItems: "center",
            height: "26px",
            rounded: "sm",
            px: "2.5",
            fontSize: "12px",
            fontWeight: "semibold",
            lineHeight: "1",
            color: "white",
            cursor: "pointer",
          })}
          style={{ background: `hsl(${hue} 65% 45%)` }}
        >
          Go
        </button>
      </div>
    );
  };

  return (
    <div
      style={dark ? darkVars : lightVars}
      className={css({
        minH: "100vh",
        background: "var(--bg)",
        color: "var(--fg)",
      })}
    >
      <StressTest name="Panda CSS" renderItem={renderStressItem} />
      {/* Header */}
      <header
        className={css({
          display: "flex",
          alignItems: "center",
          gap: "3",
          px: "6",
          py: "3",
          borderBottom: "1px solid var(--border)",
        })}
      >
        <h1 className={css({ fontSize: "lg", fontWeight: "semibold" })}>
          Panda CSS
        </h1>
        <span className={css({ fontSize: "sm", color: "var(--muted)" })}>
          Panda CSS v{pandaPkg.version} · CSS-in-JS · build-time (zero runtime)
        </span>
        <button
          type="button"
          onClick={() => setDark((d) => !d)}
          aria-label="toggle dark mode"
          className={css({
            ml: "auto",
            rounded: "md",
            border: "1px solid var(--border)",
            background: "var(--surface)",
            color: "var(--fg)",
            px: "3",
            py: "1.5",
            fontSize: "sm",
            cursor: "pointer",
          })}
        >
          <ThemeIcon dark={dark} />
        </button>
      </header>

      <main
        className={css({
          maxW: "3xl",
          mx: "auto",
          display: "flex",
          flexDirection: "column",
          gap: "8",
          px: "6",
          py: "8",
        })}
      >
        {/* Buttons */}
        <section>
          <h2
            className={css({
              fontSize: "md",
              fontWeight: "semibold",
              mb: "3",
            })}
          >
            Buttons
          </h2>
          <div className={css({ display: "flex", flexWrap: "wrap", gap: "3" })}>
            <button className={cx(btnBase, btnContained)}>Contained</button>
            <button className={cx(btnBase, btnOutlined)}>Outlined</button>
            <button className={cx(btnBase, btnText)}>Text</button>
            <button className={cx(btnBase, btnContained)}>
              <HeartIcon /> With Icon
            </button>
            <button className={cx(btnBase, btnContained)} disabled>
              Disabled
            </button>
          </div>
        </section>

        <hr className={css({ borderColor: "var(--border)" })} />

        {/* Card */}
        <section>
          <h2
            className={css({
              fontSize: "md",
              fontWeight: "semibold",
              mb: "3",
            })}
          >
            Card
          </h2>
          <div
            className={css({
              maxW: "sm",
              rounded: "xl",
              border: "1px solid var(--border)",
              background: "var(--card)",
              boxShadow: "sm",
            })}
          >
            <div className={css({ p: "5" })}>
              <h3
                className={css({
                  fontSize: "md",
                  fontWeight: "semibold",
                  mb: "1",
                })}
              >
                Card title
              </h3>
              <p className={css({ fontSize: "sm", color: "var(--muted)" })}>
                같은 카드 UI 를 각 프레임워크로 구현해 스타일링 방식을
                비교합니다.
              </p>
            </div>
            <div
              className={css({
                display: "flex",
                gap: "2",
                px: "3",
                py: "2",
                borderTop: "1px solid var(--border)",
              })}
            >
              <button className={cx(btnBase, btnText)}>Share</button>
              <button className={cx(btnBase, btnText)}>Learn more</button>
            </div>
          </div>
        </section>

        <hr className={css({ borderColor: "var(--border)" })} />

        {/* Form */}
        <section>
          <h2
            className={css({
              fontSize: "md",
              fontWeight: "semibold",
              mb: "3",
            })}
          >
            Form
          </h2>
          <form
            className={css({
              display: "flex",
              flexDirection: "column",
              gap: "4",
              maxW: "sm",
            })}
            onSubmit={(e) => {
              e.preventDefault();
              setSubmitted(JSON.stringify({ name, role, agree }, null, 2));
            }}
          >
            <label
              className={css({
                display: "flex",
                flexDirection: "column",
                gap: "1",
                fontSize: "sm",
              })}
            >
              <span>Name</span>
              <input
                type="text"
                value={name}
                onChange={(e) => setName(e.target.value)}
                className={field}
              />
            </label>

            <label
              className={css({
                display: "flex",
                flexDirection: "column",
                gap: "1",
                fontSize: "sm",
              })}
            >
              <span>Role</span>
              <select
                value={role}
                onChange={(e) => setRole(e.target.value)}
                className={field}
              >
                {ROLES.map((r) => (
                  <option key={r} value={r}>
                    {r}
                  </option>
                ))}
              </select>
            </label>

            <label
              className={css({
                display: "flex",
                alignItems: "center",
                gap: "2",
                fontSize: "sm",
              })}
            >
              <input
                type="checkbox"
                checked={agree}
                onChange={(e) => setAgree(e.target.checked)}
                className={css({ width: "4", height: "4" })}
              />
              <span>I agree to the terms</span>
            </label>

            <button
              type="submit"
              className={cx(btnBase, btnContained)}
              disabled={!agree}
            >
              Submit
            </button>
          </form>

          {submitted && (
            <pre
              className={css({
                mt: "4",
                maxW: "sm",
                overflow: "auto",
                rounded: "md",
                background: "var(--surface)",
                p: "4",
                fontSize: "13px",
              })}
            >
              {submitted}
            </pre>
          )}
        </section>
      </main>
    </div>
  );
}
