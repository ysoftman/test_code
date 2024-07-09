// ysoftman
// oop state pattern test
// 블로그의 포스트가 게시되기까지의 상태 관리하는 예제

struct Post {
    // 블로그 포스트 -> 초안 -> 리뷰 -> 게시 등의 상태를 나타내는 옵션 변수
    state: Option<Box<dyn State>>,
    content: String,
}
impl Post {
    fn new() -> Post {
        println!("초안 상태");
        Post {
            state: Some(Box::new(Draft {})),
            content: String::new(),
        }
    }
    // 포스트 내용 추가
    // self 가 변경되기 때문에 가변 인자(&mut self)를 사용한다.
    fn add_text(&mut self, text: &str) {
        self.content.push_str(text);
    }
    // 포스트 내용 보기
    fn content(&self) -> &str {
        // &self 로 부터 state 이동을 위해 as_ref() 로 Option 참조자 사용
        // unwrap() Option 값이 None 이라면 패닉 발생, 다른 포스트의 메소들은 state 가 항상 Some 을 보장하도록 했다.
        // Option 값이 Some 이면 현태 state 의 content() 메소드를 호출한다.
        self.state.as_ref().unwrap().content(&self)
    }

    // 포스트 리뷰
    fn request_review(&mut self) {
        // take() 는 state 로부터 Some()값을 리턴해주고 그 자리를 None으로 바꾼다.
        // 이렇게 self.state 상태를 갱신하고 이전 state 를 None 으로 만들어 하나의 State 를 유지한다.
        if let Some(s) = self.state.take() {
            self.state = Some(s.request_review())
        }
    }

    // 포스트 승인
    fn approve(&mut self) {
        if let Some(s) = self.state.take() {
            self.state = Some(s.approve())
        }
    }
}

// State(상태) 트레잇을 사용하기 위해서 트레잇내의 함수들을 구현해야 한다.
trait State {
    // Box<Self>로 Box 로 호출될경우만 유효, Box<Self>로 받는 인자의 소유권을 가져간다.
    // 이전 상태를 소비하기 위해서 Box<Self>로 state 값을 소유해야 한다.
    fn request_review(self: Box<Self>) -> Box<dyn State>;
    fn approve(self: Box<Self>) -> Box<dyn State>;

    // 디폴트로 content 는 빈 스트링을 리턴하도록 한다.
    // Post 참조중임으로 리턴 값도 Post 와 같은 라이브타임을 가져야 한다.
    fn content<'a>(&self, _post: &'a Post) -> &'a str {
        ""
    }
}

// 초안 상태
struct Draft {}
impl State for Draft {
    // Draft 상태에서 리뷰를 하면 PendingReview 상태로 변경한다.
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        println!("리뷰 상태로 변경");
        Box::new(PendingReview {})
    }
    // 초안 상태에서 승인을 해도 자신을 리턴함으로 상태 변화가 없도록 한다.
    fn approve(self: Box<Self>) -> Box<dyn State> {
        self
    }
}
// 리뷰를 가리는 상태
struct PendingReview {}
impl State for PendingReview {
    // PendingReview 에서 리뷰를 하면 상태 변화 없이 PendingReview 자신을 리턴한다.
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        self
    }
    // 리뷰 상태에서 승인하면 게시 상태로 변경한다.
    fn approve(self: Box<Self>) -> Box<dyn State> {
        println!("게시 상태로 변경");
        Box::new(Published {})
    }
}
// 게시 상태
struct Published {}
// 게시 상태는 마지막 상태로 리뷰, 승인을 해도 자신 상태(Published)그대로다.
impl State for Published {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        self
    }
    fn approve(self: Box<Self>) -> Box<dyn State> {
        self
    }
    // Published 상태에서만 content 를 리턴한다.
    fn content<'a>(&self, post: &'a Post) -> &'a str {
        &post.content
    }
}

fn main() {
    // 초안 상태
    let mut post = Post::new();
    post.add_text("포스트 내용");
    assert_eq!("", post.content());
    println!("content:{}", post.content());

    // 리뷰 상태로 변경
    post.request_review();
    assert_eq!("", post.content());
    println!("content:{}", post.content());

    // 게시 상태로 변경
    // 포스트를 승인하면 published 상태가 되고 publilshed 상태에서는 content() 로 포스트 내용을 볼 수 있다.
    post.approve();
    assert_eq!("포스트 내용", post.content());
    println!("content:{}", post.content());
}
