import { execSync } from "node:child_process";
import { defineConfig } from "vite";

function getGitInfo() {
  try {
    // github action 에서 태그정보를 파악할 수 있도록 다음 설정 추가
    // - name: Checkout repository
    //   uses: actions/checkout@v4
    //   with:
    //     # 전체 이력(tags 포함) 가져오기
    //     fetch-depth: 0
    //     # 또는 태그 정보  표시
    //     # tags: true

    // 현재 커밋에 Git 태그가 매칭되면 태그 사용 아니면 "develop"
    // "git describe master --tags --exact-match 2> /dev/null || echo 'develop'",
    // 커밋 해시나 태그 이후의 커밋 수를 포함하지 않고, 가장 가까운 태그 이름만 출력
    // "git describe master --tags --abbrev=0 2> /dev/null || echo 'develop'",
    const lastGitTag = execSync("git describe master --tags --exact-match 2> /dev/null || echo 'develop'").toString().trim();

    const lastGitCommitHash = execSync("git log master -1 --date=iso-strict --pretty=format:'%H'").toString().trim();
    const lastGitCommitDate = execSync("git log master -1 --date=iso-strict --pretty=format:'%cd'").toString().trim();
    const lastGitCommitMessage = execSync("git log master -1 --pretty=format:'%s'").toString().trim();
    return {
      LAST_GIT_TAG: JSON.stringify(lastGitTag),
      LAST_GIT_COMMIT_HASH: JSON.stringify(lastGitCommitHash),
      LAST_GIT_COMMIT_DATE: JSON.stringify(lastGitCommitDate),
      LAST_GIT_COMMIT_MESSAGE: JSON.stringify(lastGitCommitMessage),
    };
  } catch {
    console.warn("Git command failed, returning default values.");
    return {
      LAST_GIT_TAG: JSON.stringify("unknown"),
      LAST_GIT_COMMIT_HASH: JSON.stringify("unknown"),
      LAST_GIT_COMMIT_DATE: JSON.stringify("unknown"),
      LAST_GIT_COMMIT_MESSAGE: JSON.stringify("unknown"),
    };
  }
}

const gitInfo = getGitInfo();

export default defineConfig({
  define: {
    __LAST_VERSION_TAG__: gitInfo.LAST_GIT_TAG,
    __LAST_COMMIT_HASH__: gitInfo.LAST_GIT_COMMIT_HASH,
    __LAST_COMMIT_DATE__: gitInfo.LAST_GIT_COMMIT_DATE,
    __LAST_COMMIT_MESSAGE__: gitInfo.LAST_GIT_COMMIT_MESSAGE,
  },
  server: {
    open: true,
  },
  build: {
    outDir: "dist",
    target: "esnext",
  },
});
