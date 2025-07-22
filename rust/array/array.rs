fn main() {
    // array 타입(고정 크기의 모두 같은 타입)
    // array는 추가,삭제 할 수 없다.
    let arr1 = [1, 2, 3, 4, 5];
    println!("arr1[0]:{}", arr1[0]);
    println!("arr1[1]:{}", arr1[1]);
    // 안전한 get 함수를 이용하면 없는 index값은 None으로 나온다.
    // get 함수 결과는 debug print 로 출력해야 한다.
    println!("arr1[1]:{:?}", arr1.get(2));
    println!("arr1[1]:{:?}", arr1.get(7));
    // &으로 배열 슬라이싱할 수 있다.
    // {:?} 로 n 개의 값 출력
    println!("&arr1[1..3]:{:?}", &arr1[1..3]);
    // 모든 원소 슬라이스
    println!("&arr1[..]:{:?}", &arr1[..]);
    // 2번째 부터 끝까지 슬라이싱
    println!("&arr1[2..]:{:?}", &arr1[2..]);
    // 0번째 부터 2번째까지 슬라이싱
    println!("&arr1[..3]:{:?}", &arr1[..3]);
    // 0번째 부터 3번째까지(3번째포함) 슬라이싱
    println!("&arr1[..=3]:{:?}", &arr1[..=3]);

    // array element 의 타입과 크기 지정
    let arr2: [f32; 3] = [1.0, 2.5, 3.7];
    println!("arr2:{arr2:?}");
    println!("arr2.len():{:?}", arr2.len());
    println!(
        "arr2 allocated memory size:{:?}",
        std::mem::size_of_val(&arr2)
    );

    // 0값 100개로 초기화
    let arr3 = [0; 100];
    println!("{arr3:?}")
}
