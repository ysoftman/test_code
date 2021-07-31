use ansi_term::Color::*;
use ansi_term::Style;
use std::io;
use std::str;

fn red(string: &str) {
    print!("{}", Style::new().bold().on(Black).fg(Red).paint(string));
}

fn green(string: &str) {
    print!("{}", Green.paint(string));
}
fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();
    stdin.read_line(&mut buf).unwrap();
    red(&buf);
    green(&buf);
}
