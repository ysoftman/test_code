// ysoftman
import "./common.css"; // css, scss 중 마지막에 import 해야 올바르게 적용된다.
import { webApiKey } from "./web_api_key.js";
import { restaurantlist } from "./restaurant_list.js";
import { initializeApp } from "firebase/app";
import {
  getAuth,
  signInAnonymously,
  onAuthStateChanged,
  GoogleAuthProvider,
  signInWithPopup,
  signOut,
  getRedirectResult,
  setPersistence,
  signInWithEmailAndPassword,
} from "firebase/auth";
import { getDatabase } from "firebase/database";
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
import { getMessaging } from "firebase/messaging";
import { getStorage, ref, getDownloadURL, listAll } from "firebase/storage";

const firebaseConfig = {
  apiKey: webApiKey(),
  authDomain: "ysoftman-firebase.firebaseapp.com",
  databaseURL: "https://ysoftman-firebase.firebaseio.com",
  projectId: "ysoftman-firebase",
  storageBucket: "ysoftman-firebase.appspot.com",
  messagingSenderId: "",
};

const firebase = initializeApp(firebaseConfig);
const storage = getStorage();
const db = getFirestore();
const auth = getAuth();
const loginBoxID = "login_google";
const loginAnonymousBoxID = "login_anonymous";
const coll = "restaurant";
export const makeLogoutBoxHTML = function (userName) {
  if (userName.length == 0) {
    return `Anonymous (logout)`;
  }
  return `${userName} (logout)`;
};

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

// firestore 컬렉션 문서있으면 업데이트 없으면 생성
export const setRestaurantDoc = function (coll, docData) {
  let docRef = doc(db, coll, docData.name);
  runTransaction(db, function (transaction) {
    // This code may get re-run multiple times if there are conflicts.
    return transaction.get(docRef).then(function (doc1) {
      if (doc1.exists()) {
        // 필드 삭제시
        //updateDoc(docRef, { menu: deleteField(), detailInfo: deleteField() });
        transaction.update(docRef, {
          name: docData.name,
          glyphicons: docData.glyphicons,
          location: docData.location,
          tags: docData.tags,
        });
        console.log("update RestaurantDoc", docData);
        return;
      }
      transaction.set(docRef, {
        name: docData.name,
        glyphicons: docData.glyphicons,
        location: docData.location,
        tags: docData.tags,
        likeCntUsers: docData.likeCntUsers,
        dislikeCntUsers: docData.dislikeCntUsers,
        likeCnt: docData.likeCnt,
        dislikeCnt: docData.dislikeCnt,
      });
      console.log("set RestaurantDoc", doc);
    });
  })
    .then(function () {
      console.log("Transaction successfully committed!");
    })
    .catch(function (error) {
      console.log("Transaction failed: ", docData.name, error);
    });
};

export const onLikeClick = function (docName, htmlId) {
  incRestaurantCnt(coll, docName, "likeCnt", htmlId);
};

export const onDisLikeClick = function (docName, htmlId) {
  incRestaurantCnt(coll, docName, "dislikeCnt", htmlId);
};
export const backupRestaurantDB = async function (coll) {
  // collection 전체 문서 가져오기
  // likeCnt 많은 순으로
  const q = query(collection(db, coll), orderBy("likeCnt", "desc"));
  const querySnapshot = await getDocs(q);

  let data = "export let restaurantlist = [\n";

  querySnapshot.forEach((doc) => {
    data += JSON.stringify(doc.data());
    console.log("----", JSON.stringify(doc.data()));
  });
  data += "\n]";
  return data;
};
export const updateRestaurantAll = function () {
  // firestore 컬렉션 문서있으면 업데이트 없으면 생성
  restaurantlist.forEach((doc) => {
    setRestaurantDoc(coll, doc);
  });
};

export const makeDetailInfo = function (name) {
  return (
    "https://search.daum.net/search?w=tot&DA=YZR&t__nil_searchbox=btn&q=" + name
  );
};

export const readRestaurantAll = async function (coll, tag) {
  if (tag == undefined) {
    console.log("undefined tag");
    tag = "";
  }
  // collection 전체 문서 가져오기
  // likeCnt 많은 순으로
  const q = query(collection(db, coll), orderBy("likeCnt", "desc"));
  const querySnapshot = await getDocs(q);

  let docNames = [];
  let html = `<div class="row row-cols-1 row-cols-md-3 g-4">`;

  querySnapshot.forEach((doc) => {
    if (
      !doc.data().name.includes(tag) &&
      !doc.data().location.includes(tag) &&
      !doc.data().tags.includes(tag)
    ) {
      return;
    }
    docNames.push(doc.data().name);
    let detailInfo = makeDetailInfo(doc.data().name);
    html += `
<div class="col">
<div class="card h-100">
<div class="card-body">
    <h4 class="card-title">
        ${doc.data().name}
        <i class="bi ${doc.data().glyphicons}"></i>
    </h4>
    <p class="card-text">${doc.data().location}</p>
    <p class="card-text">${doc.data().tags}</p>
</div>
<p class="text-center">
    <a href="${detailInfo}" target="_blank" class="btn btn-primary">상세정보</a>
    <button type="button" id='${doc.data().name}_like' class="btn btn-success"><div id='${doc.data().name}_좋아요'>좋아요 ${doc.data().likeCnt}</div></button>
    <button type="button" id='${doc.data().name}_dislike' class="btn btn-danger"><div id='${doc.data().name}_싫어요'>싫어요 ${doc.data().dislikeCnt}</div></button>
</p>
</div>
</div>
`;
  });

  html += `</div>`;

  document.getElementById("html_out").innerHTML = html;
  for (const name of docNames) {
    //console.log("name:", name)
    //<button onClick="onLikeClick"  으로 하면 onLikeClick 함수를 찾지 못하는 에러가 발생한다.
    //따라서 다음과 같이 이벤트 리스터를 추가한다.
    document.getElementById(name + "_like").addEventListener("click", () => {
      onLikeClick(name, name + "_좋아요");
    });
    document.getElementById(name + "_dislike").addEventListener("click", () => {
      onDisLikeClick(name, name + "_싫어요");
    });
  }
  document.getElementById("restaurant_cnt").innerHTML =
    " (결과: " + docNames.length + "개)";

  document
    .getElementById("search_restaurant_input")
    .addEventListener("keypress", function (event) {
      if (event.key === "Enter") {
        event.preventDefault();
        document.getElementById("search_restaurant_button").click();
      }
    });
  document
    .getElementById("search_restaurant_button")
    .addEventListener("click", () => {
      readRestaurantAll(
        coll,
        document.getElementById("search_restaurant_input").value,
      );
    });

  //console.log(html);
};

// firestore 컬렉션 해당하는 문서 카운트 증가시키기
export const incRestaurantCnt = function (coll, docName, cntType, htmlId) {
  if (!checkLogin()) {
    alert("로그인이 필요합니다.");
    return;
  }
  let docRef = doc(collection(db, coll), docName);
  // likeCnt 값을 읽어 1개 증가를 트랜젹션(원자적 읽기/쓰기)으로 처리한다.
  runTransaction(db, function (transaction) {
    // This code may get re-run multiple times if there are conflicts.
    return transaction.get(docRef).then(function (doc1) {
      if (!doc1.exists()) {
        throw "Document doest not exist!";
      }
      let newCnt = 0;
      let incValue = 1;
      if (cntType == "likeCnt") {
        let lcUsers = doc1.data().likeCntUsers;
        console.log("lcUsers", lcUsers);
        let pos = lcUsers.indexOf(auth.currentUser.email);
        // 좋아요를 이미 클릭한 사용자라면 카운트 취소하기
        if (pos >= 0) {
          incValue = -1;
          lcUsers.splice(pos, 1);
        } else {
          lcUsers.push(auth.currentUser.email);
        }
        newCnt = doc1.data().likeCnt + incValue;
        transaction.update(docRef, {
          likeCnt: newCnt,
          likeCntUsers: lcUsers,
        });
        console.log(
          "incRestaurantCnt",
          htmlId,
          `${doc1.data().name} likeCnt: ${newCnt}`,
        );
        document.getElementById(htmlId).innerHTML = `좋아요 ${newCnt}`;
      } else if (cntType == "dislikeCnt") {
        let dlcUsers = doc1.data().dislikeCntUsers;
        console.log("dlcUsers", dlcUsers);
        let pos = dlcUsers.indexOf(auth.currentUser.email);
        // 싫어요를 이미 클릭한 사용자라면 카운트 취소하기
        if (pos >= 0) {
          incValue = -1;
          dlcUsers.splice(pos, 1);
        } else {
          dlcUsers.push(auth.currentUser.email);
        }
        newCnt = doc1.data().dislikeCnt + incValue;
        transaction.update(docRef, {
          dislikeCnt: newCnt,
          dislikeCntUsers: dlcUsers,
        });
        console.log(
          "incRestaurantCnt",
          htmlId,
          `${doc1.data().name} dislikeCnt: ${newCnt}`,
        );
        document.getElementById(htmlId).innerHTML = `싫어요 ${newCnt}`;
      }
    });
  })
    .then(function () {
      console.log("Transaction successfully committed!");
    })
    .catch(function (error) {
      console.log("Transaction failed: ", error);
    });
};

// 로그인한 사용자에 대한 정보가 필요한 앱 페이지마다 전역 인증 객체에 관찰자를 연결합니다.
// 사용자의 로그인 상태가 변경될 때마다 이 관찰자가 호출됩니다.
onAuthStateChanged(auth, (user) => {
  document.getElementById(loginBoxID).addEventListener("click", loginGoogle);
  document
    .getElementById(loginAnonymousBoxID)
    .addEventListener("click", loginAnonymous);
  if (user) {
    console.log("user:", user);
    if (user.isAnonymous) {
      document.getElementById(loginAnonymousBoxID).innerHTML =
        makeLogoutBoxHTML("");
      return;
    }
    let userName = user.displayName + " " + user.email;
    document.getElementById(loginBoxID).innerHTML = makeLogoutBoxHTML(userName);
    document.getElementById(loginAnonymousBoxID).innerHTML = "login Anonymous";
  } else {
    // User is signed out.
  }
});

// 로그인 유지설정(필요한 경우에만 호출)
export const setAuthPersistence = function () {
  setPersistence(auth, firebase.auth.Auth.Persistence.SESSION)
    .then(function () {
      return signInWithEmailAndPassword(auth, email, password);
    })
    .catch(function (error) {
      alert("errCode:" + error.code + "\nerrMessage:" + error.message);
    });
};

export const checkLogin = () => {
  console.log("auth.currentUser: ", auth.currentUser);
  if (auth.currentUser == null) {
    return false;
  }
  if (auth.currentUser.email == "") {
    return false;
  }
  return true;
};

// firebase > authentication > 익명 로그인 활성화했음
export const loginAnonymous = function () {
  if (auth.currentUser != null && auth.currentUser.isAnonymous) {
    logout();
    document.getElementById(loginAnonymousBoxID).innerHTML = "login Anonymous";
    return;
  }
  signInAnonymously(auth)
    .then(() => {
      // Signed in..
      document.getElementById(loginAnonymousBoxID).innerHTML =
        makeLogoutBoxHTML("");
      window.location.reload();
    })
    .catch((error) => {
      console.log("error: ", error);
      // ...
    });
};

// 구글 로그인하기
export const loginGoogle = function () {
  if (checkLogin()) {
    logout();
    return;
  }
  let provider = new GoogleAuthProvider();
  signInWithPopup(auth, provider)
    .then(function (result) {
      // This gives you a Google Access Token. You can use it to access the Google API.
      console.log("loginGoogle result.user:", result.user);
      let userName = result.user.displayName + " " + result.user.email;
      document.getElementById(loginAnonymousBoxID).innerHTML =
        "login Anonymous";
      document.getElementById(loginBoxID).innerHTML =
        makeLogoutBoxHTML(userName);
      //GoogleLoginResult()
    })
    .catch(function (error) {
      alert(
        "errCode:" +
          error.code +
          "\nerrMessage:" +
          error.message +
          "\nerrMail:" +
          error.mail,
      );
    });
};

// 로그아웃
export const logout = function () {
  signOut(auth);
  console.log("logout...");
  document
    .getElementById(loginAnonymousBoxID)
    .addEventListener("click", loginAnonymous);
  document.getElementById(loginBoxID).addEventListener("click", loginGoogle);
  window.location.reload();
};

// 구글 로그인 이후 결과 정보
export const GoogleLoginResult = function () {
  getRedirectResult(auth)
    .then(function (result) {
      if (result.credential) {
        // This gives you a Google Access Token. You can use it to access the Google API.
      }
      console.log("GoogleLoginResult result.user:", result.user);
    })
    .catch(function (error) {
      alert(
        "errCode:" +
          error.code +
          "\nerrMessage:" +
          error.message +
          "\nerrMail:" +
          error.mail,
      );
    });
};