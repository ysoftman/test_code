use axum::{
    Json, Router,
    http::StatusCode,
    routing::{get, post},
};
// Serde는 "SERialize"와 "DEserialize"의 약어입니다
// "서-디" (Sir-dee): 많은 개발자들이 이 발음을 사용합니다. Serde의 원작자도 "sir-dee"라고 발음한다고 언급했습니다.
use serde::{Deserialize, Serialize};

// tokio의 발음은 일반적으로 "토-키-오" (Toe-key-oh) 입니다.
// 실제로 Tokio는 도쿄에서 영감을 받아 이름 지어진 것으로 알려져 있습니다.
#[tokio::main]
async fn main() {
    // initialize tracing
    tracing_subscriber::fmt::init();

    // build our application with a route
    let app = Router::new()
        // `GET /` goes to `root`
        .route("/", get(root))
        // `POST /users` goes to `create_user`
        .route("/users", post(create_user));

    // run our app with hyper, listening globally on port 3000
    let listener = tokio::net::TcpListener::bind("0.0.0.0:8080").await.unwrap();
    println!("start axum server...");
    axum::serve(listener, app)
        .await
        .expect("failed to start server");
}

// basic handler that responds with a static string
async fn root() -> &'static str {
    let msg = "hello";
    println!("[get] / ... response: {msg}");
    msg
}

async fn create_user(
    // this argument tells axum to parse the request body
    // as JSON into a `CreateUser` type
    Json(payload): Json<CreateUser>,
) -> (StatusCode, Json<User>) {
    println!("[post] /users ... request username: {}", payload.username);
    // insert your application logic here
    let user = User {
        id: 1337,
        username: payload.username,
    };

    // this will be converted into a JSON response
    // with a status code of `201 Created`
    (StatusCode::CREATED, Json(user))
}

// the input to our `create_user` handler
#[derive(Deserialize)]
struct CreateUser {
    // #[serde(rename = "userName")] // JSON 필드명 다르게 하고 매칭할때 사용
    username: String,
}

// the output to our `create_user` handler
#[derive(Serialize)]
struct User {
    id: u64,
    username: String,
}
