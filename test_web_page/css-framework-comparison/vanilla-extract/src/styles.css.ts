import {
  createTheme,
  style,
  styleVariants,
  globalStyle,
} from "@vanilla-extract/css";

// 라이트 테마가 contract(vars) 를 정의하고, 다크 테마는 같은 vars 에 값만 교체.
export const [lightClass, vars] = createTheme({
  color: {
    bg: "#ffffff",
    fg: "#111827",
    muted: "#6b7280",
    border: "#e5e7eb",
    card: "#ffffff",
    surface: "#f3f4f6",
    primary: "#2563eb",
    primaryHover: "#1d4ed8",
  },
});

export const darkClass = createTheme(vars, {
  color: {
    bg: "#0a0a0a",
    fg: "#f3f4f6",
    muted: "#9ca3af",
    border: "#1f2937",
    card: "#111827",
    surface: "#1f2937",
    primary: "#3b82f6",
    primaryHover: "#2563eb",
  },
});

globalStyle("*", { boxSizing: "border-box" });
globalStyle("body", {
  margin: 0,
  fontFamily:
    '-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif',
});

export const root = style({
  minHeight: "100vh",
  background: vars.color.bg,
  color: vars.color.fg,
});

export const header = style({
  display: "flex",
  alignItems: "center",
  gap: 12,
  padding: "12px 24px",
  borderBottom: `1px solid ${vars.color.border}`,
});

export const title = style({
  fontSize: "1.125rem",
  fontWeight: 600,
  margin: 0,
});
export const subtle = style({ fontSize: "0.875rem", color: vars.color.muted });

export const main = style({
  maxWidth: "48rem",
  margin: "0 auto",
  display: "flex",
  flexDirection: "column",
  gap: 32,
  padding: "32px 24px",
});

export const sectionTitle = style({
  fontSize: "1rem",
  fontWeight: 600,
  margin: "0 0 12px",
});

export const row = style({ display: "flex", flexWrap: "wrap", gap: 12 });

const btnBase = style({
  display: "inline-flex",
  alignItems: "center",
  gap: 8,
  borderRadius: 6,
  padding: "8px 16px",
  fontSize: "0.875rem",
  fontWeight: 500,
  cursor: "pointer",
  border: "1px solid transparent",
  transition: "background 0.15s, opacity 0.15s",
  selectors: {
    "&:disabled": { opacity: 0.5, cursor: "not-allowed" },
  },
});

export const button = styleVariants({
  contained: [
    btnBase,
    {
      background: vars.color.primary,
      color: "#ffffff",
      selectors: { "&:hover": { background: vars.color.primaryHover } },
    },
  ],
  outlined: [
    btnBase,
    {
      background: "transparent",
      color: vars.color.primary,
      borderColor: vars.color.primary,
      selectors: { "&:hover": { background: "rgba(37, 99, 235, 0.08)" } },
    },
  ],
  text: [
    btnBase,
    {
      background: "transparent",
      color: vars.color.primary,
      selectors: { "&:hover": { background: "rgba(37, 99, 235, 0.08)" } },
    },
  ],
});

export const card = style({
  maxWidth: "24rem",
  borderRadius: 12,
  border: `1px solid ${vars.color.border}`,
  background: vars.color.card,
  boxShadow: "0 1px 2px rgba(0, 0, 0, 0.06)",
});
export const cardBody = style({ padding: 20 });
export const cardActions = style({
  display: "flex",
  gap: 8,
  padding: "8px 12px",
  borderTop: `1px solid ${vars.color.border}`,
});

export const form = style({
  display: "flex",
  flexDirection: "column",
  gap: 16,
  maxWidth: "24rem",
});
export const label = style({
  display: "flex",
  flexDirection: "column",
  gap: 4,
  fontSize: "0.875rem",
});
export const checkRow = style({
  display: "flex",
  alignItems: "center",
  gap: 8,
  fontSize: "0.875rem",
});

export const control = style({
  borderRadius: 6,
  padding: "8px 12px",
  fontSize: "0.875rem",
  background: "transparent",
  color: vars.color.fg,
  border: `1px solid ${vars.color.border}`,
  outline: "none",
  selectors: {
    "&:focus": {
      borderColor: vars.color.primary,
      boxShadow: `0 0 0 1px ${vars.color.primary}`,
    },
  },
});

export const toggleBtn = style({
  marginLeft: "auto",
  borderRadius: 6,
  border: `1px solid ${vars.color.border}`,
  background: vars.color.surface,
  color: vars.color.fg,
  padding: "6px 12px",
  fontSize: "0.875rem",
  cursor: "pointer",
});

export const divider = style({
  border: "none",
  borderTop: `1px solid ${vars.color.border}`,
  margin: 0,
});

export const pre = style({
  marginTop: 16,
  maxWidth: "24rem",
  overflow: "auto",
  borderRadius: 6,
  background: vars.color.surface,
  padding: 16,
  fontSize: 13,
});
