// ysoftman
// firebase api 사용
// Initialize Firebase
var config = {
    apiKey: "AIzaSyDNZCVxYjUU_-YrA-BNuLvYoYZBM_AWYU0",
    authDomain: "ysoftman-test.firebaseapp.com",
    databaseURL: "https://ysoftman-test.firebaseio.com",
    projectId: "ysoftman-test",
    storageBucket: "ysoftman-test.appspot.com",
    messagingSenderId: "366021551206"
};
firebase.initializeApp(config);

// Create a reference with an initial file path and name
var storage = firebase.storage();
var db = firebase.firestore();
var auth = firebase.auth();
var doc1_likeCnt = 0;
var loginBoxID = "google_login_result";
var loginText = `<button class="btn btn-dark" onClick="loginGoogle()">Google 로그인</button>`;
var userEmail = "";
var userToken = "";

var makeLogoutText = function (userName) {
    return `<button class="btn btn-dark" onClick="logout()">${userName} (로그아웃)</button>`;
}

// firestorage 에 저장된 이미지 url 불러오기
var loadImage = function (htmlId) {
    //var pathReference = storage.ref('xelloss.jpg');
    var gsReference = storage.refFromURL('gs://ysoftman-test.appspot.com/xelloss.jpg')
    gsReference.getDownloadURL().then(function (url) {
        //console.log('File available at', url);
        document.getElementById(htmlId).innerHTML = '<img src="' + url + '"></img>';
    }).catch(function (error) {
        // Handle any errors
        console.error('download failed:', error);
    });
}


// firestore 테스트 문서 생성
var setTestDoc = function (coll, doc) {
    db.collection(coll).doc(doc).set({
        name: doc,
        visitCnt: 0
    }).then(function () {
        console.log("Document written!");
    }).catch(function (error) {
        console.error("Error adding document: ", error);
    });
}

// firestore 테스트 방문카운트
var incTestVisitCnt = function (coll, doc, cntType, htmlId) {
    var docRef = db.collection(coll).doc(doc);
    // likeCnt 값을 읽어 1개 증가를 트랜젹션(원자적 읽기/쓰기)으로 처리한다.
    db.runTransaction(function (transaction) {
        // This code may get re-run multiple times if there are conflicts.
        return transaction.get(docRef).then(function (doc1) {
            if (!doc1.exists) {
                throw "Document doest not exist!";
            }
            var newCnt = doc1.data().visitCnt + 1;
            transaction.update(docRef, {
                visitCnt: newCnt
            });
            console.log("incTestVisitCnt", htmlId, `${doc1.data().name} visitCnt: ${newCnt}`)
            document.getElementById(htmlId).innerHTML = `${newCnt}`;
        });
    }).then(function () {
        console.log("Transaction successfully committed!");
    }).catch(function (error) {
        console.log("Transaction failed: ", error);
    });
}


// firestore 컬렉션(판교식당) 문서 생성
var setRestaurantDoc = function (coll, doc) {
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
var updateRestaurantDoc = function (coll, doc) {
    // console.log("userEmail:", userEmail)
    // if (userEmail == "") {
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

var onLikeClick = function (doc, htmlId) {
    incRestaurantCnt(coll, doc, 'likeCnt', htmlId);
}

var onDisLikeClick = function (doc, htmlId) {
    incRestaurantCnt(coll, doc, 'dislikeCnt', htmlId);
}

var readRestaurantAll = function (coll) {
    // collection 전체 문서 가져오기
    db.collection(coll).get().then((querySnapshot) => {
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
var readRestaurantCnt = function (coll, doc, cntType, htmlId) {
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
var incRestaurantCnt = function (coll, doc, cntType, htmlId) {
    console.log("userEmail:", userEmail)
    if (userEmail == "") {
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
                var pos = lcUsers.indexOf(userEmail)
                // 좋아요를 이미 클릭한 사용자라면 카운트 취소하기
                if (pos >= 0) {
                    incValue = -1;
                    lcUsers.splice(pos, 1);
                } else {
                    lcUsers.push(userEmail);
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
                var pos = dlcUsers.indexOf(userEmail)
                // 싫어요를 이미 클릭한 사용자라면 카운트 취소하기
                if (pos >= 0) {
                    incValue = -1;
                    dlcUsers.splice(pos, 1);
                } else {
                    dlcUsers.push(userEmail);
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
    if (user) {
        // User is signed in.
        var displayName = user.displayName;
        var email = user.email;
        var emailVerified = user.emailVerified;
        var photoURL = user.photoURL;
        var isAnonymous = user.isAnonymous;
        var uid = user.uid;
        var providerData = user.providerData;
        // ...
        userEmail = user.email
        var userName = user.displayName + " " + user.email
        document.getElementById(loginBoxID).innerHTML = makeLogoutText(userName)
    } else {
        // User is signed out.
        // ...
        userEmail = ""
        userToken = ""
        document.getElementById(loginBoxID).innerHTML = loginText
    }
});

// 로그인 유지설정(필요한 경우에만 호출)
var setAuthPersistence = function () {
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
var getToken = function () {
    auth.currentUser.getIdToken(/* forceRefresh */ true).then(function (idToken) {
        // Send token to your backend via HTTPS
        // ...
        // console.log("idToken:", idToken)
        userToken = idToken
    }).catch(function (error) {
        // Handle error
    });
}

// 구글 로그인하기
var loginGoogle = function () {
    var provider = new firebase.auth.GoogleAuthProvider();

    auth.signInWithPopup(provider).then(function (result) {
        // This gives you a Google Access Token. You can use it to access the Google API.
        var token = result.credential.accessToken;
        // The signed-in user info.
        var user = result.user;
        // ...
        console.log("loginGoogle result.user:", result.user)
        var userName = result.user.displayName + " " + result.user.email
        document.getElementById(loginBoxID).innerHTML = makeLogoutText(userName)
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
var logout = function () {
    auth.signOut()
    document.getElementById(loginBoxID).innerHTML = loginText
}

// 구글 로그인 이후 결과 정보
var GoogleLoginResult = function () {
    auth.getRedirectResult().then(function (result) {
        if (result.credential) {
            // This gives you a Google Access Token. You can use it to access the Google API.
            var token = result.credential.accessToken;
            // ...
        }
        // The signed-in user info.
        var user = result.user;
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
