use tokio::task;
use tokio::time::{Duration, sleep};

// tokio는 비동기 I/O, 타이머, 태스크 스케줄링 등을 제공하며 async/await 문법과 함께 사용
#[tokio::main]
async fn main() {
    println!("tokio test...");
    // 쓰레드 대신 async 를 쓰는 이유
    // 쓰레드는 한계가 있지만, async는 경량 future(아직 완료되지 않는, 미래에 완료될 작업)로 관리 가능
    let task1 = task::spawn(async {
        // await(결과를 줄때까지  기다리기)
        sleep(Duration::from_secs(5)).await;
        println!("[task1] 5초 후 완료");
    });
    let task2 = task::spawn(async {
        sleep(Duration::from_secs(1)).await;
        println!("[task2] 1초 후 완료");
    });

    task1.await.expect("task1 fails");
    task2.await.expect("task2 fails");

    let n = num123().await;
    println!("num123:{n}");
}

// 비동기 함수, await 가 있는 위치에서 실행이 시작된다.(lazy 실행)
// Future<Output = i32> 를 반환(지금은 결과가 없지만 나중에 생길것이라는 의미)
async fn num123() -> i32 {
    sleep(Duration::from_secs(3)).await;
    println!("3초 후 완료 후 리턴");
    123
}
