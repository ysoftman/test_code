// ysoftman
// trait test
// 트레잇(trait)은 다른 언어의 인터페이스와 비슷, 컴파일러에게 특정한 타입이 다른 타입과 공유할 수 있는 기능을 알려준다(명시한다).

// trait 정의
// Summarizable 동작을 하길 원하는 구조체들이 구현한다.
trait Summarizable {
    // 트레잇 메소드들
    // 시그니처로만 표현한 메소드는 각 구조체는 구현을 해야만 하는 강제성이 있다.(인터페이스,추상클래스 같은 느낌?)
    fn summary(&self) -> String;

    // 각 구조체가 구현을 하지 않아도 기본 기능을 사용할 수 있도록 할 수도 있다.
    // 각 구조체들이 summary 를 구현하면 그 메소드로 override 된다.
    fn base_summary(&self) -> String {
        // 여기서 get_author 를 사용해 get_author() 구현을 강제할 수 있다.
        format!("기본 summary, 작성자는 : {}", self.get_author())
    }

    fn get_author(&self) -> String;
}

struct News {
    title: String,
    author: String,
    content: String,
}

// news 에서 Summarizable 구현
impl Summarizable for News {
    fn summary(&self) -> String {
        format!(
            "{} - {}, by {}",
            self.title,
            self.author,
            &self.content[..6]
        )
    }
    fn get_author(&self) -> String {
        "ysoftman".to_string()
    }
}

struct Sns {
    date: String,
    username: String,
    content: String,
}

// sns 에서 Summarizable 구현
impl Summarizable for Sns {
    fn summary(&self) -> String {
        format!(
            "{} - {}, by {}",
            self.date,
            self.username,
            &self.content[..6]
        )
    }
    fn get_author(&self) -> String {
        self.username.clone()
    }
}

fn main() {
    let news = News {
        title: "타이틀".to_string(),
        author: "작성자".to_string(),
        content: "냉무, 아무내용 없음".to_string(),
    };
    let sns = Sns {
        date: "2020/01/01".to_string(),
        username: "ysoftman".to_string(),
        content: "냉무, 아무내용 없음".to_string(),
    };
    println!("{}", news.summary());
    println!("{}", news.base_summary());
    println!("{}", sns.summary());
    println!("{}", sns.base_summary());

    print_summary(news);
    print_summary(sns);
}

// Summarizable 를 구현한 구조체만 제약할 수 있다.(trait bounds)
fn print_summary<T: Summarizable>(item: T) {
    println!("--- {}", item.summary());
}

// 2개의 trait(aaa, bbb) 을 구현한 구조체 타입만 받을 수 있도록 하는 경우
// fn print_summary<T: aaa + bbb, T2 :bbb+ccc>(item1: T, item2: T2)  {
// 또는 where 로 표현할 수 도 있다.
// fn print_summary<T, T2>(item1: T, item2 : T2)
// where T : aaa+bbb, T2: aaa+ccc {
