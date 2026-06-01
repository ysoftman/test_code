import { useState } from "react";

// 모든 프레임워크가 공유하는 데모 사양:
// 1) 다크모드 토글  2) 버튼 변형  3) 카드  4) 폼(입력 -> 제출 결과 표시)

const ROLES = ["Frontend", "Backend", "Designer", "PM"];

const btnBase =
  "inline-flex items-center gap-2 rounded-md px-4 py-2 text-sm font-medium transition disabled:cursor-not-allowed disabled:opacity-50";
const btnContained =
  btnBase +
  " bg-blue-600 text-white hover:bg-blue-700 disabled:hover:bg-blue-600";
const btnOutlined =
  btnBase +
  " border border-blue-600 text-blue-600 hover:bg-blue-50 dark:hover:bg-blue-950";
const btnText =
  btnBase + " text-blue-600 hover:bg-blue-50 dark:hover:bg-blue-950";

export default function App() {
  const [dark, setDark] = useState(true);

  const [name, setName] = useState("");
  const [role, setRole] = useState(ROLES[0]);
  const [agree, setAgree] = useState(false);
  const [submitted, setSubmitted] = useState<string | null>(null);

  return (
    <div className={dark ? "dark" : ""}>
      <div className="min-h-screen bg-white text-gray-900 dark:bg-gray-950 dark:text-gray-100">
        {/* Header */}
        <header className="flex items-center gap-3 border-b border-gray-200 px-6 py-3 dark:border-gray-800">
          <h1 className="text-lg font-semibold">Tailwind CSS</h1>
          <span className="text-sm text-gray-500 dark:text-gray-400">
            유틸리티 우선 · zero runtime
          </span>
          <button
            type="button"
            onClick={() => setDark((d) => !d)}
            aria-label="toggle dark mode"
            className="ml-auto rounded-md border border-gray-300 px-3 py-1.5 text-sm hover:bg-gray-100 dark:border-gray-700 dark:hover:bg-gray-800"
          >
            {dark ? "☀️ Light" : "🌙 Dark"}
          </button>
        </header>

        <main className="mx-auto flex max-w-3xl flex-col gap-8 px-6 py-8">
          {/* Buttons */}
          <section>
            <h2 className="mb-3 text-base font-semibold">Buttons</h2>
            <div className="flex flex-wrap gap-3">
              <button className={btnContained}>Contained</button>
              <button className={btnOutlined}>Outlined</button>
              <button className={btnText}>Text</button>
              <button className={btnContained}>
                <span>❤</span> With Icon
              </button>
              <button className={btnContained} disabled>
                Disabled
              </button>
            </div>
          </section>

          <hr className="border-gray-200 dark:border-gray-800" />

          {/* Card */}
          <section>
            <h2 className="mb-3 text-base font-semibold">Card</h2>
            <div className="max-w-sm rounded-xl border border-gray-200 bg-white shadow-sm dark:border-gray-800 dark:bg-gray-900">
              <div className="p-5">
                <h3 className="mb-1 text-base font-semibold">Card title</h3>
                <p className="text-sm text-gray-500 dark:text-gray-400">
                  같은 카드 UI 를 각 프레임워크로 구현해 스타일링 방식을
                  비교합니다.
                </p>
              </div>
              <div className="flex gap-2 border-t border-gray-100 px-3 py-2 dark:border-gray-800">
                <button className={btnText}>Share</button>
                <button className={btnText}>Learn more</button>
              </div>
            </div>
          </section>

          <hr className="border-gray-200 dark:border-gray-800" />

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
              <label className="flex flex-col gap-1 text-sm">
                <span>Name</span>
                <input
                  type="text"
                  value={name}
                  onChange={(e) => setName(e.target.value)}
                  className="rounded-md border border-gray-300 bg-transparent px-3 py-2 outline-none focus:border-blue-600 focus:ring-1 focus:ring-blue-600 dark:border-gray-700"
                />
              </label>

              <label className="flex flex-col gap-1 text-sm">
                <span>Role</span>
                <select
                  value={role}
                  onChange={(e) => setRole(e.target.value)}
                  className="rounded-md border border-gray-300 bg-transparent px-3 py-2 outline-none focus:border-blue-600 focus:ring-1 focus:ring-blue-600 dark:border-gray-700 dark:bg-gray-900"
                >
                  {ROLES.map((r) => (
                    <option key={r} value={r}>
                      {r}
                    </option>
                  ))}
                </select>
              </label>

              <label className="flex items-center gap-2 text-sm">
                <input
                  type="checkbox"
                  checked={agree}
                  onChange={(e) => setAgree(e.target.checked)}
                  className="h-4 w-4 accent-blue-600"
                />
                <span>I agree to the terms</span>
              </label>

              <button type="submit" className={btnContained} disabled={!agree}>
                Submit
              </button>
            </form>

            {submitted && (
              <pre className="mt-4 max-w-sm overflow-auto rounded-md bg-gray-100 p-4 text-[13px] dark:bg-gray-800">
                {submitted}
              </pre>
            )}
          </section>
        </main>
      </div>
    </div>
  );
}
