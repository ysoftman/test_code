import { useState } from "react";
import styled, {
  ThemeProvider,
  createGlobalStyle,
  type DefaultTheme,
} from "styled-components";

// 모든 프레임워크가 공유하는 데모 사양:
// 1) 다크모드 토글  2) 버튼 변형  3) 카드  4) 폼(입력 -> 제출 결과 표시)

const ROLES = ["Frontend", "Backend", "Designer", "PM"];

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

export default function App() {
  const [isDark, setIsDark] = useState(true);

  const [name, setName] = useState("");
  const [role, setRole] = useState(ROLES[0]);
  const [agree, setAgree] = useState(false);
  const [submitted, setSubmitted] = useState<string | null>(null);

  return (
    <ThemeProvider theme={isDark ? dark : light}>
      <GlobalStyle />
      <Header>
        <Title>styled-components</Title>
        <Subtle>CSS-in-JS · runtime</Subtle>
        <ToggleBtn
          type="button"
          onClick={() => setIsDark((d) => !d)}
          aria-label="toggle dark mode"
        >
          {isDark ? "☀️ Light" : "🌙 Dark"}
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
              <span>❤</span> With Icon
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
