fn main() {
    // array 타입(고정 크기의 모두 같은 타입)
    let arr1 = [1, 2, 3, 4, 5];
    println!("arr1[0]:{}", arr1[0]);
    println!("arr1[1]:{}", arr1[1]);
    // &으로 배열 슬라이싱할 수 있다.
    // {:?} 로 n 개의 값 출력
    println!("&arr1[1..3]:{:?}", &arr1[1..3]);

    // array element 의 타입과 크기 지정
    let arr2: [f32; 3] = [1.0, 2.5, 3.7];
    println!("arr2:{:?}", arr2);
}
