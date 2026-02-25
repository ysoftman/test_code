// ysoftman
// oop inheritance 를 trait 으로 구현해 보기

// Draw 트레잇(일종의 인터페이스로)
trait Draw {
    fn draw(&self);
}

struct Screen {
    // Box<Draw> 타입의 components 벡터 정의
    // trait objects without an explicit `dyn` are deprecated
    // trait 오브젝트 사용할때는 dyn 을 명시하지 않으면 경고가 발생한다.
    pub components: Vec<Box<dyn Draw>>,
}
// 다음과 같이 제너릭을 이용하면 전부 Button 또는 전부 SelectBox 만 사용해야 한다.
// impl<T> Screen<T>
// where
//     T: Draw,
// Draw 트레잇을 만족(구현한)하는 어떤 타입도 Screen 을 사용할 수 있다.
// golang 의 duck typing 과 유사하다.
impl Screen {
    pub fn run(&self) {
        for component in self.components.iter() {
            component.draw();
        }
    }
}

struct Button {
    width: u32,
    height: u32,
    label: String,
}
// Button 에서 사용할 Draw 트레잇 내용 구현
impl Draw for Button {
    fn draw(&self) {
        println!("버튼 그리기 {} {} {}", self.width, self.height, self.label);
    }
}

struct SelectBox {
    width: u32,
    height: u32,
    options: Vec<String>,
}
// SelectBox 에서 사용할 Draw 트레잇 내용 구현
impl Draw for SelectBox {
    fn draw(&self) {
        println!(
            "선택상자 그리기 {} {} {:?}",
            self.width, self.height, self.options
        );
    }
}

fn main() {
    let screen = Screen {
        // SelectBox, Button 모두 Draw 트레잇을 구현해서 components 로 담을 수 있다.
        components: vec![
            Box::new(SelectBox {
                width: 75,
                height: 10,
                options: vec![
                    String::from("옵션1"),
                    String::from("옵션2"),
                    String::from("옵션3"),
                ],
            }),
            Box::new(Button {
                width: 50,
                height: 10,
                label: String::from("확인"),
            }),
        ],
    };

    screen.run();
}
