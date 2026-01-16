// Generated using webpack-cli https://github.com/webpack/webpack-cli
import HtmlWebpackPlugin from "html-webpack-plugin";
import path from "path";
import webpack from "webpack";
import { CleanWebpackPlugin } from "clean-webpack-plugin";
import { execSync } from "child_process";
import { fileURLToPath } from "url";

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
    const lastGitTag = execSync("git describe master --tags 2> /dev/null || echo 'develop'").toString().trim();

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
      GIT_TAG: JSON.stringify("unknown"),
      LAST_GIT_COMMIT_HASH: JSON.stringify("unknown"),
      LAST_GIT_COMMIT_DATE: JSON.stringify("unknown"),
      LAST_GIT_COMMIT_MESSAGE: JSON.stringify("unknown"),
    };
  }
}
const gitInfo = getGitInfo();

const isProduction = process.env.NODE_ENV === "production";

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const config = {
  entry: {
    index: "./src/index.js",
  },
  output: {
    path: path.resolve(__dirname, "dist"),
    filename: "[name].js",
    clean: true,
  },
  devServer: {
    open: true,
    host: "localhost",
  },
  plugins: [
    new CleanWebpackPlugin(),
    new HtmlWebpackPlugin({
      filename: "index.html",
      template: "./src/index.html",
      chunks: ["page1"],
    }),
    new webpack.IgnorePlugin({
      resourceRegExp: /^\.\/locale$/,
      contextRegExp: /moment$/,
    }),
    new webpack.DefinePlugin({
      __LAST_VERSION_TAG__: gitInfo.LAST_GIT_TAG,
      __LAST_COMMIT_HASH__: gitInfo.LAST_GIT_COMMIT_HASH,
      __LAST_COMMIT_DATE__: gitInfo.LAST_GIT_COMMIT_DATE,
      __LAST_COMMIT_MESSAGE__: gitInfo.LAST_GIT_COMMIT_MESSAGE,
    }),
  ],
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /(node_modules|bower_components)/,
        use: {
          loader: "babel-loader",
          options: {
            presets: ["@babel/preset-env"],
          },
        },
      },
      {
        test: /\.(eot|svg|ttf|woff|woff2|png|jpg|gif)$/i,
        // webpack5 부터 asset/resource 타입이면 file-loader 없이 자동 번들된다.
        type: "asset/resource",
        generator: {
          filename: "[name][ext]",
        },
      },
      {
        test: /\.css$/,
        use: ["style-loader", "css-loader"],
      },
      {
        test: /\.s[ac]ss$/,
        use: ["style-loader", "css-loader", "sass-loader"],
      },
    ],
  },
  watchOptions: {
    poll: 1000,
  },
};

export default () => {
  if (isProduction) {
    config.mode = "production";
  } else {
    config.mode = "development";
  }
  return config;
};
