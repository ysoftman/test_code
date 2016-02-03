// author : ysoftman
// encoding : utf-8
// title : smi(자막) 파일 싱크 수정
// desc : .smi 파일을 읽어 + - xxx sec 로 자막 노출 시간 수정하는 프로그램
package main

import "fmt"
import "os"
import "strconv"
import "strings"

func main() {
	fmt.Println("[Usage] " + os.Args[0] + " +(-) ms file.smi")
	fmt.Println("ex) forward 5 sec to subtitle start time")
	fmt.Println(os.Args[0] + " +5000 file.smi")
	fmt.Println("ex) backward 10 sec to subtitle start time")
	fmt.Println(os.Args[0] + " -10000 file.smi")

	// 인자 개수 체크
	cntArgs := len(os.Args)
	if cntArgs != 3 {
		err := fmt.Errorf("error! args cnt(%d) != 3", cntArgs)
		if err != nil {
			fmt.Println(err)
		}
		for i := 0; i < cntArgs; i++ {
			fmt.Printf("Args[%d] %s", i, os.Args[i])
		}
		os.Exit(1)
	}

	byteTemp := make([]byte, len(os.Args[1]))
	copy(byteTemp, os.Args[1])

	// 옵션 + 또는 - 파악
	OpCode := byteTemp[0]
	if OpCode != '+' && OpCode != '-' {
		fmt.Printf("missing keyword %q\n", byteTemp[0])
		os.Exit(1)
	}

	// 옵션 초 파악
	NumString := string(byteTemp[1:])
	MilliSec, _ := strconv.Atoi(NumString)
	if MilliSec < 0 {
		fmt.Println("MilliSec < 0")
		os.Exit(1)
	}
	MilliSec = int(MilliSec)
	// for debug
	fmt.Println("OpCode:", string(OpCode))
	fmt.Println("MilliSec:", MilliSec)

	// 자막 파일 열기
	SmiFile := os.Args[2]
	fpInput, err := os.Open(SmiFile)
	if err != nil {
		fmt.Println("Can't open " + SmiFile)
		os.Exit(1)
	}
	// 파일 정보
	filestat, _ := fpInput.Stat()
	fmt.Println("Input File:", filestat.Name())
	fmt.Println("Input File Size:", filestat.Size(), "bytes")
	defer fpInput.Close()

	// 싱크 수정된 자막 파일 생성
	NewSmiFile := "New" + SmiFile
	fpOutput, err := os.Create(NewSmiFile)

	if err != nil {
		fmt.Println("Can't open " + SmiFile)
		os.Exit(1)
	}
	defer fpOutput.Close()

	maxLen := filestat.Size()

	buffer := []byte("")
	buffer = make([]byte, maxLen)
	fpInput.Read(buffer)

	strContents := string(buffer)

	// <SYNC Start=123456> 의 숫자를 찾아서 변경한다.
	sepStart := ("<SYNC Start=")
	sepEnd := ("><P Class=KRCC>")
	sepStartLen := len(sepStart)
	// sepEndLen := len(sepEnd)

	for len(strContents) > 0 {
		// 처음부터 <SYNC Start= 까지의 새파일에 기록
		idx := strings.Index(strContents, sepStart)
        // 파일 끝까지 다 찾았다면 끝내기
        if idx < 0 {
            fpOutput.WriteString(strContents)
            break
        }
		strTemp := strContents[:idx+sepStartLen]
		fpOutput.WriteString(strTemp)

		// 기록된 부분 제거하기
		strContents = strContents[idx+sepStartLen:]

		// 시간값 추출
		idx = strings.Index(strContents, sepEnd)
		strTemp = strContents[:idx]
		fmt.Println("time:", strTemp)

		newMilliSec, _ := strconv.Atoi(strTemp)

		if OpCode == '-' {
			newMilliSec -= MilliSec
		} else {
			newMilliSec += MilliSec
		}

		strTemp = strconv.Itoa(newMilliSec)
		fmt.Println("new-time:", strTemp)
		// 새 시간값 기록
		fpOutput.WriteString(strTemp)

		// 기록된 부분 제거하기
		strContents = strContents[idx:]

	}

}
