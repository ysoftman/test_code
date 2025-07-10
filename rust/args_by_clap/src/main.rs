// https://docs.rs/clap/latest/clap/index.html
// cargo run -- -h
// cargo run -- --b 200 --c lemon
use clap::Parser;

#[derive(Parser, Debug)]
#[command(name = "myapp", version, about = "clap args test")]
struct MyArgs {
    // short (-x)
    // long (--xxx) 옵션 사용
    // default_value_t 타임포함 기본값
    #[arg(short, long = "aaa", default_value_t = true, help = "boolean value")]
    a: bool,

    #[arg(short, long, default_value_t = 100)]
    b: u32,

    #[arg(short, long, default_value = "ysoftman")]
    c: String,
}
fn main() {
    let args = MyArgs::parse();
    println!("args {:?}", args);
}
