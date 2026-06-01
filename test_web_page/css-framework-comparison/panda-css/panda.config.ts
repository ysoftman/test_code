import { defineConfig } from "@pandacss/dev";

export default defineConfig({
  // 전역 리셋 포함
  preflight: true,

  // 스타일 추출 대상 (정적 분석)
  include: ["./src/**/*.{js,jsx,ts,tsx}"],
  exclude: [],

  theme: { extend: {} },

  // 생성 코드 출력 위치 (gitignore 처리됨)
  outdir: "styled-system",
});
