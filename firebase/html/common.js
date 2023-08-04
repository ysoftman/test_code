// ysoftman
// firebase api 사용
// Initialize Firebase
import {webApiKey} from "./web_api_key.js"
var config = {
    apiKey: webApiKey(),
    authDomain: "ysoftman-firebase.firebaseapp.com",
    databaseURL: "https://ysoftman-firebase.firebaseio.com",
    projectId: "ysoftman-firebase",
    storageBucket: "ysoftman-firebase.appspot.com",
    messagingSenderId: ""
};
firebase.initializeApp(config);

// Create a reference with an initial file path and name
var storage = firebase.storage();
var db = firebase.firestore();
var auth = firebase.auth();
var doc1_likeCnt = 0;
var loginBoxID = "login_google";
var loginBoxHTML = `<button class="btn btn-dark">login Google</button>`
var userInfo = {};
var userToken = "";

export const makeLogoutBoxHTML = function (userName) {
    return `<button class="btn btn-dark">${userName} (logout)</button>`;
}

// firestorage 에 저장된 이미지 url 불러오기
export const loadImage = function (htmlId, imageName) {
    //var pathReference = storage.ref('xelloss.jpg');
    var gsReference = storage.refFromURL('gs://ysoftman-firebase.appspot.com/' + imageName)
    gsReference.getDownloadURL().then(function (url) {
        //console.log('File available at', url);
        document.getElementById(htmlId).innerHTML = '<img src="' + url + '"></img>';
    }).catch(function (error) {
        // Handle any errors
        console.error('download failed:', error);
    });
}


// firestore 테스트 문서 생성
export const setTestDoc = function (coll, doc) {
    db.collection(coll).doc(doc).set({
        name: doc,
        visitCnt: 0
    }).then(function () {
        console.log("Document written!");
    }).catch(function (error) {
        console.error("Error adding document: ", error);
    });
}

// firestore 테스트 방문카운트 및 조회
export const visitCnt = function (coll, doc, cntType, htmlId) {
   var docRef = db.collection(coll).doc(doc);
    // likeCnt 값을 읽어 1개 증가를 트랜젹션(원자적 읽기/쓰기)으로 처리한다.
    db.runTransaction(function (transaction) {
        // This code may get re-run multiple times if there are conflicts.
        return transaction.get(docRef).then(function (doc1) {
            if (!doc1.exists) {
                throw "Document doest not exist!";
            }
            var newCnt = doc1.data().visitCnt;
            if (checkLogin()) {
                newCnt += 1
                transaction.update(docRef, {
                    visitCnt: newCnt
                });
            }
            //console.log("htmlId:", htmlId, `doc1.data().name: ${doc1.data().name} visitCnt: ${newCnt}`)
            document.getElementById(htmlId).innerHTML = `${newCnt}`;
        });
    }).then(function () {
        console.log("Transaction successfully committed!");
    }).catch(function (error) {
        console.log("Transaction failed: ", error);
    });
}


// firestore 컬렉션(판교식당) 문서 생성
export const setRestaurantDoc = function (coll, doc) {
    db.collection(coll).doc(doc.name).set({
        name: doc.name,
        glyphicons: doc.glyphicons,
        location: doc.location,
        menu: doc.menu,
        detailInfo: doc.detailInfo,
        likeCntUsers: doc.likeCntUsers,
        dislikeCntUsers: doc.dislikeCntUsers,
        likeCnt: doc.likeCnt,
        dislikeCnt: doc.dislikeCnt
    }).then(function () {
        console.log("Document written!");
    }).catch(function (error) {
        console.error("Error adding document: ", error);
    });
}


// firestore 컬렉션(판교식당) 문서 필드 없데이트
export const updateRestaurantDoc = function (coll, doc) {
    // console.log("user.email:", user.email)
    // if (user.email == "") {
    //     return
    // }
    var docRef = db.collection(coll).doc(doc.name);
    db.runTransaction(function (transaction) {
        // This code may get re-run multiple times if there are conflicts.
        return transaction.get(docRef).then(function (doc1) {
            if (!doc1.exists) {
                throw "Document doest not exist!";
            }
            transaction.update(docRef, {
                name: doc.name,
                glyphicons: doc.glyphicons,
                location: doc.location,
                menu: doc.menu,
                detailInfo: doc.detailInfo
            });
            console.log("updateRestaurantDoc", doc)
        });
    }).then(function () {
        console.log("Transaction successfully committed!");
    }).catch(function (error) {
        console.log("Transaction failed: ", error);
    });
}

export const onLikeClick = function (doc, htmlId) {
    incRestaurantCnt(coll, doc, 'likeCnt', htmlId);
}

export const onDisLikeClick = function (doc, htmlId) {
    incRestaurantCnt(coll, doc, 'dislikeCnt', htmlId);
}

export const readRestaurantAll = function (coll) {
    // collection 전체 문서 가져오기
    // likeCnt 많은 순으로
    db.collection(coll).orderBy("likeCnt", "desc").get().then((querySnapshot) => {
        var html = `<div class="card-columns">`;
        querySnapshot.forEach((doc) => {
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
        <button type="button" onClick="onLikeClick('${doc.data().name}', '${doc.data().name}_좋아요')" class="btn btn-success"><div id='${doc.data().name}_좋아요'>좋아요 ${doc.data().likeCnt}</div></button>
        <button type="button" onClick="onDisLikeClick('${doc.data().name}', '${doc.data().name}_싫어요')" class="btn btn-danger"><div id='${doc.data().name}_싫어요'>싫어요 ${doc.data().dislikeCnt}</div></button>
    </p>
</div>
`
        });
        html += `</div>`
        document.getElementById('html_out').innerHTML = html;
        // console.log(html);
    });
}

// firestore 컬렉션(판교식당) 문서이름으로 읽기
export const readRestaurantCnt = function (coll, doc, cntType, htmlId) {
    // collection->doc1 하나만 가져오기
    // onSnapshot(콜백함수) 로 수신대기하면서 현재 내용(변수등)값들을 스냅샷(문서)으로 저장 한다.
    // 그리고 내용이 변경될때마다 콜백함수(문서가져오기)가 실행되어 스냅샷을 업데이트한다.
    // (주의) doc1_likeCnt++ 등변수값을 변경하게 되면 매번 내용이 변경되서 문서가져오기가 무한으로 수행돼 과금될 수 있다.
    db.collection(coll).doc(doc).onSnapshot(function (doc1) {
        console.log("Current data: ", doc1.data(), "->", htmlId);
        if (cntType == 'likeCnt') {
            document.getElementById(htmlId).innerHTML = `${doc1.data().likeCnt}`;
        } else if (cntType == 'dislikeCnt') {
            document.getElementById(htmlId).innerHTML = `${doc1.data().dislikeCnt}`;
        }
    });
}

// firestore 컬렉션(판교식당) 해당하는 문서 카운트 증가시키기
export const incRestaurantCnt = function (coll, doc, cntType, htmlId) {
    console.log("user.email:", user.email)
    if (user.email == "") {
        alert("로그인이 필요합니다.");
        return
    }
    var docRef = db.collection(coll).doc(doc);
    // likeCnt 값을 읽어 1개 증가를 트랜젹션(원자적 읽기/쓰기)으로 처리한다.
    db.runTransaction(function (transaction) {
        // This code may get re-run multiple times if there are conflicts.
        return transaction.get(docRef).then(function (doc1) {
            if (!doc1.exists) {
                throw "Document doest not exist!";
            }
            var newCnt = 0
            var incValue = 1;
            if (cntType == 'likeCnt') {
                var lcUsers = doc1.data().likeCntUsers;
                console.log("lcUsers", lcUsers)
                var pos = lcUsers.indexOf(user.email)
                // 좋아요를 이미 클릭한 사용자라면 카운트 취소하기
                if (pos >= 0) {
                    incValue = -1;
                    lcUsers.splice(pos, 1);
                } else {
                    lcUsers.push(user.email);
                }
                newCnt = doc1.data().likeCnt + incValue;
                transaction.update(docRef, {
                    likeCnt: newCnt,
                    likeCntUsers: lcUsers
                });
                console.log("incRestaurantCnt", htmlId, `${doc1.data().name} likeCnt: ${newCnt}`)
                document.getElementById(htmlId).innerHTML = `좋아요 ${newCnt}`;
            } else if (cntType == 'dislikeCnt') {
                var dlcUsers = doc1.data().dislikeCntUsers;
                console.log("dlcUsers", dlcUsers)
                var pos = dlcUsers.indexOf(user.email)
                // 싫어요를 이미 클릭한 사용자라면 카운트 취소하기
                if (pos >= 0) {
                    incValue = -1;
                    dlcUsers.splice(pos, 1);
                } else {
                    dlcUsers.push(user.email);
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
auth.onAuthStateChanged(function (user) {
    document.getElementById(loginBoxID).addEventListener("click", loginGoogle);
    if (user) {
        // User is signed in.
        //user.displayName;
        //user.email;
        //user.emailVerified;
        //user.photoURL;
        //user.isAnonymous;
        //user.uid;
        //user.providerData;
        userInfo = user;
        // ...
        var userName = user.displayName + " " + user.email
        document.getElementById(loginBoxID).innerHTML = makeLogoutBoxHTML(userName)
    } else {
        // User is signed out.
        userInfo = {};
        userToken = ""
        document.getElementById(loginBoxID).innerHTML = loginBoxHTML
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
            var errorCode = error.code;
            var errorMessage = error.message;
        });
}

// 로그인 후 토큰가져오기
export const getToken = function () {
    auth.currentUser.getIdToken(/* forceRefresh */ true).then(function (idToken) {
        // Send token to your backend via HTTPS
        // ...
        //console.log("idToken:", idToken)
        userToken = idToken
    }).catch(function (error) {
        // Handle error
    });
}

export const checkLogin = () => {
    console.log("userInfo: ", userInfo);
    if (userInfo.email != null && userInfo.email != "") {
        return true
    }
    return false
}

// 구글 로그인하기
export const loginGoogle = function () {
    if (checkLogin()) {
        logoutGoogle()
        return
    }
    var provider = new firebase.auth.GoogleAuthProvider();
    auth.signInWithPopup(provider).then(function (result) {
        // This gives you a Google Access Token. You can use it to access the Google API.
        userToken = result.credential.accessToken;
        // The signed-in user info.
        userInfo = result.user;
        // ...
        console.log("loginGoogle result.user:", result.user)
        var userName = result.user.displayName + " " + result.user.email
        document.getElementById(loginBoxID).innerHTML = makeLogoutBoxHTML(userName)
        // 사용자 토큰 파악해두기
        getToken()
        //GoogleLoginResult()
    }).catch(function (error) {
        // Handle Errors here.
        var errorCode = error.code;
        var errorMessage = error.message;
        // The email of the user's account used.
        var email = error.email;
        // The firebase.auth.AuthCredential type that was used.
        var credential = error.credential;
        alert("errCode:" + error.code +
            "\nerrMessage:" + error.message +
            "\nerrMail:" + error.mail)
    });

}

// 로그아웃
export const logoutGoogle = function () {
    auth.signOut()
    document.getElementById(loginBoxID).innerHTML = loginBoxHTML
    document.getElementById(loginBoxID).addEventListener("click", loginGoogle);
}

// 구글 로그인 이후 결과 정보
export const GoogleLoginResult = function () {
    auth.getRedirectResult().then(function (result) {
        if (result.credential) {
            // This gives you a Google Access Token. You can use it to access the Google API.
            userToken = result.credential.accessToken;
            // ...
        }
        // The signed-in user info.
        userInfo = result.user;
        console.log("GoogleLoginResult result.user:", result.user)
    }).catch(function (error) {
        // Handle Errors here.
        var errorCode = error.code;
        var errorMessage = error.message;
        // The email of the user's account used.
        var email = error.email;
        // The firebase.auth.AuthCredential type that was used.
        var credential = error.credential;
        // ...
    });
}


