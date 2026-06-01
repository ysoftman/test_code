import { useState } from "react";
import * as s from "./styles.css";

// 모든 프레임워크가 공유하는 데모 사양:
// 1) 다크모드 토글  2) 버튼 변형  3) 카드  4) 폼(입력 -> 제출 결과 표시)

const ROLES = ["Frontend", "Backend", "Designer", "PM"];

export default function App() {
  const [isDark, setIsDark] = useState(true);

  const [name, setName] = useState("");
  const [role, setRole] = useState(ROLES[0]);
  const [agree, setAgree] = useState(false);
  const [submitted, setSubmitted] = useState<string | null>(null);

  return (
    <div className={`${isDark ? s.darkClass : s.lightClass} ${s.root}`}>
      <header className={s.header}>
        <h1 className={s.title}>vanilla-extract</h1>
        <span className={s.subtle}>빌드 타임 CSS-in-JS · zero runtime</span>
        <button
          type="button"
          onClick={() => setIsDark((d) => !d)}
          aria-label="toggle dark mode"
          className={s.toggleBtn}
        >
          {isDark ? "☀️ Light" : "🌙 Dark"}
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
              <span>❤</span> With Icon
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
