// ysoftman
import "./common.css"; // css, scss 중 마지막에 import 해야 올바르게 적용된다.
import { webApiKey } from "./web_api_key.js";
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

const firebaseConfig = {
  apiKey: webApiKey(),
  authDomain: "ysoftman-firebase.firebaseapp.com",
  databaseURL: "https://ysoftman-firebase.firebaseio.com",
  projectId: "ysoftman-firebase",
  storageBucket: "ysoftman-firebase.appspot.com",
  messagingSenderId: "",
};

const firebase = initializeApp(firebaseConfig);
const auth = getAuth();
const loginBoxID = "login_google";
const loginAnonymousBoxID = "login_anonymous";

export const makeLogoutBoxHTML = function (userName) {
  if (userName.length == 0) {
    return `Anonymous (logout)`;
  }
  return `${userName} (logout)`;
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
