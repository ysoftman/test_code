import "vuetify/styles";
import { createVuetify } from "vuetify";

const isDark = (() => {
  const v = localStorage.getItem("dark_theme");
  return v === "true";
})();

export const vuetify = createVuetify({
  theme: {
    defaultTheme: isDark ? "dark" : "light",
    themes: {
      light: {
        dark: false,
      },
      dark: {
        dark: true,
      },
    },
  },
});
