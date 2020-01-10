extern crate rand;

use rand::Rng;

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}

pub fn add_ten(v: u32) -> u32 {
    v + 10
}

pub fn get_random_number() -> u32 {
    rand::thread_rng().gen_range(1, 101)
}
