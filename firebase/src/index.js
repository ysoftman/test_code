import "@fontsource/press-start-2p";
// yarn add nes.css --ignore-engines
import "nes.css/css/nes.min.css";
import "./common.js";
import { getStorage, ref, getDownloadURL, listAll } from "firebase/storage";
import {
  getFirestore,
  collection,
  doc,
  getDocs,
  setDoc,
  query,
  where,
  orderBy,
  runTransaction,
  updateDoc,
  deleteField,
} from "firebase/firestore";

const storage = getStorage();
const db = getFirestore();

export const loadImages = async function (htmlId, imageNames) {
  document.getElementById(htmlId).innerHTML = "";
  let isImage = true;
  let item = "";
  for (const name of imageNames) {
    isImage = true;
    if (name.endsWith("mp4")) {
      isImage = false;
    }
    if (isImage) {
      item =
        `<div class="nes-container with-title"><p class="title">` +
        name +
        ` (<span id="` +
        name +
        `_img_size"></span>)</p><div id="` +
        name +
        `_img"></div></div>`;
    } else {
      item =
        `<div class="nes-container with-title"><p class="title">` +
        name +
        `</p><div id="` +
        name +
        `_video"></div></div>`;
    }
    document.getElementById(htmlId).insertAdjacentHTML("beforeend", item);
  }
  //forEach 안에서 await 를 사용할 수 없다.
  //imageNames.forEaCh(function (name) {})
  for (const name of imageNames) {
    // firestorage 에 저장된 이미지 url 불러오기
    let storageRef = ref(storage, name);
    getDownloadURL(storageRef).then((url) => {
      isImage = true;
      if (name.endsWith("mp4")) {
        isImage = false;
      }
      let id = name;
      if (isImage) {
        item = `<img loading="lazy" src=` + url + `></img>`;
        id += "_img";
      } else {
        item =
          `<video width="640" controls autoplay muted><source type="video/mp4" src=` +
          url +
          `></video>`;
        id += "_video";
      }
      if (document.getElementById(id) == null) {
        return;
      }
      document.getElementById(id).innerHTML = item;
      if (isImage) {
        // 동기식으로 이미지 크기를 순서대로 파악할 경우
        //await getImgMetaSync(url).then(img => {
        //    let imgSize="<span>"+img.naturalWidth+"x"+img.naturalHeight+"</span>"
        //    document.getElementById(url+"_size").innerHTML = imgSize
        //})
        getMeta(url, (err, img) => {
          let imgSize =
            "<span>" + img.naturalWidth + "x" + img.naturalHeight + "</span>";
          if (document.getElementById(name + "_img_size") == null) {
            return;
          }
          document.getElementById(name + "_img_size").innerHTML = imgSize;
        });
      }
    });
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

export const getImageDirs = async function (path) {
  let listRef = ref(storage, path);
  const pathList = [];
  const res = await listAll(listRef);
  res.prefixes.forEach((folderRef) => {
    pathList.push(folderRef.fullPath);
    //console.log("directory:", folderRef.fullPath);
  });
  return pathList;
};
// firestorage 에 저장된 이미지 list
export const getImageList = async function (path) {
  let listRef = ref(storage, path);
  const imgList = [];
  // Find all the prefixes and items.
  const res = await listAll(listRef);
  res.items.forEach((itemRef) => {
    imgList.push(itemRef.fullPath);
    //console.log("file:", itemRef.fullPath);
  });
  return imgList;
};

// firestore 문서 생성
export const setFirestoreDoc = async function (coll, docName) {
  const newdocRef = doc(collection(db, coll), docName);
  await setDoc(newdocRef, {
    name: docName,
    visitCnt: 1,
  });
};

// firestore 테스트 방문카운트 및 조회
export const getFirestoreVisitCnt = function (coll, docName, htmlId) {
  let docRef = doc(db, coll, docName);
  // likeCnt 값을 읽어 1개 증가를 트랜젹션(원자적 읽기/쓰기)으로 처리한다.
  runTransaction(db, function (transaction) {
    // This code may get re-run multiple times if there are conflicts.
    return transaction.get(docRef).then(function (doc1) {
      if (!doc1.exists() || doc1.data().visitCnt == undefined) {
        //throw "Document doest not exist!";
        setFirestoreDoc(coll, docName);
        document.getElementById(htmlId).innerHTML = `1`;
        return;
      }
      let newCnt = doc1.data().visitCnt;
      newCnt += 1;
      transaction.update(docRef, {
        visitCnt: newCnt,
      });
      document.getElementById(htmlId).innerHTML = `${newCnt}`;
    });
  })
    .then(function () {
      console.log("Transaction successfully committed!");
    })
    .catch(function (error) {
      console.log("Transaction failed: ", error);
    });
};

const version =
  "last_version: " +
  __LAST_VERSION_TAG__ +
  "<br>" +
  "last_commit_hash: " +
  __LAST_COMMIT_HASH__ +
  "<br>" +
  "last_commit_date: " +
  __LAST_COMMIT_DATE__ +
  "<br>" +
  "last_commit_message: " +
  __LAST_COMMIT_MESSAGE__ +
  "<br>";
document.getElementById("version").innerHTML = version;

async function loadImg(path) {
  const imgNames = await getImageList(path);
  // image div 태그를 구성해 이미지 순서를 보장
  await loadImages("images", imgNames);
}

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

getFirestoreVisitCnt("index", "ysoftman", "visitcnt");

if (imgDirs.length > 0) {
  loadImg(imgDirs[0]);
}
