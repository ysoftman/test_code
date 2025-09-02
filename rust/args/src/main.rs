// ysoftman
// args test
// 빌드 및 테스트
// cargo run --  -o foo.txt -dvvvs 1337 -l alice -l bob --nb-cars 4 bar.txt baz.txt
// cargo build && ./target/debug/args -o foo.txt -dvvvs 1337 -l alice -l bob --nb-cars 4 bar.txt baz.txt

use std::path::PathBuf;
// structopt 는 한때 표준처럼 쓰였지만, 현재는 유지보수 중단 상태입니다.
// clap 3.x 버전에 structopt 기능이 통합되었기 때문에 더 이상 쓸 필요가 없습니다.
// use structopt::StructOpt;
use clap::{ArgAction, Parser};
use std::env;

//  사용하지 않는 코드 warning 발생하지 않게 하는 attribute
#[allow(dead_code)]
fn main() {
    // 기본 env args 사용
    // map 내의 클로저에서 스트링으로 변환된것을 collect
    let args: Vec<String> = env::args().map(|x| x.to_string()).collect();
    println!("args.len(): {}", args.len());
    println!("args[0]: {}", args[0]);
    println!("args: {args:?}");
    println!("args[1..]: {:?}", &args[1..]);
    println!("--------------------------");

    // structopt crate 사용(보안 취약점 있는 atty 사용하고, 유지보수 안되고 있어 사용않는다.)
    // #[derive(StructOpt, Debug)]
    // #[structopt(name = "basic")]
    // 여기에 cli 옵션(flag)으로 사용할 argument 를 명세한다.
    // struct Opt {
    //     #[structopt(short, long)]
    //     debug: bool,
    //
    //     // The number of occurrences of the `v/verbose` flag
    //     /// Verbose mode (-v, -vv, -vvv, etc.)
    //     #[structopt(short, long, parse(from_occurrences))]
    //     verbose: u8,
    //
    //     /// Set speed
    //     #[structopt(short, long, default_value = "42")]
    //     speed: f64,
    //
    //     /// Output file
    //     #[structopt(short, long, parse(from_os_str))]
    //     output: PathBuf,
    //
    //     // the long option will be translated by default to kebab case,
    //     // i.e. `--nb-cars`.
    //     /// Number of cars
    //     #[structopt(short = "c", long)]
    //     nb_cars: Option<i32>,
    //
    //     /// admin_level to consider
    //     #[structopt(short, long)]
    //     level: Vec<String>,
    //     // Files to process
    //     // - 가 없는 인자
    //     // #[structopt(name = "FILE", parse(from_os_str))]
    //     // files: Vec<PathBuf>,
    //
    //     // - 가 없는 인자
    //     #[structopt(default_value = "lemon")]
    //     name1: String,
    //     // - 가 없는 인자
    //     #[structopt(default_value = "orange")]
    //     name2: String,
    // }
    // clap crate 사용
    #[derive(Parser, Debug)]
    #[command(name = "basic")]
    struct Opt {
        // short 인자 사용 -d
        // long : kebab-case 스타일의 long 인자 사용 --debug
        #[arg(short, long)]
        debug: bool,

        // The number of occurrences of the `v/verbose` flag
        // Verbose mode (-v, -vv, -vvv, etc.)
        // v의 사용회에 따라 레벨 차이날 수 있도록
        #[arg(short, long, action = ArgAction::Count)]
        verbose: u8,

        // Set speed
        #[arg(short, long, default_value = "42")]
        speed: f64,

        // Output file
        // PathBuf, OsString 같은 타입들은 clap 이 기본적으로 지원하는 파서가 있어서
        // 그냥value_parser 만 적어주면 된다.
        #[arg(short, long, value_parser)]
        output: PathBuf,

        // the long option will be translated by default to kebab case,
        // short = 'c'  -c 10
        // long 자동 생성 --nb-cars 10
        #[arg(short = 'c', long)]
        nb_cars: Option<i32>,

        /// admin_level to consider
        #[arg(short, long)]
        level: Vec<String>,
        // Files to process
        // - 가 없는 인자
        // #[structopt(name = "FILE", parse(from_os_str))]
        // files: Vec<PathBuf>,

        // - 가 없는 인자
        #[arg(default_value = "lemon")]
        name1: String,
        // - 가 없는 인자
        #[arg(default_value = "orange")]
        name2: String,
    }

    // let opt = Opt::from_args();  // structopt 사용시
    let opt = Opt::parse();
    println!("{opt:#?}");
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
