// ysoftman
// struct test
// struct 이름은 carmal case 여야 한다.
// Area 를 {:?} 또는 {:#?} 로 디버깅 출력할 수 있도록 해주는 어노테이션
#[derive(Debug)]
struct User {
    name: String,
    email: String,
    cnt: u64,
    active: bool,
}

// 필드명 없이 타입만 명시한 tuple struct
// 튜플 처럼 () 를 사용해야 한다.
struct TupleUser(u32, String);

// Area 를 {:?} 또는 {:#?} 로 디버깅 출력할 수 있도록 해주는 어노테이션
#[derive(Debug)]
struct Area {
    width: u32,
    height: u32,
}
// struct 내에서 선언되고 사용되는 함수(메소스) 구현
impl Area {
    // 메소드는 항상 첫번째 파라미터로 self(sturct instance)를 사용해야 한다.
    // 메소드 호출시 self 를 명시하지는 않는다.
    // 메소드가 인스턴스의 대한 소유권을 가져 가지 않도록 참조(&)를 사용했다.
    // 메소스내에서 변경이 필요하면 $mut self 를 사용한다.
    fn get_area(&self) -> u32 {
        println!("self {:#?}", self);
        self.width * self.height
    }

    // 다른 area 가 이 area 내에 포함된는지 여부 판단하는 메소드
    fn can_hold(&self, other: &Area) -> bool {
        self.width > other.width && self.height > other.height
    }

    // self 갖지 않는 않지만 연관이 있는 함수도 impl 내에 정의 할 수 있고,
    // 이를 연관함수(associated function)라고 한다.
    // 새로운 width = height 은 새로운 Area 객체를 리턴한다.
    fn make_square(size: u32) -> Area {
        Area {
            width: size,
            height: size,
        }
    }
}
fn main() {
    // 구조체내의 모든 변수(필드)는 초기화 돼야 한다.
    let user1 = User {
        name: String::from("ysoftman"),
        email: String::from("ysoftman@email.com"),
        cnt: 99,
        active: true,
    };
    println!("{:?}", user1);
    // {:#?} 좀더 newline, indent 등으로 pretty 하게 출력한다.
    println!("{:#?}", user1);
    let user2 = make_user(&String::from("ysoftman2"), 123);
    println!("{:#?}", user2);

    let user3 = User {
        name: String::from("ysoftman3"),
        email: String::from("ysoftman3@email.com"),
        // 그밖의 필드들은 user1 값을 할당
        ..user1
    };
    println!("{:#?}", user3);
    // 만약 user3 에서 name, email 을 user1 을 사용하면
    // user3 로 move 되었기 때문에 여기서 사용할 수 없다.
    println!("{:#?}", user1);

    // tuple struct 생성및 사용
    let tuser1 = TupleUser(0, String::from("aaaa"));
    println!("{}", tuser1.0);
    println!("{}", tuser1.1);

    // tuple parameter 를 이용한 함수 호출
    // let width_height = (10, 20);
    println!("{} * {} = {}", 10, 20, calc_area1((10, 20)));

    // struct parameter 를 이용한 함수 호출
    let mut area1 = Area {
        width: 10,
        height: 20,
    };
    println!("area1 {:#?} -> {}", area1, calc_area2(&area1));
    area1.height = 30;
    println!("area1 {:#?} -> {}", area1, calc_area2(&area1));

    // Area 의 메소드 호출
    // [참고]
    // c++ 의 포인터객체의 메소드 호출시 사용되는 -> 는 rust 에는 없다.
    // rust 는 자동적으로 &, * 등을 붙여 메소드 시그니처와 맞도록 한다.
    println!("area1 {:#?} -> {}", area1, area1.get_area());

    // area 들간의 포함 여부 체크 메소스 호출
    let area2 = Area {
        width: 5,
        height: 5,
    };
    let area3 = Area {
        width: 50,
        height: 50,
    };
    println!("area2 {:#?} - {}", area2, area1.can_hold(&area2));
    println!("area3 {:#?} - {}", area3, area1.can_hold(&area3));

    // 연관함수 사실 메소든은 아니기 때문에 . 대신 호출은 :: 사용해야 한다.
    let sq = Area::make_square(50);
    println!("sq {:#?}", sq);
}

fn make_user(name: &String, cnt: u64) -> User {
    User {
        // name 필드는 String 인데 name 파라미터는 String 참조자라서
        // String 을 리턴하는 to_string()을 사용해한다.
        name: name.to_string(),
        // 구조내 필드명과 이름이 같은 파라미터는 필드명시 없이 바로 할당할 수 있다.
        cnt,
        active: true,
        // name 이 이미 User의 name 필드로 move 되어서 name 파라미터는 이제 사용할 수없다.
        email: name.clone(),
        // email: String::from("sample@ysoftman.com"),
    }
}

// 사각형 넓이 구하는 함수에서 width, height 두개의 파라미터를 각각 명시하는 대시
// () 튜플 파라미터로 전달
fn calc_area1(dimentions: (u32, u32)) -> u32 {
    dimentions.0 * dimentions.1
}

fn calc_area2(dimentions: &Area) -> u32 {
    dimentions.width * dimentions.height
}
