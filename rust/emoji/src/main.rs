// static 전역 메모리 상수로 슬라이스 참조 가능(고정 메모리 주소)
static EMOJI_UNICODE_RANGE: &[(u32, u32, bool)] = &[
    // 기본 이모지 유니코드 범위 (Unicode Emojis)
    (0x1F600, 0x1F64F, false), // 이모티콘
    (0x1F300, 0x1F5FF, false), // 그림 문자
    (0x1F680, 0x1F6FF, false), // 교통/지도
    (0x2600, 0x26FF, true),    // 기타 기호
    (0x2700, 0x27BF, true),    // (Dingbats)
    // nerd fonts code points
    // https://github.com/ryanoasis/nerd-fonts/wiki/Glyph-Sets-and-Code-Points
    (0x23fb, 0x23fe, true), // IEC Power Symbols
    (0x2665, 0x2665, true), // Octicons
    (0x26a1, 0x26a1, true), // Octicons
    (0x2b58, 0x2b58, true), // IEC Power Symbols
    (0xe000, 0xe00a, true), // Pomicons
    (0xe0a0, 0xe0a2, true), // Powerline
    (0xe0a3, 0xe0a3, true), // Powerline Extra
    (0xe0b0, 0xe0b3, true), // Powerline
    (0xe0b4, 0xe0c8, true), // Powerline Extra
    (0xe0ca, 0xe0ca, true), // Powerline Extra
    (0xe0cc, 0xe0d7, true), // Powerline Extra
    (0xe200, 0xe2a9, true), // Font Awesome Extension
    (0xe300, 0xe3e3, true), // Weather Icons
    (0xe5fa, 0xe6b7, true), // Seti-UI + Custom
    (0xe700, 0xe8ef, true), // Devicons
    (0xea60, 0xec1e, true), // Codicons
    (0xed00, 0xefce, true), //Font Awesome
    (0xf000, 0xf2ff, true), //Font Awesome
    (0xf300, 0xf381, true), // Font Logos
    (0xf400, 0xf533, true), // Octicons
    (0xf500, 0xfd46, true), // Material Design
                            // (0xf001, 0xf1af0, true), // Material Design // 터미널에서 출력이 제대로 안된다.
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
        println!("{:X} ~ {:X} : {}", start, end, (end - start) + 1);
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
