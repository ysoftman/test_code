// ysoftman
// beep 패키지 테스트
package main

import (
	"fmt"
	"log"
	"os"
	"time"

	"github.com/faiface/beep"
	"github.com/faiface/beep/mp3"
	"github.com/faiface/beep/speaker"
	"github.com/faiface/beep/wav"
)

func main() {
	convertMP3toWav()
	playmp3()
}

func convertMP3toWav() {
	// mp3 파일 출처 http://file-examples.com/wp-content/uploads/2017/11/file_example_MP3_1MG.mp3
	f, err := os.Open("file_example_MP3_1MG.mp3")
	if err != nil {
		log.Fatal(err)
	}

	// streamer : 사운드 스트림 데이터
	// format : 샘플링 포맷 정보
	streamer, format, err := mp3.Decode(f)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("format(sampling rate):", format)

	wavfile, err := os.Create("out.wav")
	if err != nil {
		log.Fatal(err)
	}
	// decode 된 mp3 -> wav 파일로 인코딩해서 저장
	wav.Encode(wavfile, streamer, format)
}

func playmp3() {
	f, err := os.Open("file_example_MP3_1MG.mp3")
	if err != nil {
		log.Fatal(err)
	}

	streamer, format, err := mp3.Decode(f)

	// 사운드 출력을 위해 스피커 초기화
	speaker.Init(format.SampleRate, format.SampleRate.N(time.Second/10))

	// 사운드 플레이
	// speaker.Play(streamer)
	// 플레이를 계속할 수있도록 hang on -> 플레이가 종료되도 끝나지 않는 ugly 방법이라 비추
	// select {}

	// 사운드 플레이
	done := make(chan bool)
	speaker.Play(beep.Seq(streamer, beep.Callback(func() {
		done <- true
	})))
	<-done

}
