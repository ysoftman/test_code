; ysoftman
; x86 assembly hello assembly 출력
; 
; nasm -hf 로 f 옵션 값 보기
; 리눅스 기준
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
; nasm -f elf64 hello.asm -o hello.o && ld hello.o -o hello

; 맥 기준
; 어세블러 실행 ELF(Executable and Linkable Format) 파일 형식으로 오브젝트 파일 생성
; valid output formats for -f are (`*' denotes default):
;   * bin       flat-form binary files (e.g. DOS .COM, .SYS)
;     aout      Linux a.out object files
;     aoutb     NetBSD/FreeBSD a.out object files
;     coff      COFF (i386) object files (e.g. DJGPP for DOS)
;     elf       ELF32 (i386) object files (e.g. Linux)
;     as86      Linux as86 (bin86 version 0.3) object files
;     obj       MS-DOS 16-bit/32-bit OMF object files
;     win32     Microsoft Win32 (i386) object files
;     rdf       Relocatable Dynamic Object File Format v2.0
;     ieee      IEEE-695 (LADsoft variant) object file format
;     macho     NeXTstep/OpenStep/Rhapsody/Darwin/MacOS X object files
; 어셈블 및 링크
; -e 로 entrypoint 지정
; nasm -f macho hello.asm -o hello.o && ld hello.o -o hello -e _start
; 빌드는 되지만 문자열이 출력되지 않는다.???

global _start

; 여기서부터는 데이터 영역
section .data
msg: db "hello assembly", 0x0a
.len: equ $ - msg

; 여기서부터는 텍스트 영역
section .text

; 여기서 부터는 시작 영역
_start:
    ; eax = 4, sys_write 시스템콜 설정
    mov eax, 4
    ; ebx = 1, stdout file descriptor 설정
    mov ebx, 1
    ; ecx = msg, msg 내용 설정
    mov ecx, msg
    ; edx = len, msg 길이 설정
    mov edx, msg.len
    ; 0x80 인터럽트 발생 -> 시스템 콜 실행
    int 0x80
    ; eax = 1, sys_exit 시스템콜 설정
    mov eax, 1
    ; ebx = 0, exit 코드 0 설정
    mov ebx, 0
    ; 0x80 인터럽트 발생 -> 시스템 콜 실행
    int 0x80
