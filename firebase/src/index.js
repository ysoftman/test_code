import {getFirestoreVisitCnt, getImageList, loadImages} from "./common.js"
getFirestoreVisitCnt("index", "ysoftman", "visitcnt")
const imgNames = await getImageList("")
// image div 태그를 구성해 이미지 순서를 보장
loadImages("images", imgNames)
