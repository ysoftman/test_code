package main

import (
	"log"
	"net/http"
	"os"
	"os/signal"
	"syscall"

	"github.com/go-chi/chi"
)

func main() {

	sqldb = NewDB()
	defer sqldb.sqlDB.Close()
	log.Println("connected db")

	r := chi.NewRouter()
	r.Route("/api", func(r chi.Router) {
		r.HandleFunc("/upload", UploadHandler())
		r.HandleFunc("/query", QueryDataHandler())
	})

	go func() {
		if err := http.ListenAndServe(":9000", r); err != nil {
			log.Fatal(err)
		}
	}()

	log.Println("server is running :9000")
	sigQuitChan := make(chan os.Signal)
	signal.Notify(sigQuitChan, syscall.SIGINT, syscall.SIGQUIT, syscall.SIGKILL)
	sigInfo := <-sigQuitChan
	log.Printf("Shutdown server, Caused by (%v) signal\n", sigInfo)
}
