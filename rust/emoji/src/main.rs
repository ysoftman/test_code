// static 전역 메모리 상수로 슬라이스 참조 가능(고정 메모리 주소)
static EMOJI_UNICODE_RANGE: &[(u32, u32, bool)] = &[
    // 기본 이모지 유니코드 범위 (Unicode Emojis)
    (0x1F600, 0x1F64F, false), // 이모티콘
    (0x1F300, 0x1F5FF, false), // 그림 문자
    (0x1F680, 0x1F6FF, false), // 교통/지도
    (0x2600, 0x26FF, true),    // 기타 기호
    (0x2700, 0x27BF, true),    // (Dingbats)
    // nerd font
    (0x23fb, 0x23fe, true),   // Power Symbols
    (0x2665, 0x2665, true),   // Octicons
    (0xe000, 0xe00a, true),   // Pomicons
    (0xe0a0, 0xe0a2, true),   // Powerline Symbols
    (0xe0b0, 0xe0b3, true),   // Powerline Symbols
    (0xe0b4, 0xe0c8, true),   // Powerline Extra Symbols
    (0xe200, 0xe2a9, true),   // Font Awesome Extension
    (0xe600, 0xe6a6, true),   // Devicons
    (0xf0001, 0xf1af0, true), // Material Design Icons (v3+)
];
//
//const 컴파일타임에 정해지는 상수로 포인터,슬라이스 같은 참조는 제한(컴파일 타임에 치환된다=>인라인 상수로 삽입)
// const HACK_NERD_FONT_RANGES: [(u32, u32, bool); 5] = [
//     (0x1F600, 0x1F64F, false), // 이모티콘
//     (0x1F300, 0x1F5FF, false), // 그림 문자
//     (0x1F680, 0x1F6FF, false), // 교통/지도
//     (0x2600, 0x26FF, false),   // 기타 기호
//     (0x2700, 0x27BF, true),    // (Dingbats)
// ];

fn main() {
    println!("show emojis");
    for &(start, end, padding) in EMOJI_UNICODE_RANGE {
        println!("{:X} ~ {:X}", start, end);
        for emoji in start..=end {
            let ch = char::from_u32(emoji).unwrap();
            if padding {
                print!("{} ", ch)
            } else {
                print!("{}", ch)
            }
        }
        println!();
    }
}
