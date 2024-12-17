package main

import (
	"log"
	"time"

	"go.uber.org/zap"
)

func main() {
	logConfig := zap.Config{
		// An AtomicLevel is an atomically changeable, dynamic logging level. It lets you safely change the log level of a tree of loggers (the root logger and any children created by adding context) at runtime.
		Level:            zap.NewAtomicLevelAt(zap.DebugLevel),
		EncoderConfig:    zap.NewProductionEncoderConfig(),
		Encoding:         "json",
		OutputPaths:      []string{"stdout"},
		ErrorOutputPaths: []string{"stderr"},
	}
	logger, err := logConfig.Build()
	if err != nil {
		log.Fatal(err)
	}
	defer logger.Sync() // flushes buffer, if any
	sugar := logger.Sugar()
	url := "ysoftman.tes.com"
	sugar.Infow("failed to fetch URL",
		// Structured context as loosely typed key-value pairs.
		"url", url,
		"attempt", 3,
		"backoff", time.Second,
	)
	sugar.Infof("Failed to fetch URL: %s", url)
	sugar.Debugf("Failed to fetch URL: %s", url)
}
