// ysoftman
// use test

mod lemon {
    pub mod apple {
        pub mod orange {
            pub fn juice() {
                pritnln!("orange juice!");
            }
        }
    }
}

fn main() {
    lemon::apple::orange::juice();
}
