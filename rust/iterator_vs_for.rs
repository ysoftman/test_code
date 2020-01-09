// ysoftman
// iterator vs for
// iterator(반복자)는 컴파일되서 어셈블리코드가 생성되면 loop unrolling 되어 for 이상으로 빠르다.
// loop unrolling - 반복문을 쓰지 않고 반복만큼 코드를 반복(풀어)시킨다.
// for i<10; i++ {
//     dosomething;
// }
// 을 loop unrolling 하면
// dosomething; ... 10 번 명시하게 된다.
// 루프 마다 조건을 검사하는 오버헤드를 줄여 속도를 빠르게 할 수 있는 장점이 있지만
// 코드 사이즈가 커지고 unrolling 후 가독성이 떨어진다.
fn main() {
    let v1: Vec<u32> = (0..100).collect();
    // iter()반복자로 각 요소마다 1더하기
    let result: Vec<u32> = v1.iter().map(|a| a + 1).collect();
    println!("{:?}", result);
}
