package main

import (
	"fmt"
	"time"

	l4g "github.com/alecthomas/log4go"
)

func main() {
	fmt.Println("log4go test...")

	l4g.LoadConfiguration("log4go.xml")
	l4g.Info("The time is now: %s", time.Now())
	// FINEST
	// FINE
	// DEBUG
	// TRACE
	// INFO
	// WARNING
	// ERROR
	// CRITICAL
	l4g.Finest("Finest")
	l4g.Fine("Fine")
	l4g.Debug("Debug")
	l4g.Trace("Trace")
	l4g.Info("Info")
	l4g.Warn("warn")
	l4g.Error("Error")
	l4g.Critical("Critical")

	fmt.Println("end.")

}
