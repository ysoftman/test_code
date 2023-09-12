// new URL 로 파싱해 URL 오브젝트로 저장
function parseURL1(url) {
    try {
        let myURL = new URL(url)
        console.log("myURL", myURL)
    } catch (error) {
        console.error("myURL error", error)
    }
}
parseURL1("http://")
parseURL1("http://www.daum.net")
parseURL1("http://www.daum.net/a/b/c/")
parseURL1("http://www.daum.net/a/b/c/?a=1&b=2")
parseURL1("http://www.daum.net/a/b/c/?a=1&b=2&c=http://ysoftman.test.com")


parseURL2("http://")
parseURL2("http://www.daum.net")
parseURL2("http://www.daum.net/a/b/c")
parseURL2("http://www.daum.net/a/b/c?a=1&b=2")
parseURL2("http://www.daum.net/a/b/c?a=1&b=2&c=http://ysoftman.test.com")

// URL 구분해 보기
function parseURL2(url) {
    console.log("----- url -----", url)
    let index = url.indexOf("//")
    let protocol = url.slice(0, index)
    console.log("protocol:", protocol)

    let temp = url.slice(index + "//".length, )
    index = temp.indexOf("/")
    // host / 가 없는 경우 이후로는 없으니 끝낸다.
    if (index < 0) {
        let host = temp.slice(0, )
        console.log("host:", host)
        return
    }
    let host = temp.slice(0, index)
    console.log("host:", host)

    temp = temp.slice(index, )
    index = temp.indexOf("?")
    // path ? 가 없는 경우 이후로는 없으니 끝낸다.
    if (index < 0) {
        let path = temp.slice(0, )
        console.log("path:", path)
        return
    }
    let path = temp.slice(0, index)
    console.log("path:", path)

    let params = temp.slice(index, )
    console.log("params:", params)
}
