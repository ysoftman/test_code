// ysoftman
// args test
// 빌드 및 테스트
// cargo run --  -o foo.txt -dvvvs 1337 -l alice -l bob --nb-cars 4 bar.txt baz.txt
// cargo build && ./target/debug/args -o foo.txt -dvvvs 1337 -l alice -l bob --nb-cars 4 bar.txt baz.txt

use std::path::PathBuf;
use structopt::StructOpt;

use std::env;
//  사용하지 않는 코드 warning 발생하지 않게 하는 attribute
#[allow(dead_code)]
fn main() {
    // 기본 env args 사용
    // map 내의 클로저에서 스트링으로 변환된것을 collect
    let args: Vec<String> = env::args().map(|x| x.to_string()).collect();
    println!("args.len(): {}", args.len());
    println!("args[0]: {}", args[0]);
    println!("args: {:?}", args);
    println!("args[1..]: {:?}", &args[1..]);
    println!("--------------------------");

    // strutopt crate 사용
    #[derive(StructOpt, Debug)]
    #[structopt(name = "basic")]
    // 여기에 cli 옵션(flag)으로 사용할 argument 를 명세한다.
    struct Opt {
        #[structopt(short, long)]
        debug: bool,

        // The number of occurrences of the `v/verbose` flag
        /// Verbose mode (-v, -vv, -vvv, etc.)
        #[structopt(short, long, parse(from_occurrences))]
        verbose: u8,

        /// Set speed
        #[structopt(short, long, default_value = "42")]
        speed: f64,

        /// Output file
        #[structopt(short, long, parse(from_os_str))]
        output: PathBuf,

        // the long option will be translated by default to kebab case,
        // i.e. `--nb-cars`.
        /// Number of cars
        #[structopt(short = "c", long)]
        nb_cars: Option<i32>,

        /// admin_level to consider
        #[structopt(short, long)]
        level: Vec<String>,
        // Files to process
        // - 가 없는 인자
        // #[structopt(name = "FILE", parse(from_os_str))]
        // files: Vec<PathBuf>,

        // - 가 없는 인자
        #[structopt(default_value = "lemon")]
        name1: String,
        // - 가 없는 인자
        #[structopt(default_value = "orange")]
        name2: String,
    }
    let opt = Opt::from_args();
    println!("{:#?}", opt);
    // -d --debug 플래그 지정 여부
    if opt.debug {
        println!("opt.debug: {}", opt.debug);
    }
    println!("opt.verbose: {}", opt.verbose);
    println!("opt.speed: {}", opt.speed);
    println!("opt.level: {:?}", opt.level);
    println!("opt.name1: {}", opt.name1);
    println!("opt.name2: {}", opt.name2);
}
