// helloworld 응답주는 tcp 서버
// tcp 테스트
// curl -v tcp://localhost:8080
const tcp = require("net")
const server = tcp.createServer(function (conn) {
    conn.write("hello world~\n")
    conn.end()
});

const ip = "127.0.0.1"
const port = 8080

server.listen(port, ip, () => {
    console.log(`server ${ip}:${port}`)
})
