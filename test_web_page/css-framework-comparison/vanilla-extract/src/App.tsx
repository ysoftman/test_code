import { useEffect, useState } from "react";
import * as s from "./styles.css";
import vePkg from "@vanilla-extract/css/package.json";

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
  const [isDark, setIsDark] = useState(false);

  const [name, setName] = useState("");
  const [role, setRole] = useState(ROLES[0]);
  const [agree, setAgree] = useState(false);
  const [submitted, setSubmitted] = useState<string | null>(null);

  // 부모(비교 페이지)에서 일괄 테마 적용 메시지를 받는다.
  useEffect(() => {
    const onMsg = (e: MessageEvent) => {
      if (e.data?.type === "setTheme") setIsDark(!!e.data.dark);
    };
    window.addEventListener("message", onMsg);
    return () => window.removeEventListener("message", onMsg);
  }, []);

  return (
    <div className={`${isDark ? s.darkClass : s.lightClass} ${s.root}`}>
      <header className={s.header}>
        <h1 className={s.title}>vanilla-extract</h1>
        <span className={s.subtle}>
          vanilla-extract v{vePkg.version} · CSS-in-JS · build-time (zero
          runtime)
        </span>
        <button
          type="button"
          onClick={() => setIsDark((d) => !d)}
          aria-label="toggle dark mode"
          className={s.toggleBtn}
        >
          <ThemeIcon dark={isDark} />
        </button>
      </header>

      <main className={s.main}>
        {/* Buttons */}
        <section>
          <h2 className={s.sectionTitle}>Buttons</h2>
          <div className={s.row}>
            <button className={s.button.contained}>Contained</button>
            <button className={s.button.outlined}>Outlined</button>
            <button className={s.button.text}>Text</button>
            <button className={s.button.contained}>
              <HeartIcon /> With Icon
            </button>
            <button className={s.button.contained} disabled>
              Disabled
            </button>
          </div>
        </section>

        <hr className={s.divider} />

        {/* Card */}
        <section>
          <h2 className={s.sectionTitle}>Card</h2>
          <div className={s.card}>
            <div className={s.cardBody}>
              <h3 style={{ margin: "0 0 4px", fontSize: "1rem" }}>
                Card title
              </h3>
              <span className={s.subtle}>
                같은 카드 UI 를 각 프레임워크로 구현해 스타일링 방식을
                비교합니다.
              </span>
            </div>
            <div className={s.cardActions}>
              <button className={s.button.text}>Share</button>
              <button className={s.button.text}>Learn more</button>
            </div>
          </div>
        </section>

        <hr className={s.divider} />

        {/* Form */}
        <section>
          <h2 className={s.sectionTitle}>Form</h2>
          <form
            className={s.form}
            onSubmit={(e) => {
              e.preventDefault();
              setSubmitted(JSON.stringify({ name, role, agree }, null, 2));
            }}
          >
            <label className={s.label}>
              <span>Name</span>
              <input
                className={s.control}
                value={name}
                onChange={(e) => setName(e.target.value)}
              />
            </label>
            <label className={s.label}>
              <span>Role</span>
              <select
                className={s.control}
                value={role}
                onChange={(e) => setRole(e.target.value)}
              >
                {ROLES.map((r) => (
                  <option key={r} value={r}>
                    {r}
                  </option>
                ))}
              </select>
            </label>
            <label className={s.checkRow}>
              <input
                type="checkbox"
                checked={agree}
                onChange={(e) => setAgree(e.target.checked)}
              />
              <span>I agree to the terms</span>
            </label>
            <button
              type="submit"
              className={s.button.contained}
              disabled={!agree}
            >
              Submit
            </button>
          </form>

          {submitted && <pre className={s.pre}>{submitted}</pre>}
        </section>
      </main>
    </div>
  );
}
