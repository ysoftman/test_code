import { useEffect, useMemo, useState } from "react";
import {
  AppBar,
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
  IconButton,
  MenuItem,
  Stack,
  TextField,
  Toolbar,
  Typography,
  createTheme,
  ThemeProvider,
} from "@mui/material";
import DarkModeIcon from "@mui/icons-material/DarkMode";
import LightModeIcon from "@mui/icons-material/LightMode";
import FavoriteIcon from "@mui/icons-material/Favorite";

// 모든 프레임워크가 공유하는 데모 사양:
// 1) 다크모드 토글  2) 버튼 변형  3) 카드  4) 폼(입력 -> 제출 결과 표시)

const ROLES = ["Frontend", "Backend", "Designer", "PM"];

export default function App() {
  const [mode, setMode] = useState<"light" | "dark">("light");
  const theme = useMemo(() => createTheme({ palette: { mode } }), [mode]);

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
      <AppBar position="static" color="default" elevation={1}>
        <Toolbar>
          <Typography variant="h6" sx={{ flexGrow: 1 }}>
            MUI
          </Typography>
          <Typography variant="body2" sx={{ mr: 1, opacity: 0.7 }}>
            Material UI · Emotion (runtime)
          </Typography>
          <IconButton
            onClick={() => setMode((m) => (m === "dark" ? "light" : "dark"))}
            color="inherit"
            aria-label="toggle dark mode"
          >
            {mode === "dark" ? <LightModeIcon /> : <DarkModeIcon />}
          </IconButton>
        </Toolbar>
      </AppBar>

      <Container maxWidth="md" sx={{ py: 4 }}>
        <Stack spacing={4}>
          {/* Buttons */}
          <section>
            <Typography variant="h6" gutterBottom>
              Buttons
            </Typography>
            <Stack direction="row" spacing={2} flexWrap="wrap" useFlexGap>
              <Button variant="contained">Contained</Button>
              <Button variant="outlined">Outlined</Button>
              <Button variant="text">Text</Button>
              <Button variant="contained" startIcon={<FavoriteIcon />}>
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
            <Typography variant="h6" gutterBottom>
              Card
            </Typography>
            <Card sx={{ maxWidth: 360 }}>
              <CardContent>
                <Typography variant="h6" gutterBottom>
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
            <Typography variant="h6" gutterBottom>
              Form
            </Typography>
            <Box
              component="form"
              onSubmit={(e) => {
                e.preventDefault();
                setSubmitted(JSON.stringify({ name, role, agree }, null, 2));
              }}
            >
              <Stack spacing={2} sx={{ maxWidth: 360 }}>
                <TextField
                  label="Name"
                  value={name}
                  onChange={(e) => setName(e.target.value)}
                  fullWidth
                />
                <TextField
                  select
                  label="Role"
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
                  maxWidth: 360,
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
