import "@fontsource/press-start-2p";
// yarn add nes.css --ignore-engines
import "nes.css/css/nes.min.css";
import {
  getFirestoreVisitCnt,
  getImageDirs,
  getImageList,
  loadImages,
} from "./common.js";
getFirestoreVisitCnt("index", "ysoftman", "visitcnt");

const imgDirs = await getImageDirs("/");
for (const dir of imgDirs) {
  const item =
    `<button class="nes-btn is-primary" id='load_` +
    dir +
    `'>` +
    dir +
    `</button>`;
  document
    .getElementById("load_img_buttons")
    .insertAdjacentHTML("beforeend", item);
  document.getElementById("load_" + dir).addEventListener("click", () => {
    if (document.getElementById("images") != null) {
      document.getElementById("images").innerHTML = "";
    }
    loadImg(dir);
  });
}

async function loadImg(path) {
  const imgNames = await getImageList(path);
  // image div 태그를 구성해 이미지 순서를 보장
  await loadImages("images", imgNames);
}
if (imgDirs.length > 0) {
  loadImg(imgDirs[0]);
}