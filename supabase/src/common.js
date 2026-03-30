// ysoftman
import "./common.css"; // css, scss 중 마지막에 import 해야 올바르게 적용된다.
import { createClient } from "@supabase/supabase-js";
import { supabasePublishableKey, supabaseUrl } from "./supabase_config.js";

export const supabase = createClient(supabaseUrl(), supabasePublishableKey());

const loginBoxID = "login_google";
const loginAnonymousBoxID = "login_anonymous";

const makeLogoutBoxHTML = (userName) => {
  if (userName.length === 0) {
    return `Anonymous (logout)`;
  }
  return `${userName} (logout)`;
};

// 로그인한 사용자에 대한 정보가 필요한 앱 페이지마다 인증 상태 변경 리스너를 등록합니다.
// 사용자의 로그인 상태가 변경될 때마다 이 콜백이 호출됩니다.
supabase.auth.onAuthStateChange((_event, session) => {
  document.getElementById(loginBoxID).addEventListener("click", loginGoogle);
  document.getElementById(loginAnonymousBoxID).addEventListener("click", loginAnonymous);
  if (session?.user) {
    const user = session.user;
    console.log("user:", user);
    if (user.is_anonymous) {
      document.getElementById(loginAnonymousBoxID).innerHTML = makeLogoutBoxHTML("");
      return;
    }
    const userName = `${user.user_metadata?.full_name || ""} ${user.email || ""}`;
    document.getElementById(loginBoxID).innerHTML = makeLogoutBoxHTML(userName);
    document.getElementById(loginAnonymousBoxID).innerHTML = "login Anonymous";
  } else {
    // User is signed out.
  }
});

// supabase > authentication > 익명 로그인 활성화했음
const loginAnonymous = async () => {
  const {
    data: { user },
  } = await supabase.auth.getUser();
  if (user?.is_anonymous) {
    await logout();
    document.getElementById(loginAnonymousBoxID).innerHTML = "login Anonymous";
    return;
  }
  const { error } = await supabase.auth.signInAnonymously();
  if (error) {
    console.log("error: ", error);
    return;
  }
  document.getElementById(loginAnonymousBoxID).innerHTML = makeLogoutBoxHTML("");
  window.location.reload();
};

// 구글 로그인하기
const loginGoogle = async () => {
  const {
    data: { user },
  } = await supabase.auth.getUser();
  if (user?.email) {
    await logout();
    return;
  }
  const { error } = await supabase.auth.signInWithOAuth({
    provider: "google",
    options: {
      redirectTo: window.location.origin,
    },
  });
  if (error) {
    alert(`errCode:${error.code}\nerrMessage:${error.message}`);
  }
};

// 로그아웃
const logout = async () => {
  await supabase.auth.signOut();
  console.log("logout...");
  window.location.reload();
};
