import { defineConfig } from "vitepress";

// docs -> ../../MachineLearning 심볼릭 링크로 원본 md 를 복사 없이 그대로 사용한다.
// Served from GitHub Pages at /test_code/ml-docs/
export default defineConfig({
  srcDir: "docs",
  rewrites: { "README.md": "index.md" },
  base: "/test_code/ml-docs/",
  lang: "ko-KR",
  title: "MachineLearning",
  description: "ML 책, 강의 내용 정리",
  lastUpdated: true,
  // 링크 경로를 유지해야 md 가 import 하는 vue 를 이 프로젝트의 node_modules 에서 찾는다.
  vite: { resolve: { preserveSymlinks: true } },
  themeConfig: {
    outline: [2, 3],
    search: { provider: "local" },
    sidebar: [
      { text: "개요", link: "/" },
      {
        text: "책, 강의 내용 정리",
        items: [
          {
            text: "DeepLearning from Scratch",
            link: "/deeplearning_from_scratch",
          },
          {
            text: "K-MOOC 2018 인공지능 및 기계학습",
            link: "/kmooc_2018_인공지능_및_기계학습",
          },
          {
            text: "K-MOOC 2019 인공지능의 기초",
            link: "/kmooc_2019_인공지능의_기초",
          },
        ],
      },
    ],
    socialLinks: [
      {
        icon: "github",
        link: "https://github.com/ysoftman/test_code/tree/main/MachineLearning",
      },
    ],
  },
});
