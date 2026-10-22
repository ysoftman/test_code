import "styled-components";

declare module "styled-components" {
  export interface DefaultTheme {
    colors: {
      bg: string;
      fg: string;
      muted: string;
      border: string;
      card: string;
      surface: string;
      primary: string;
      primaryHover: string;
    };
  }
}
