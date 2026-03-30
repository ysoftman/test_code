import "./common.js";
import "@fontsource/press-start-2p";
import "nes.css/css/nes.min.css";
import { supabase } from "./common.js";

const STORAGE_BUCKET = "images";

export const loadImages = async (htmlId, imageNames) => {
  document.getElementById(htmlId).innerHTML = "";
  let isImage = true;
  let item = "";
  for (const name of imageNames) {
    isImage = true;
    if (name.endsWith("mp4")) {
      isImage = false;
    }
    if (isImage) {
      item = `<div class="nes-container with-title"><p class="title">${name} (<span id="${name}_img_size"></span>)</p><div id="${name}_img"></div></div>`;
    } else {
      item = `<div class="nes-container with-title"><p class="title">${name}</p><div id="${name}_video"></div></div>`;
    }
    document.getElementById(htmlId).insertAdjacentHTML("beforeend", item);
  }
  for (const name of imageNames) {
    // supabase storage 에 저장된 이미지 public url 불러오기
    const {
      data: { publicUrl },
    } = supabase.storage.from(STORAGE_BUCKET).getPublicUrl(name);
    const url = publicUrl;
    isImage = true;
    if (name.endsWith("mp4")) {
      isImage = false;
    }
    let id = name;
    if (isImage) {
      item = `<img loading="lazy" src=${url}></img>`;
      id += "_img";
    } else {
      item = `<video width="640" controls autoplay muted><source type="video/mp4" src=${url}></video>`;
      id += "_video";
    }
    if (document.getElementById(id) == null) {
      continue;
    }
    document.getElementById(id).innerHTML = item;
    if (isImage) {
      getMeta(url, (_err, img) => {
        const imgSize = `<span>${img.naturalWidth}x${img.naturalHeight}</span>`;
        if (document.getElementById(`${name}_img_size`) == null) {
          return;
        }
        document.getElementById(`${name}_img_size`).innerHTML = imgSize;
      });
    }
  }
};

// get image width height
export const getImgMetaSync = (url) => {
  return new Promise((resolver, reject) => {
    const img = new Image();
    img.onload = () => resolver(img);
    img.onerror = (err) => reject(err);
    img.src = url;
  });
};
export const getMeta = (url, cb) => {
  const img = new Image();
  img.onload = () => cb(null, img);
  img.onerror = (err) => cb(err);
  img.src = url;
};

// supabase storage 디렉토리 목록 조회
export const getImageDirs = async (path) => {
  const { data, error } = await supabase.storage.from(STORAGE_BUCKET).list(path, {
    limit: 1000,
    sortBy: { column: "name", order: "asc" },
  });
  if (error) {
    console.log("getImageDirs error:", error);
    return [];
  }
  // 폴더는 id가 null인 항목
  const dirs = data
    .filter((item) => item.id === null)
    .map((item) => {
      if (path === "" || path === "/") return item.name;
      return `${path}/${item.name}`;
    });
  return dirs;
};

// supabase storage 에 저장된 이미지 list
export const getImageList = async (path) => {
  const { data, error } = await supabase.storage.from(STORAGE_BUCKET).list(path, {
    limit: 1000,
    sortBy: { column: "name", order: "asc" },
  });
  if (error) {
    console.log("getImageList error:", error);
    return [];
  }
  // 파일은 id가 null이 아닌 항목
  const files = data
    .filter((item) => item.id !== null)
    .map((item) => {
      if (path === "" || path === "/") return item.name;
      return `${path}/${item.name}`;
    });
  return files;
};

// supabase database(index 테이블) 문서 생성
export const setVisitDoc = async (docName) => {
  const { error } = await supabase.from("index").upsert({
    name: docName,
    visit_cnt: 1,
  });
  if (error) {
    console.log("setVisitDoc error:", error);
  }
};

// supabase database 방문카운트 조회 및 증가
// RPC(stored procedure) 를 사용해 원자적 증가 처리
export const getVisitCnt = async (docName, htmlId) => {
  // rpc 함수 increment_visit_cnt 호출 (supabase SQL editor 에서 생성 필요)
  const { data, error } = await supabase.rpc("increment_visit_cnt", {
    doc_name: docName,
  });
  if (error) {
    console.log("getVisitCnt error:", error);
    // rpc 실패시 직접 조회 시도
    const { data: row } = await supabase.from("index").select("visit_cnt").eq("name", docName).single();
    if (row) {
      document.getElementById(htmlId).innerHTML = `${row.visit_cnt}`;
    }
    return;
  }
  document.getElementById(htmlId).innerHTML = `${data}`;
};

const version = `last_version: ${__LAST_VERSION_TAG__}<br>last_commit_hash: ${__LAST_COMMIT_HASH__}<br>last_commit_date: ${__LAST_COMMIT_DATE__}<br>last_commit_message: ${__LAST_COMMIT_MESSAGE__}<br>`;
document.getElementById("version").innerHTML = version;

async function loadImg(path) {
  const imgNames = await getImageList(path);
  // image div 태그를 구성해 이미지 순서를 보장
  await loadImages("images", imgNames);
}

const imgDirs = await getImageDirs("");
for (const dir of imgDirs) {
  const item = `<button class="nes-btn is-primary" id='load_${dir}'>${dir}</button>`;
  document.getElementById("load_img_buttons").insertAdjacentHTML("beforeend", item);
  document.getElementById(`load_${dir}`).addEventListener("click", () => {
    if (document.getElementById("images") != null) {
      document.getElementById("images").innerHTML = "";
    }
    loadImg(dir);
  });
}

getVisitCnt("ysoftman", "visitcnt");

if (imgDirs.length > 0) {
  loadImg(imgDirs[0]);
}
