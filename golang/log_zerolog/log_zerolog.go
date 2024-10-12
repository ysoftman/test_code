package main

import (
	"io"
	"os"

	"github.com/rs/zerolog"
	"github.com/rs/zerolog/log"
)

func main() {
	// UNIX Time is faster and smaller than most timestamps
	zerolog.TimeFieldFormat = zerolog.TimeFormatUnix
	zerolog.SetGlobalLevel(zerolog.DebugLevel)
	//zerolog.SetGlobalLevel(zerolog.InfoLevel)
	log.Print("hello world")

	// 종료
	//log.Fatal().Msg("fatal")

	log.Debug().
		Str("Scale", "833 cents").
		Float64("Interval", 833.09).
		Msg("Fibonacci is everywhere")

	// Msg 없이 출력하기
	// 키 중복을 허용한다
	log.Debug().
		Str("Name", "Tom").
		Str("Name", "Bill").
		Send()

	log.Info().Msg("This message appears when log level set to Debug or Info")

	//info level 이라면 debug 로그 출력 안된다
	log.Debug().Msg("This message appears only when log level set to Debug")
	if log.Debug().Enabled() {
		log.Debug().Str("name", "lemon").Msg("test~~")
	}

	isJson := false
	var writer io.Writer
	if isJson {
		writer = os.Stdout
	} else {
		writer = zerolog.ConsoleWriter{Out: os.Stdout}
	}
	// Output duplicates the global logger and sets w as its output.
	logger2 := log.Output(writer)
	logger2.Info().Msg("logger2 -> consoleWriter")

	// Create a child logger for concurrency safety
	logger := log.Logger.With().Logger()
	logger.Debug().Str("name", "childlog").Send()

	// Add context fields
	logger.UpdateContext(func(c zerolog.Context) zerolog.Context {
		return c.Str("fruit", "lemon")
	})
	//위에서 context 에 추가한 값이 같이 출력된다
	logger.Debug().Str("name", "childlog").Msg("context fields have added")
}
