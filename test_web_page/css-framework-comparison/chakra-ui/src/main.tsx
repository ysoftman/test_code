import React from "react";
import ReactDOM from "react-dom/client";
import {
  ChakraProvider,
  createSystem,
  defaultConfig,
  defineConfig,
} from "@chakra-ui/react";
import { ColorModeProvider } from "./color-mode";
import App from "./App";

// 다른 프레임워크와 동일한 시스템 폰트로 통일
const FONT =
  '-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif';
const system = createSystem(
  defaultConfig,
  defineConfig({
    theme: {
      tokens: {
        fonts: {
          heading: { value: FONT },
          body: { value: FONT },
        },
      },
    },
  }),
);

ReactDOM.createRoot(document.getElementById("root")!).render(
  <React.StrictMode>
    <ChakraProvider value={system}>
      <ColorModeProvider>
        <App />
      </ColorModeProvider>
    </ChakraProvider>
  </React.StrictMode>,
);
