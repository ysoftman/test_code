fn mul_number(one: i32, two: i32) -> i32 {
    let result = {
        let num = 2;
        num * one * two
    };
    //return result;
    // do not use ; if return value
    result
}

fn main() {
    let num = mul_number(3, 5);
    println!("num:{}", num)
}
