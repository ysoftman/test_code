// author : ysoftman
// encoding : utf-8
// title : 간단한 프로세스 성능 모니터링(현재 윈도우환경만 지원)
package main

import "fmt"
import "runtime"
import "os"
import "log"
import "time"
import "syscall"
import "unsafe"

// Windows 원형 값들
//#define TH32CS_SNAPPROCESS  0x00000002
//typedef unsigned long       DWORD;
//typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;
//typedef char CHAR;
//typedef long LONG;
//#define MAX_PATH          260
//typedef struct tagPROCESSENTRY32
//{
//    DWORD   dwSize;
//    DWORD   cntUsage;
//    DWORD   th32ProcessID;          // this process
//    ULONG_PTR th32DefaultHeapID;
//    DWORD   th32ModuleID;           // associated exe
//    DWORD   cntThreads;
//    DWORD   th32ParentProcessID;    // this process's parent process
//    LONG    pcPriClassBase;         // Base priority of process's threads
//    DWORD   dwFlags;
//    CHAR    szExeFile[MAX_PATH];    // Path
//} PROCESSENTRY32;

const TH32CS_SNAPPROCESS int32 = 0x2
const MAX_PATH int32 = 260

type PROCESSENTRY32 struct {
	dwSize              uint32
	cntUsage            uint32
	th32ProcessID       uint32
	th32DefaultHeapID   uintptr
	th32ModuleID        uint32
	cntThreads          uint32
	th32ParentProcessID uint32
	pcPriClassBase      int32
	dwFlags             uint32
	szExeFile           [MAX_PATH]uint16
}

type PROCESSENTRY32_FOR_PRINT struct {
	dwSize              uint32
	cntUsage            uint32
	th32ProcessID       uint32
	th32DefaultHeapID   uintptr
	th32ModuleID        uint32
	cntThreads          uint32
	th32ParentProcessID uint32
	pcPriClassBase      int32
	dwFlags             uint32
	szExeFile           string
}

// 윈도우 커닐 시스템콜 사용을 위해
// 참고로 64bit 환경에서도 kernel32.dll 을 사용한다.
// kernel32 에서 사용할 프로세스 관련 시스템콜
var kernel = syscall.NewLazyDLL("kernel32.dll")
var CreateToolhelp32Snapshot = kernel.NewProc("CreateToolhelp32Snapshot")

//var Process32First = kernel.NewProc("Process32First")
//var Process32Next = kernel.NewProc("Process32Next")
// 명령줄을 UTF16ToString 로 변환하기위기해 WideChar(유니코드2바이트) 함수를 사용한다.
var Process32First = kernel.NewProc("Process32FirstW")
var Process32Next = kernel.NewProc("Process32NextW")
var CloseHandle = kernel.NewProc("CloseHandle")

func main() {

	fmt.Println("Start simplePf...")

	// 측정 결과를 저장할 파일
	fp, err := os.Create("pf.log")
	if err != nil {
		// Fatal 은 os.Exit(1) 호출함
		log.Fatal("fail to create log file.")
		// Fatal 은 os.Exit(1) 호출함
		//os.Exit(1)
	}
	defer fp.Close()

	//	fmt.Println("runtime version = ", runtime.Version())
	fmt.Println("Num of CPUs = ", runtime.NumCPU())

	hProcessSnap, _, _ := CreateToolhelp32Snapshot.Call(uintptr(TH32CS_SNAPPROCESS), 0)
	if hProcessSnap < 0 {
		syscall.GetLastError()
		log.Fatal("fail to call CreateToolhelp32Snapshot")
		// Fatal 은 os.Exit(1) 호출함
		//os.Exit(1)
	}
	defer CloseHandle.Call(hProcessSnap)

	var pi PROCESSENTRY32
	// 사용하기 전 프로세스 정보가 담길 구조체 크기 설정해야함
	pi.dwSize = uint32(unsafe.Sizeof(pi))

	// https://msdn.microsoft.com/ko-kr/library/windows/desktop/ms686701(v=vs.85).aspx
	// 현재 실행중인 프로세스들 파악하기 위해선 첫번째 프로세스르 찾고 순차적으로
	// 다음 프로세스를 찾아 가는 방식을 취한다.
	// 첫번째 프로세스 찾기
	ret, _, _ := Process32First.Call(hProcessSnap, uintptr(unsafe.Pointer(&pi)))
	if ret <= 0 {
		syscall.GetLastError()
		log.Fatal("there is no process info")
		// Fatal 은 os.Exit(1) 호출함
		//os.Exit(1)
	}

	WriteLog(fp, pi)

	for {
		ret, _, _ = Process32Next.Call(hProcessSnap, uintptr(unsafe.Pointer(&pi)))
		WriteLog(fp, pi)
		if ret <= 0 {
			fmt.Println("Finding Process Finished.")
			break
		}
	}
	time.Sleep(3000000000)
}

func WriteLog(fp *os.File, pi PROCESSENTRY32) (ret int32) {

	var pi_for_print PROCESSENTRY32_FOR_PRINT

	pi_for_print.dwSize = pi.dwSize
	pi_for_print.cntUsage = pi.cntUsage
	pi_for_print.th32ProcessID = pi.th32ProcessID
	pi_for_print.th32DefaultHeapID = pi.th32DefaultHeapID
	pi_for_print.th32ModuleID = pi.th32ModuleID
	pi_for_print.cntThreads = pi.cntThreads
	pi_for_print.th32ParentProcessID = pi.th32ParentProcessID
	pi_for_print.pcPriClassBase = pi.pcPriClassBase
	pi_for_print.dwFlags = pi.dwFlags

	// szExeFile 길이 파악
	cnt := 0
	for {
		if pi.szExeFile[cnt] == 0 {
			break
		}
		cnt++
	}
	// UTF16 으로 문자열로 변환
	pi_for_print.szExeFile = syscall.UTF16ToString(pi.szExeFile[:cnt])

	//	fmt.Printf("%v\t%v\t%v\t%v\t%v\t%v\t%v\t%v\t%v\t%v\t\n",
	//		pi_for_printdwSize, pi_for_printcntUsage, pi_for_printth32ProcessID, pi_for_printth32DefaultHeapID,
	//		pi_for_printth32ModuleID, pi_for_printcntThreads, pi_for_printth32ParentProcessID,
	//		pi_for_printpcPriClassBase, pi_for_printdwFlags, pi_for_printszExeFile)
	//	fmt.Fprintf(fp, "%v\t%v\t%v\t%v\t%v\t%v\t%v\t%v\t%v\t%v\t\n",
	//		pi_for_printdwSize, pi_for_printcntUsage, pi_for_printth32ProcessID, pi_for_printth32DefaultHeapID,
	//		pi_for_printth32ModuleID, pi_for_printcntThreads, pi_for_printth32ParentProcessID,
	//		pi_for_printpcPriClassBase, pi_for_printdwFlags, pi_for_printszExeFile)
	// %+v 를 사용하면 구조체 데이터를 한번에 프린트할 수 있음.
	fmt.Printf("%+v\n", pi_for_print)
	fmt.Fprintf(fp, "%+v\n", pi_for_print)

	return ret
}
