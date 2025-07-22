use std::sync::mpsc;
use std::sync::Arc;
use std::sync::Mutex;
use std::thread;

enum Message {
    NewJob(Job),
    Terminate,
}
// ThreadPool 구현
pub struct ThreadPool {
    workers: Vec<Worker>,
    sender: mpsc::Sender<Message>,
}
impl ThreadPool {
    pub fn new(size: usize) -> ThreadPool {
        assert!(size > 0);

        // 쓰레드풀은 채널을 통해 워커와 통한다.
        let (sender, receiver) = mpsc::channel();
        // 채널은 여러개의 producer(sender), 한개의 consumer(receiver)로 사용된다.
        // 따라서 receiver 를 모든 쓰레드에서 공유하기 위해
        // Arc(Atomic Reference Counting)-뮤텍스로 receiver 를 사용한다.
        let receiver = Arc::new(Mutex::new(receiver));
        // 워커(쓰레드)들이 저장된 벡터 공간 할당
        // with_capacity() 미리 벡터 공간을 할당 할 수 있다.
        let mut workers = Vec::with_capacity(size);

        // size 만큰 워커들 생성해서 workers 에 저장
        for id in 0..size {
            // 워커가 생성될때 Job 을 전달받기 위해 receiver 를 알려준다.
            // Arc::Clone 으로 워커가 receiver 에 대한 복수 소유권을 갖도록 한다.
            workers.push(Worker::new(id, Arc::clone(&receiver)));
        }
        // 쓰레드풀은 워커에게 Job 을 전달해주는 sender 를 가지고 있다.
        ThreadPool { workers, sender }
    }

    // thread::spawn 구현체와 비슷하게 구현한다.
    // F 라는 제너릭 매개변수는 클로저를 받게되고
    // F 아래와 같은 조건이어야 한다.
    pub fn execute<F>(&self, f: F)
    where
        F: FnOnce() + Send + 'static,
    {
        // 수행할 잡을 생성하고
        let job = Box::new(f);
        // 송신자를 통해 채널로 보낸다.(워커들 중 하나가 receiver로 잡을 전달 받는다.)
        self.sender.send(Message::NewJob(job)).unwrap();
    }
}
// ThreadPool 종료시 생성된 워커들내 쓰레드 종료시키기
impl Drop for ThreadPool {
    fn drop(&mut self) {
        println!("sending terminate message to all workers.");

        // 모든 워커들에게 종료 메시지 전달
        for _ in &mut self.workers {
            self.sender.send(Message::Terminate).unwrap();
        }
        // 모든 워커들의 쓰레드 종료
        for worker in &mut self.workers {
            println!("shutting down worker : {}", worker.id);

            // join() 은 인수의 소유권을 필요로 하기 때문에 바로 워커내 쓰레드는 join() 할 수 없다.
            // worker.thread.join().unwrap();
            // 따라서 take() 로 Some() variant 값은 빼내고 None 으로 변경하고
            // 빼낸 thread 로 join() 을 수행한다.
            if let Some(thread) = worker.thread.take() {
                thread.join().unwrap();
            }
        }
    }
}

struct Worker {
    id: usize,
    thread: Option<thread::JoinHandle<()>>,
}
impl Worker {
    fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Message>>>) -> Worker {
        let thread = thread::spawn(move || {
            // 워커 쓰레드 잡을 처리 후에도 계속 사용하기 위해 무한 루프로 수행된다.
            loop {
                // 공유중인 receiver() 를 접근되고 잡을 수신(전달) 받는다.
                // lock()은 워커들이 공유중인 receiver 에 오직 하나의 워커 쓰레드 접근 보장을 위함
                // recv()는 채널로 수신을 위함, 수신이 있을때까지 대기
                let message = receiver.lock().unwrap().recv().unwrap();
                // 새로운 잡 또는 종료 메시지
                match message {
                    Message::NewJob(job) => {
                        println!("Worker {id} got a job and executing.");
                        // 전달 받은 잡 실행
                        // 아래와 같이 호출해서 사용할 수 없어
                        // (*job)();
                        // 별도의 FnBox 트레잇 및 구현해서 사용해야 한다.
                        job.call_box();
                    }
                    Message::Terminate => {
                        println!("Worker {id} terminating.");
                        break;
                    }
                }
            }
        });
        Worker {
            id,
            thread: Some(thread),
        }
    }
}

type Job = Box<dyn FnBox + Send + 'static>;

trait FnBox {
    fn call_box(self: Box<Self>);
}
impl<F: FnOnce()> FnBox for F {
    fn call_box(self: Box<F>) {
        (*self)()
    }
}
