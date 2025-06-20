# axum(web application framework) test

```bash
# cargo add axum tracing tracing-subscriber
# cargo add serde --features derive
# cargo add tokio --features full
# cargo install cargo-watch

# 로컬 개발시 코드 수정시 자동 실행
cargo watch -x run

# 서버 동작 확인
curl http://localhost:8080
curl -X POST http://localhost:8080/users \
-H "Content-Type: application/json" \
-d '{"username":"ysoftman"}'
```
