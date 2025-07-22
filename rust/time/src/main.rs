// ysoftman
// time test
extern crate chrono;
use chrono::prelude::*;
use chrono::{DateTime, Local, TimeZone, Utc};
use std::thread;
use std::time::{Duration, SystemTime};

fn main() {
    for i in 1..=3 {
        thread::sleep(Duration::from_secs(1));
        println!("{i} sec...");
    }

    // 현재시간(unix epoch time)
    let now = SystemTime::now()
        .duration_since(SystemTime::UNIX_EPOCH)
        .unwrap();
    println!("unix time sec: {}", now.as_secs());
    println!("unix time milli sec: {}", now.as_millis());
    println!("unix time micro sec: {}", now.as_micros());
    println!("unix time nano sec: {}", now.as_nanos());

    // chrono 사용
    // UTC 현재시간
    let now = Utc::now();
    println!("UTC now {now}");
    println!("UTC now.to_rfc2822() {}", now.to_rfc2822());
    println!("UTC now.to_rfc3339() {}", now.to_rfc3339());
    println!("UTC now.timezone() {}", now.timezone());
    // date() deprecated
    // println!("UTC now.date() {}", now.date());
    println!("UTC now.date_naive() {}", now.date_naive());
    println!("UTC now.date() {}", now.hour());
    let (is_pm, hour) = now.hour12();
    println!(
        "UTC {} {:02} {:02} {:02}",
        if is_pm { "pm" } else { "am" },
        hour,
        now.minute(),
        now.second()
    );
    // local 현재시간
    let now = Local::now();
    let (is_pm, hour) = now.hour12();
    println!(
        "Local {} {:02} {:02} {:02}",
        if is_pm { "pm" } else { "am" },
        hour,
        now.minute(),
        now.second()
    );

    // 날짜 스트링으로 부터 datetime 파싱 방법1
    println!(
        "{:?}",
        // Local.datetime_from_str("Fri Nov 28 12:00:09 2014", "%a %b %e %T %Y") // deprecated
        DateTime::parse_from_str("Fri Nov 28 12:00:09 2014", "%a %b %e %T %Y")
    );
    // 날짜 스트링으로 부터 datetime 파싱 방법2
    println!(
        "{:?}",
        DateTime::parse_from_str("2014-11-28 21:00:09 +09:00", "%Y-%m-%d %H:%M:%S %z")
    );
    println!(
        "{:?}",
        DateTime::parse_from_rfc2822("Fri, 28 Nov 2014 21:00:09 +0900")
    );
    println!(
        "{:?}",
        DateTime::parse_from_rfc3339("2014-11-28T21:00:09+09:00")
    );

    // 특정 날짜 생성
    // let dt = Utc.ymd(2014, 11, 28).and_hms(12, 0, 9); // deprecated
    let dt = Utc.with_ymd_and_hms(2014, 11, 28, 12, 0, 9).unwrap();
    println!("dt {dt:?}");
    println!("dt.year() {}", dt.year());
    println!("dt.month() {}", dt.month());
    // println!("dt.date() {}", dt.date()); // deprecated
    println!("dt.date() {}", dt.date_naive());
    println!("dt.hour() {}", dt.hour());

    // unix epoch -> datetime
    let unix_sec = Local::now().timestamp();
    println!("unix sec {unix_sec}");
    // 첫번째 인자는 sec, 두번재 인자는 nano sec
    // let dt = Utc.timestamp(unix_sec, 0);
    let dt = Utc.timestamp_opt(unix_sec, 0).unwrap();
    println!("dt from timestamp {dt:?}");
    // 현재 로컬 타임존 기준으로 출력
    println!(
        "dt from timestamp {:?}",
        dt.with_timezone(&Local::now().timezone())
    );
}
