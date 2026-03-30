import { execSync } from "node:child_process";
import { defineConfig } from "vite";

function getGitInfo() {
  try {
    const lastGitTag = execSync("git describe master --tags --exact-match 2> /dev/null || echo 'develop'")
      .toString()
      .trim();
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
