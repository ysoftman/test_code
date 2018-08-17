; ysoftman
; x86 assembly hello assembly 출력
;
; nasm 설치
; sudo yum install nasm
; brew install nasm
;
; 어셈블러 옵션 참고
; nasm -h
;
; nasm -hf 로 f 옵션 값 보기
;   * bin       flat-form binary files (e.g. DOS .COM, .SYS)
;     ith       Intel hex
;     srec      Motorola S-records
;     aout      Linux a.out object files
;     aoutb     NetBSD/FreeBSD a.out object files
;     coff      COFF (i386) object files (e.g. DJGPP for DOS)
;     elf32     ELF32 (i386) object files (e.g. Linux)
;     elf64     ELF64 (x86_64) object files (e.g. Linux)
;     elfx32    ELFX32 (x86_64) object files (e.g. Linux)
;     as86      Linux as86 (bin86 version 0.3) object files
;     obj       MS-DOS 16-bit/32-bit OMF object files
;     win32     Microsoft Win32 (i386) object files
;     win64     Microsoft Win64 (x86-64) object files
;     rdf       Relocatable Dynamic Object File Format v2.0
;     ieee      IEEE-695 (LADsoft variant) object file format
;     macho32   NeXTstep/OpenStep/Rhapsody/Darwin/MacOS X (i386) object files
;     macho64   NeXTstep/OpenStep/Rhapsody/Darwin/MacOS X (x86_64) object files
;     dbg       Trace of all info passed to output stage
;     elf       ELF (short name for ELF32)
;     macho     MACHO (short name for MACHO32)
;     win       WIN (short name for WIN32)
; 어셈블 및 링크
; -e 로 entrypoint 지정
; 기본으로 설치된 /usr/bin/nasm 버전대신 brew 로 설치한 nasm 사용
; /usr/local/bin/nasm -f macho64 hello.mac.asm -o hello.o && ld hello.o -o hello -e start

global start

; 여기서부터는 데이터 영역
section .data
msg: db "hello assembly", 0x0a ; 0x0a(10) LF
.len: equ $ - msg

; 여기서부터는 텍스트(source code) 영역
section .text

; 여기서 부터는 시작 루틴
start:
    mov     rax, 0x2000004
    mov     rdi, 1
    mov     rsi, msg
    mov     rdx, msg.len
    syscall
    mov     rax, 0x2000001
    mov     rdi, 0
    syscall
