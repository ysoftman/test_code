import {getFirestoreVisitCnt, getImageList, loadImages} from "./common.js"
getFirestoreVisitCnt("index", "ysoftman", "visitcnt")

async function loadImg(path) {
    const imgNames = await getImageList(path)
    // image div 태그를 구성해 이미지 순서를 보장
    loadImages("images", imgNames)
}
loadImg("/funny")

document.getElementById("load_funny").addEventListener("click", ()=>{
    document.getElementById("images").innerHTML=""
    loadImg("/funny")
});
document.getElementById("load_wallpaper").addEventListener("click",()=>{
    document.getElementById("images").innerHTML=""
    loadImg("/wallpaper")
});

