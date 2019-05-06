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


function loadImage(htmlId) {
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

var db = firebase.firestore();
var doc1_likeCnt = 0


function setTestDoc(coll, doc) {
    db.collection(coll).doc(doc).set({
        name: doc,
        visitCnt: 0
    }).then(function () {
        console.log("Document written!");
    }).catch(function (error) {
        console.error("Error adding document: ", error);
    });
}

function incTestVisitCnt(coll, doc, cntType, htmlId) {
    var docRef = db.collection(coll).doc(doc);
    // likeCnt 값을 읽어 1개 증가를 트랜젹션(원자적 읽기/쓰기)으로 처리한다.
    db.runTransaction(function (transaction) {
        // This code may get re-run multiple times if there are conflicts.
        return transaction.get(docRef).then(function (doc1) {
            if (!doc1.exists) {
                throw "Document doest not exist!";
            }
            var newCnt = doc1.data().visitCnt + 1;
            transaction.update(docRef, { visitCnt: newCnt });
            console.log("incTestVisitCnt", htmlId, `${doc1.data().name} visitCnt: ${newCnt}`)
            document.getElementById(htmlId).innerHTML = `${newCnt}`;
        });
    }).then(function () {
        console.log("Transaction successfully committed!");
    }).catch(function (error) {
        console.log("Transaction failed: ", error);
    });
}


function setRestaurantDoc(coll, doc) {
    db.collection(coll).doc(doc.name).set({
        name: doc.name,
        glyphicons: "",
        location: "",
        menu: "",
        detailInfo: "",
        likeCnt: 0,
        dislikeCnt: 0
    }).then(function () {
        console.log("Document written!");
    }).catch(function (error) {
        console.error("Error adding document: ", error);
    });
}


function readRestaurantAll(coll) {
    // collection 전체 문서 가져오기
    db.collection(coll).get().then((querySnapshot) => {
        querySnapshot.forEach((doc) => {
            console.log(doc.data().name);
            document.getElementById(doc.data().name + '_좋아요').innerHTML = `${doc.data().likeCnt}`;
            document.getElementById(doc.data().name + '_싫어요').innerHTML = `${doc.data().dislikeCnt}`;
        });
    });
}

function readRestaurantCnt(coll, doc, cntType, htmlId) {
    // collection->doc1 하나만 가져오기
    // onSnapshot(콜백함수) 로 수신대기하면서 현재 내용(변수등)값들을 스냅샷(문서)으로 저장 한다.
    // 그리고 내용이 변경될때마다 콜백함수(문서가져오기)가 실행되어 스냅샷을 업데이트한다.
    // (주의) doc1_likeCnt++ 등변수값을 변경하게 되면 매번 내용이 변경되서 문서가져오기가 무한으로 수행돼 과금될 수 있다.
    db.collection(coll).doc(doc).onSnapshot(function (doc1) {
        console.log("Current data: ", doc1.data(), "->", htmlId);
        if (cntType == 'likeCnt') {
            document.getElementById(htmlId).innerHTML = `${doc1.data().likeCnt}`;
        }
        else if (cntType == 'dislikeCnt') {
            document.getElementById(htmlId).innerHTML = `${doc1.data().dislikeCnt}`;
        }
    });
}

function incRestaurantCnt(coll, doc, cntType, htmlId) {
    var docRef = db.collection(coll).doc(doc);
    // likeCnt 값을 읽어 1개 증가를 트랜젹션(원자적 읽기/쓰기)으로 처리한다.
    db.runTransaction(function (transaction) {
        // This code may get re-run multiple times if there are conflicts.
        return transaction.get(docRef).then(function (doc1) {
            if (!doc1.exists) {
                throw "Document doest not exist!";
            }
            var newCnt = 0
            if (cntType == 'likeCnt') {
                newCnt = doc1.data().likeCnt + 1;
                transaction.update(docRef, { likeCnt: newCnt });
                console.log("increaseCnt", htmlId, `${doc1.data().name} likeCnt: ${newCnt}`)
                document.getElementById(htmlId).innerHTML = `${newCnt}`;
            }
            else if (cntType == 'dislikeCnt') {
                newCnt = doc1.data().dislikeCnt + 1;
                transaction.update(docRef, { dislikeCnt: newCnt });
                console.log("increaseCnt", htmlId, `${doc1.data().name} dislikeCnt: ${newCnt}`)
                document.getElementById(htmlId).innerHTML = `${newCnt}`;
            }
        });
    }).then(function () {
        console.log("Transaction successfully committed!");
    }).catch(function (error) {
        console.log("Transaction failed: ", error);
    });
}
