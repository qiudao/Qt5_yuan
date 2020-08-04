package main

import (
	"./yuan"
	"time"
)

const (
	serverAddr = "0.0.0.0:443"
      )

func main() {
	var y yuan.Yuan

	y.String()

	go y.ListenAndServe(serverAddr)

	for true {
		time.Sleep(time.Second)
	}
}
