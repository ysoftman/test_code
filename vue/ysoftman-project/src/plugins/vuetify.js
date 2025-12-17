import "vuetify/styles";
import { createVuetify } from "vuetify";
import * as components from "vuetify/components";
import * as directives from "vuetify/directives";

const isDark = (() => {
  const v = localStorage.getItem("dark_theme");
  return v === "true";
})();

export const vuetify = createVuetify({
  components,
  directives,
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
