// ysoftman
import {webApiKey} from "./web_api_key.js"
import {initializeApp} from "https://www.gstatic.com/firebasejs/10.0.0/firebase-app.js"
import {getAuth} from "https://www.gstatic.com/firebasejs/10.0.0/firebase-auth.js"
import {getDatabase} from "https://www.gstatic.com/firebasejs/10.0.0/firebase-database.js"
import {getFirestore, collection, doc, getDocs, setDoc, query, orderBy, runTransaction} from "https://www.gstatic.com/firebasejs/10.0.0/firebase-firestore.js"
import {getMessaging} from "https://www.gstatic.com/firebasejs/10.0.0/firebase-messaging.js"
import {getStorage, ref, getDownloadURL, listAll} from "https://www.gstatic.com/firebasejs/10.0.0/firebase-storage.js"

const firebaseConfig = {
    apiKey: webApiKey(),
    authDomain: "ysoftman-firebase.firebaseapp.com",
    databaseURL: "https://ysoftman-firebase.firebaseio.com",
    projectId: "ysoftman-firebase",
    storageBucket: "ysoftman-firebase.appspot.com",
    messagingSenderId: ""
};

const firebase = initializeApp(firebaseConfig);
const storage = getStorage();
const db = getFirestore();
const auth = getAuth();
const loginBoxID = "login_google";
const loginAnonymousBoxID = "login_anonymous";
let userToken = "";
const coll = "restaurant"
export const makeLogoutBoxHTML = function (userName) {
    if (userName.length == 0) {
        return `Anonymous (logout)`
    }
    return `${userName} (logout)`;
}

export const loadImages = async function(htmlId, imageNames) {
    let images =`<div class="item">`
    //forEach 안에서 await 를 사용할 수 없다.
    //imageNames.forEach(function (name) {})
    const imgURLs = []
    for (const name of imageNames) {
        let imgURL = await imageURL(name)
        images += `<div class="nes-container with-title"><p class="title">`+name+` (<span id=`+imgURL+`_size></span>)</p><img loading="lazy" src=`+imgURL+`></img></div>`
        imgURLs.push(imgURL)
    }
    images += `</div>`
    document.getElementById(htmlId).innerHTML = images

    for (const url of imgURLs) {
        // 동기식으로 이미지 크기를 순서대로 파악할 경우
        //await getImgMeta(url).then(img => {
        //    let imgSize="<span>"+img.naturalWidth+"x"+img.naturalHeight+"</span>"
        //    document.getElementById(url+"_size").innerHTML = imgSize
        //})
        getMeta(url, (err, img) => {
            let imgSize="<span>"+img.naturalWidth+"x"+img.naturalHeight+"</span>"
            document.getElementById(url+"_size").innerHTML = imgSize
        });
    }
}

// get image width height
export const getImgMetaSync = (url) => {
    return new Promise((resolver, reject) => {
        const img = new Image();
        img.onload = () => resolver(img);
        img.onerror = (err) => reject(err);
        img.src = url;
    })
}
export const getMeta = (url, cb) => {
  const img = new Image();
  img.onload = () => cb(null, img);
  img.onerror = (err) => cb(err);
  img.src = url;
};

// firestorage 에 저장된 이미지 url 불러오기
export const imageURL = async function (imageName) {
    let storageRef = ref(storage, 'gs://ysoftman-firebase.appspot.com/' + imageName);
    // getDownloadURL() 은 비동기라 await 로 순서를 보장한다
    const url = await getDownloadURL(storageRef);
    return url
}

// firestorage 에 저장된 이미지 list
//export const getImageList = function (path) {
//    let listRef = ref(storage, 'gs://ysoftman-firebase.appspot.com/' + path);
//    const imgList = []
//    // Find all the prefixes and items.
//    listAll(listRef)
//      .then((res) => {
//        res.prefixes.forEach((folderRef) => {
//            // All the prefixes under listRef.
//            // You may call listAll() recursively on them.
//            console.error("aaaaaaaaaaaa", folderRef);
//        });
//        res.items.forEach((itemRef) => {
//            imgList.push(itemRef)
//            // All the items under listRef.
//            console.error("-----", itemRef);
//        });
//      }).catch((error) => {
//        console.error("Error getting image list: ", error);
//      });
//}
//
// firestore 문서 생성
export const setFirestoreDoc = async function (coll, doc) {
    const newdocRef = doc(collection(db, coll));
    await setDoc(newdocRef, {
        name: doc,
        visitCnt: 0
    })
}

// firestore 테스트 방문카운트 및 조회
export const getFirestoreVisitCnt = function (coll, docName, htmlId) {
    let docRef = doc(db, coll, docName);
    // likeCnt 값을 읽어 1개 증가를 트랜젹션(원자적 읽기/쓰기)으로 처리한다.
    runTransaction(db, function (transaction) {
        // This code may get re-run multiple times if there are conflicts.
        return transaction.get(docRef).then(function (doc1) {
            if (!doc1.exists()) {
                throw "Document doest not exist!";
            }
            let newCnt = doc1.data().visitCnt;
            newCnt += 1
            transaction.update(docRef, {
                visitCnt: newCnt
            });
            document.getElementById(htmlId).innerHTML = `${newCnt}`;
        });
    }).then(function () {
        console.log("Transaction successfully committed!");
    }).catch(function (error) {
        console.log("Transaction failed: ", error);
    });
}

// firestore 컬렉션(판교식당) 문서있으면 업데이트 없으면 생성
export const setRestaurantDoc = function (coll, docData) {
    let docRef = doc(db, coll, docData.name);
    runTransaction(db, function (transaction) {
        // This code may get re-run multiple times if there are conflicts.
        return transaction.get(docRef).then(function (doc1) {
            if (doc1.exists) {
                transaction.update(docRef, {
                    name: docData.name,
                    glyphicons: docData.glyphicons,
                    location: docData.location,
                    menu: docData.menu,
                    detailInfo: "https://search.daum.net/search?w=tot&DA=YZR&t__nil_searchbox=btn&q=판교+"+docData.name
                });
                console.log("update RestaurantDoc", doc)
                return
            }
            transaction.set(docRef, {
                name: docData.name,
                glyphicons: docData.glyphicons,
                location: docData.location,
                menu: docData.menu,
                detailInfo: "https://search.daum.net/search?w=tot&DA=YZR&t__nil_searchbox=btn&q=판교+"+docData.name,
                likeCntUsers: docData.likeCntUsers,
                dislikeCntUsers: docData.dislikeCntUsers,
                likeCnt: docData.likeCnt,
                dislikeCnt: doc.dislikeCnt
            });
            console.log("set RestaurantDoc", doc)
        });
    }).then(function () {
        console.log("Transaction successfully committed!");
    }).catch(function (error) {
        console.log("Transaction failed: ", error);
    });
}

export const onLikeClick = function (docName, htmlId) {
    incRestaurantCnt(coll, docName, 'likeCnt', htmlId);
}

export const onDisLikeClick = function (docName, htmlId) {
    incRestaurantCnt(coll, docName, 'dislikeCnt', htmlId);
}

export const readRestaurantAll = async function (coll) {
    // collection 전체 문서 가져오기
    // likeCnt 많은 순으로
    const q = query(collection(db, coll), orderBy("likeCnt", "desc"))
    const querySnapshot = await getDocs(q)
    
    let docNames = [];
    let html = `<div class="card-columns">`;
   
    querySnapshot.forEach((doc) => {
        docNames.push(`${doc.data().name}`);
        html += `
<div class="card">
<div class="card-body">
    <h4 class="card-title">
        ${doc.data().name}
        <img src="glyphicons_free/glyphicons/png/${doc.data().glyphicons}">
    </h4>
    <p class="card-text">${doc.data().location}</p>
    <p class="card-text">${doc.data().menu}</p>
</div>
<p class="text-center">
    <a href="${doc.data().detailInfo}" target="_blank" class="btn btn-primary">상세정보</a>
    <button type="button" id='${doc.data().name}_like' class="btn btn-success"><div id='${doc.data().name}_좋아요'>좋아요 ${doc.data().likeCnt}</div></button>
    <button type="button" id='${doc.data().name}_dislike' class="btn btn-danger"><div id='${doc.data().name}_싫어요'>싫어요 ${doc.data().dislikeCnt}</div></button>
</p>
</div>
`
    });

    html += `</div>`

    document.getElementById('html_out').innerHTML = html;
    for (const name of docNames) {
        //console.log("name:", name)
        //<button onClick="onLikeClick"  으로 하면 onLikeClick 함수를 찾지 못하는 에러가 발생한다.
        //따라서 다음과 같이 이벤트 리스터를 추가한다.
        document.getElementById(name+"_like").addEventListener("click", ()=>{onLikeClick(name, name+"_좋아요")});
        document.getElementById(name+"_dislike").addEventListener("click",()=>{onDisLikeClick(name, name+"_싫어요")});
    }
    document.getElementById("restaurant_cnt").innerHTML = " ("+docNames.length+"개)";
    //console.log(html);
}

// firestore 컬렉션(판교식당) 해당하는 문서 카운트 증가시키기
export const incRestaurantCnt = function (coll, docName, cntType, htmlId) {
    if (!checkLogin()) {
        alert("로그인이 필요합니다.");
        return
    }
    let docRef = doc(collection(db, coll), docName);
    // likeCnt 값을 읽어 1개 증가를 트랜젹션(원자적 읽기/쓰기)으로 처리한다.
    runTransaction(db, function (transaction) {
        // This code may get re-run multiple times if there are conflicts.
        return transaction.get(docRef).then(function (doc1) {
            if (!doc1.exists) {
                throw "Document doest not exist!";
            }
            let newCnt = 0
            let incValue = 1;
            if (cntType == 'likeCnt') {
                let lcUsers = doc1.data().likeCntUsers;
                console.log("lcUsers", lcUsers)
                let pos = lcUsers.indexOf(auth.currentUser.email)
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
                    likeCntUsers: lcUsers
                });
                console.log("incRestaurantCnt", htmlId, `${doc1.data().name} likeCnt: ${newCnt}`)
                document.getElementById(htmlId).innerHTML = `좋아요 ${newCnt}`;
            } else if (cntType == 'dislikeCnt') {
                let dlcUsers = doc1.data().dislikeCntUsers;
                console.log("dlcUsers", dlcUsers)
                let pos = dlcUsers.indexOf(auth.currentUser.email)
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
                    dislikeCntUsers: dlcUsers
                });
                console.log("incRestaurantCnt", htmlId, `${doc1.data().name} dislikeCnt: ${newCnt}`)
                document.getElementById(htmlId).innerHTML = `싫어요 ${newCnt}`;
            }
        });
    }).then(function () {
        console.log("Transaction successfully committed!");
    }).catch(function (error) {
        console.log("Transaction failed: ", error);
    });
}

// 로그인한 사용자에 대한 정보가 필요한 앱 페이지마다 전역 인증 객체에 관찰자를 연결합니다.
// 사용자의 로그인 상태가 변경될 때마다 이 관찰자가 호출됩니다.
auth.onAuthStateChanged((user) => {
    document.getElementById(loginBoxID).addEventListener("click", loginGoogle);
    document.getElementById(loginAnonymousBoxID).addEventListener("click", loginAnonymous);
    if (user) {
        console.log("user:", user)
        if (user.isAnonymous) {
            document.getElementById(loginAnonymousBoxID).innerHTML = makeLogoutBoxHTML("")
            return
        }
        let userName = user.displayName + " " + user.email
        document.getElementById(loginBoxID).innerHTML = makeLogoutBoxHTML(userName)
        document.getElementById(loginAnonymousBoxID).innerHTML = "login Anonymous"
    } else {
        // User is signed out.
        userToken = ""
    }
});


// 로그인 유지설정(필요한 경우에만 호출)
export const setAuthPersistence = function () {
    auth.setPersistence(firebase.auth.Auth.Persistence.SESSION)
        .then(function () {
            // Existing and future Auth states are now persisted in the current
            // session only. Closing the window would clear any existing state even
            // if a user forgets to sign out.
            // ...
            // New sign-in will be persisted with session persistence.
            return auth.signInWithEmailAndPassword(email, password);
        }).catch(function (error) {
            // Handle Errors here.
            let errorCode = error.code;
            let errorMessage = error.message;
        });
}

// 로그인 후 토큰가져오기
export const getToken = function () {
    auth.currentUser.getIdToken(/* forceRefresh */ true).then(function (idToken) {
        // Send token to your backend via HTTPS
        //console.log("idToken:", idToken)
        userToken = idToken
    }).catch(function (error) {
        // Handle error
    });
}

export const checkLogin = () => {
    console.log("auth.currentUser: ", auth.currentUser);
    if (auth.currentUser == null) {
        return false
    }
    if (auth.currentUser.email == "") {
        return false
    }
    return true
}

// firebase > authentication > 익명 로그인 활성화했음
export const loginAnonymous = function () {
    if (auth.currentUser != null && auth.currentUser.isAnonymous) {
        logout()
        document.getElementById(loginAnonymousBoxID).innerHTML = "login Anonymous"
        return
    }
    auth.signInAnonymously()
        .then(() => {
            // Signed in..
            document.getElementById(loginAnonymousBoxID).innerHTML = makeLogoutBoxHTML("")
            window.location.reload();
        })
        .catch((error) => {
            console.log("error: ", error);
            // ...
        });
}

// 구글 로그인하기
export const loginGoogle = function () {
    if (checkLogin()) {
        logout()
        return
    }
    let provider = new firebase.auth.GoogleAuthProvider();
    auth.signInWithPopup(provider).then(function (result) {
        // This gives you a Google Access Token. You can use it to access the Google API.
        userToken = result.credential.accessToken;
        console.log("loginGoogle result.user:", result.user)
        let userName = result.user.displayName + " " + result.user.email
        document.getElementById(loginAnonymousBoxID).innerHTML = "login Anonymous"
        document.getElementById(loginBoxID).innerHTML = makeLogoutBoxHTML(userName)
        // 사용자 토큰 파악해두기
        getToken()
        //GoogleLoginResult()
    }).catch(function (error) {
        // Handle Errors here.
        let errorCode = error.code;
        let errorMessage = error.message;
        // The email of the user's account used.
        let email = error.email;
        // The firebase.auth.AuthCredential type that was used.
        let credential = error.credential;
        alert("errCode:" + error.code +
            "\nerrMessage:" + error.message +
            "\nerrMail:" + error.mail)
    });

}

// 로그아웃
export const logout= function () {
    auth.signOut()
    console.log("logout...")
    document.getElementById(loginAnonymousBoxID).addEventListener("click", loginAnonymous);
    document.getElementById(loginBoxID).addEventListener("click", loginGoogle);
    window.location.reload();
}

// 구글 로그인 이후 결과 정보
export const GoogleLoginResult = function () {
    auth.getRedirectResult().then(function (result) {
        if (result.credential) {
            // This gives you a Google Access Token. You can use it to access the Google API.
            userToken = result.credential.accessToken;
            // ...
        }
        console.log("GoogleLoginResult result.user:", result.user)
    }).catch(function (error) {
        // Handle Errors here.
        let errorCode = error.code;
        let errorMessage = error.message;
        // The email of the user's account used.
        let email = error.email;
        // The firebase.auth.AuthCredential type that was used.
        let credential = error.credential;
        // ...
    });
}


