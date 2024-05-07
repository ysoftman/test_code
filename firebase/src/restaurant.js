import "./bootstrap.scss";
import "./common.js";
import { restaurantlist } from "./restaurant_list.js";
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

const coll = "restaurant";
const db = getFirestore();

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

window.onload = function () {
  readRestaurantAll(coll);

  //컬렉션: restaurant 문서 추가 및 업데이트(db export 기능이 있지만 결재가 필요함)
  //local restaurant.html 접속
  //구글 로그인 후 강제 refresh(ctrl+shift+r)
  //식당리스트가 firestore 에 자동 추가되어 보인다.
  //updateRestaurantAll();
};
