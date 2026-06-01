import { useEffect, useMemo, useState } from "react";
import {
  Box,
  Button,
  Card,
  CardActions,
  CardContent,
  Checkbox,
  Container,
  CssBaseline,
  Divider,
  FormControlLabel,
  MenuItem,
  Stack,
  TextField,
  Typography,
  createTheme,
  ThemeProvider,
} from "@mui/material";
import muiPkg from "@mui/material/package.json";

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

// 다른 프레임워크와 글자/간격을 맞추기 위한 공통 섹션 제목 스타일
const sectionTitleSx = { fontSize: "1rem", fontWeight: 600, mb: 1.5 } as const;

export default function App() {
  const [mode, setMode] = useState<"light" | "dark">("light");
  const theme = useMemo(
    () =>
      createTheme({
        palette: {
          mode,
          // 다른 프레임워크와 동일한 블루 (light #2563eb / dark #3b82f6)
          primary: { main: mode === "dark" ? "#3b82f6" : "#2563eb" },
        },
        // 다른 프레임워크와 동일한 시스템 폰트로 맞춤 (MUI 기본 Roboto 대신)
        typography: {
          fontFamily:
            '-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif',
          // 다른 프레임워크와 동일하게 버튼 대문자 변환 해제
          button: { textTransform: "none" },
        },
      }),
    [mode],
  );

  const [name, setName] = useState("");
  const [role, setRole] = useState(ROLES[0]);
  const [agree, setAgree] = useState(false);
  const [submitted, setSubmitted] = useState<string | null>(null);

  // 부모(비교 페이지)에서 일괄 테마 적용 메시지를 받는다.
  useEffect(() => {
    const onMsg = (e: MessageEvent) => {
      if (e.data?.type === "setTheme") setMode(e.data.dark ? "dark" : "light");
    };
    window.addEventListener("message", onMsg);
    return () => window.removeEventListener("message", onMsg);
  }, []);

  return (
    <ThemeProvider theme={theme}>
      <CssBaseline />
      {/* Header — 다른 프레임워크와 동일한 단순 상단바 */}
      <Box
        component="header"
        sx={{
          display: "flex",
          alignItems: "center",
          gap: 1.5,
          px: 3,
          py: 1.5,
          borderBottom: 1,
          borderColor: "divider",
        }}
      >
        <Typography sx={{ fontSize: "1.125rem", fontWeight: 600 }}>
          MUI
        </Typography>
        <Typography variant="body2" color="text.secondary">
          Material UI v{muiPkg.version} · CSS-in-JS (Emotion, runtime)
        </Typography>
        <Button
          variant="outlined"
          size="small"
          color="inherit"
          sx={{ ml: "auto", minWidth: 0, px: 1 }}
          onClick={() => setMode((m) => (m === "dark" ? "light" : "dark"))}
          aria-label="toggle dark mode"
        >
          <ThemeIcon dark={mode === "dark"} />
        </Button>
      </Box>

      <Container maxWidth={false} sx={{ maxWidth: "48rem", px: 3, py: 4 }}>
        <Stack spacing={4}>
          {/* Buttons */}
          <section>
            <Typography sx={sectionTitleSx}>Buttons</Typography>
            <Stack direction="row" spacing={1.5} flexWrap="wrap" useFlexGap>
              <Button variant="contained">Contained</Button>
              <Button variant="outlined">Outlined</Button>
              <Button variant="text">Text</Button>
              <Button variant="contained" startIcon={<HeartIcon />}>
                With Icon
              </Button>
              <Button variant="contained" disabled>
                Disabled
              </Button>
            </Stack>
          </section>

          <Divider />

          {/* Card */}
          <section>
            <Typography sx={sectionTitleSx}>Card</Typography>
            <Card sx={{ maxWidth: "24rem" }}>
              <CardContent>
                <Typography sx={{ fontSize: "1rem", fontWeight: 600, mb: 0.5 }}>
                  Card title
                </Typography>
                <Typography variant="body2" color="text.secondary">
                  같은 카드 UI 를 각 프레임워크로 구현해 스타일링 방식을
                  비교합니다.
                </Typography>
              </CardContent>
              <CardActions>
                <Button size="small">Share</Button>
                <Button size="small">Learn more</Button>
              </CardActions>
            </Card>
          </section>

          <Divider />

          {/* Form */}
          <section>
            <Typography sx={sectionTitleSx}>Form</Typography>
            <Box
              component="form"
              onSubmit={(e) => {
                e.preventDefault();
                setSubmitted(JSON.stringify({ name, role, agree }, null, 2));
              }}
            >
              <Stack spacing={2} sx={{ maxWidth: "24rem" }}>
                <TextField
                  label="Name"
                  size="small"
                  value={name}
                  onChange={(e) => setName(e.target.value)}
                  fullWidth
                />
                <TextField
                  select
                  label="Role"
                  size="small"
                  value={role}
                  onChange={(e) => setRole(e.target.value)}
                  fullWidth
                >
                  {ROLES.map((r) => (
                    <MenuItem key={r} value={r}>
                      {r}
                    </MenuItem>
                  ))}
                </TextField>
                <FormControlLabel
                  control={
                    <Checkbox
                      size="small"
                      checked={agree}
                      onChange={(e) => setAgree(e.target.checked)}
                    />
                  }
                  label="I agree to the terms"
                />
                <Button type="submit" variant="contained" disabled={!agree}>
                  Submit
                </Button>
              </Stack>
            </Box>

            {submitted && (
              <Box
                component="pre"
                sx={{
                  mt: 2,
                  p: 2,
                  borderRadius: 1,
                  bgcolor: "action.hover",
                  fontSize: 13,
                  maxWidth: "24rem",
                  overflow: "auto",
                }}
              >
                {submitted}
              </Box>
            )}
          </section>
        </Stack>
      </Container>
    </ThemeProvider>
  );
}
