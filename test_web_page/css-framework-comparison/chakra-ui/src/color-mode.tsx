import { ThemeProvider, useTheme } from "next-themes";
import type { ComponentProps } from "react";

// Chakra v3 의 color mode 는 next-themes 로 동작 (html 에 .dark/.light 클래스).
export function ColorModeProvider(props: ComponentProps<typeof ThemeProvider>) {
  return (
    <ThemeProvider
      attribute="class"
      defaultTheme="light"
      enableSystem={false}
      disableTransitionOnChange
      {...props}
    />
  );
}

export function useColorMode() {
  const { resolvedTheme, setTheme } = useTheme();
  const colorMode = resolvedTheme === "dark" ? "dark" : "light";
  const toggleColorMode = () =>
    setTheme(colorMode === "dark" ? "light" : "dark");
  return { colorMode, setColorMode: setTheme, toggleColorMode };
}
