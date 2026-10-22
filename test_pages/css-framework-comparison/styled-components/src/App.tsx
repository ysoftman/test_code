import { useEffect, useState } from "react";
import styled, {
  ThemeProvider,
  createGlobalStyle,
  type DefaultTheme,
} from "styled-components";
import scPkg from "styled-components/package.json";
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

const light: DefaultTheme = {
  colors: {
    bg: "#ffffff",
    fg: "#111827",
    muted: "#6b7280",
    border: "#e5e7eb",
    card: "#ffffff",
    surface: "#f3f4f6",
    primary: "#2563eb",
    primaryHover: "#1d4ed8",
  },
};

const dark: DefaultTheme = {
  colors: {
    bg: "#0a0a0a",
    fg: "#f3f4f6",
    muted: "#9ca3af",
    border: "#1f2937",
    card: "#111827",
    surface: "#1f2937",
    primary: "#3b82f6",
    primaryHover: "#2563eb",
  },
};

const GlobalStyle = createGlobalStyle`
  * { box-sizing: border-box; }
  body {
    margin: 0;
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
    background: ${(p) => p.theme.colors.bg};
    color: ${(p) => p.theme.colors.fg};
  }
`;

const Header = styled.header`
  display: flex;
  align-items: center;
  gap: 12px;
  padding: 12px 24px;
  border-bottom: 1px solid ${(p) => p.theme.colors.border};
`;

const Title = styled.h1`
  font-size: 1.125rem;
  font-weight: 600;
  margin: 0;
`;

const Subtle = styled.span`
  font-size: 0.875rem;
  color: ${(p) => p.theme.colors.muted};
`;

const Main = styled.main`
  max-width: 48rem;
  margin: 0 auto;
  display: flex;
  flex-direction: column;
  gap: 32px;
  padding: 32px 24px;
`;

const SectionTitle = styled.h2`
  font-size: 1rem;
  font-weight: 600;
  margin: 0 0 12px;
`;

const Row = styled.div`
  display: flex;
  flex-wrap: wrap;
  gap: 12px;
`;

const Button = styled.button<{ $variant?: "contained" | "outlined" | "text" }>`
  display: inline-flex;
  align-items: center;
  gap: 8px;
  border-radius: 6px;
  padding: 8px 16px;
  font-size: 0.875rem;
  font-weight: 500;
  cursor: pointer;
  transition:
    background 0.15s,
    opacity 0.15s;
  border: 1px solid
    ${(p) =>
      p.$variant === "outlined" ? p.theme.colors.primary : "transparent"};
  background: ${(p) =>
    p.$variant === "contained" ? p.theme.colors.primary : "transparent"};
  color: ${(p) =>
    p.$variant === "contained" ? "#ffffff" : p.theme.colors.primary};

  &:hover {
    background: ${(p) =>
      p.$variant === "contained"
        ? p.theme.colors.primaryHover
        : "rgba(37, 99, 235, 0.08)"};
  }
  &:disabled {
    opacity: 0.5;
    cursor: not-allowed;
  }
`;

const Card = styled.div`
  max-width: 24rem;
  border-radius: 12px;
  border: 1px solid ${(p) => p.theme.colors.border};
  background: ${(p) => p.theme.colors.card};
  box-shadow: 0 1px 2px rgba(0, 0, 0, 0.06);
`;

const CardBody = styled.div`
  padding: 20px;
`;

const CardActions = styled.div`
  display: flex;
  gap: 8px;
  padding: 8px 12px;
  border-top: 1px solid ${(p) => p.theme.colors.border};
`;

const Form = styled.form`
  display: flex;
  flex-direction: column;
  gap: 16px;
  max-width: 24rem;
`;

const Label = styled.label`
  display: flex;
  flex-direction: column;
  gap: 4px;
  font-size: 0.875rem;
`;

const controlStyles = `
  border-radius: 6px;
  padding: 8px 12px;
  font-size: 0.875rem;
  background: transparent;
  outline: none;
`;

const Input = styled.input`
  ${controlStyles}
  border: 1px solid ${(p) => p.theme.colors.border};
  color: ${(p) => p.theme.colors.fg};
  &:focus {
    border-color: ${(p) => p.theme.colors.primary};
    box-shadow: 0 0 0 1px ${(p) => p.theme.colors.primary};
  }
`;

const Select = styled.select`
  ${controlStyles}
  border: 1px solid ${(p) => p.theme.colors.border};
  color: ${(p) => p.theme.colors.fg};
`;

const CheckRow = styled.label`
  display: flex;
  align-items: center;
  gap: 8px;
  font-size: 0.875rem;
`;

const Pre = styled.pre`
  margin-top: 16px;
  max-width: 24rem;
  overflow: auto;
  border-radius: 6px;
  background: ${(p) => p.theme.colors.surface};
  padding: 16px;
  font-size: 13px;
`;

const ToggleBtn = styled.button`
  margin-left: auto;
  border-radius: 6px;
  border: 1px solid ${(p) => p.theme.colors.border};
  background: ${(p) => p.theme.colors.surface};
  color: ${(p) => p.theme.colors.fg};
  padding: 6px 12px;
  font-size: 0.875rem;
  cursor: pointer;
`;

const Divider = styled.hr`
  border: none;
  border-top: 1px solid ${(p) => p.theme.colors.border};
  margin: 0;
`;

// 렌더 테스트 아이템: 동적 $hue 마다 새 클래스가 런타임 생성됨 (CSS-in-JS 비용)
const StressItem = styled.div<{ $hue: number }>`
  border: 1px solid ${(p) => p.theme.colors.border};
  border-top: 3px solid ${(p) => `hsl(${p.$hue} 70% 50%)`};
  background: ${(p) => p.theme.colors.card};
  color: ${(p) => p.theme.colors.fg};
  border-radius: 6px;
  padding: 8px;
  font-size: 12px;
`;

const StressGo = styled.button<{ $hue: number }>`
  margin-top: 4px;
  display: inline-flex;
  align-items: center;
  height: 26px;
  padding: 0 10px;
  border: none;
  border-radius: 4px;
  font-size: 12px;
  font-weight: 600;
  line-height: 1;
  color: #fff;
  cursor: pointer;
  background: ${(p) => `hsl(${p.$hue} 65% 45%)`};
`;

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

  const renderStressItem = (i: number, tick: number) => {
    const hue = (i * 37 + tick * 90) % 360;
    return (
      <StressItem $hue={hue}>
        <div>Item {i}</div>
        <StressGo $hue={hue}>Go</StressGo>
      </StressItem>
    );
  };

  return (
    <ThemeProvider theme={isDark ? dark : light}>
      <GlobalStyle />
      <StressTest name="styled-components" renderItem={renderStressItem} />
      <Header>
        <Title>styled-components</Title>
        <Subtle>
          styled-components v{scPkg.version} · CSS-in-JS (runtime)
        </Subtle>
        <ToggleBtn
          type="button"
          onClick={() => setIsDark((d) => !d)}
          aria-label="toggle dark mode"
        >
          <ThemeIcon dark={isDark} />
        </ToggleBtn>
      </Header>

      <Main>
        {/* Buttons */}
        <section>
          <SectionTitle>Buttons</SectionTitle>
          <Row>
            <Button $variant="contained">Contained</Button>
            <Button $variant="outlined">Outlined</Button>
            <Button $variant="text">Text</Button>
            <Button $variant="contained">
              <HeartIcon /> With Icon
            </Button>
            <Button $variant="contained" disabled>
              Disabled
            </Button>
          </Row>
        </section>

        <Divider />

        {/* Card */}
        <section>
          <SectionTitle>Card</SectionTitle>
          <Card>
            <CardBody>
              <h3 style={{ margin: "0 0 4px", fontSize: "1rem" }}>
                Card title
              </h3>
              <Subtle>
                같은 카드 UI 를 각 프레임워크로 구현해 스타일링 방식을
                비교합니다.
              </Subtle>
            </CardBody>
            <CardActions>
              <Button $variant="text">Share</Button>
              <Button $variant="text">Learn more</Button>
            </CardActions>
          </Card>
        </section>

        <Divider />

        {/* Form */}
        <section>
          <SectionTitle>Form</SectionTitle>
          <Form
            onSubmit={(e) => {
              e.preventDefault();
              setSubmitted(JSON.stringify({ name, role, agree }, null, 2));
            }}
          >
            <Label>
              <span>Name</span>
              <Input value={name} onChange={(e) => setName(e.target.value)} />
            </Label>
            <Label>
              <span>Role</span>
              <Select value={role} onChange={(e) => setRole(e.target.value)}>
                {ROLES.map((r) => (
                  <option key={r} value={r}>
                    {r}
                  </option>
                ))}
              </Select>
            </Label>
            <CheckRow>
              <input
                type="checkbox"
                checked={agree}
                onChange={(e) => setAgree(e.target.checked)}
              />
              <span>I agree to the terms</span>
            </CheckRow>
            <Button type="submit" $variant="contained" disabled={!agree}>
              Submit
            </Button>
          </Form>

          {submitted && <Pre>{submitted}</Pre>}
        </section>
      </Main>
    </ThemeProvider>
  );
}
