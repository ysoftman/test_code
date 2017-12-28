// helloworld 응답주는 http 서버
const http = require("http")
const server = http.createServer((req, res) => {
    res.statusCode = 200
    res.setHeader("Content-Type", "text/palin")
    res.write("hello world\n")
    // 1초후 end 응답 후 연결 종료
    setTimeout(function () {
        res.write("end\n")
        res.end()
    }, 1000)
});

const ip = "127.0.0.1"
// 80 포트를 사용하려면 EACCES 에러가 발생한다.
// Error: listen EACCES 127.0.0.1:80
// 1024 이전 까지의 포트는 root 권한으로 실행해아 한다.
// sudo node helloworld_http.js
// const port = 80
const port = 8080

server.listen(port, ip, () => {
    console.log(`server ${ip}:${port}`)
})