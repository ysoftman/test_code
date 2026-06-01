import { useEffect, useState, type CSSProperties } from "react";
import { css, cx } from "../styled-system/css";

// 모든 프레임워크가 공유하는 데모 사양:
// 1) 다크모드 토글  2) 버튼 변형  3) 카드  4) 폼(입력 -> 제출 결과 표시)
//
// Panda 는 빌드 타임 정적 추출이라 css() 인자는 모두 정적 리터럴이어야 한다.
// 다크모드는 추출과 충돌하지 않도록 CSS 변수를 inline style 로 교체하는 방식.

const ROLES = ["Frontend", "Backend", "Designer", "PM"];

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

  return (
    <div
      style={dark ? darkVars : lightVars}
      className={css({
        minH: "100vh",
        background: "var(--bg)",
        color: "var(--fg)",
      })}
    >
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
          빌드 타임 CSS-in-JS · zero runtime
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
          {dark ? "☀️ Light" : "🌙 Dark"}
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
              <span>❤</span> With Icon
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
