package main

import (
	"fmt"
	"main/zeromq"
	"time"
)

// Main program.
func main() {
	fmt.Println("Starting...")
	//go server.RunServer()
	go zeromq.Send("test")

	time.Sleep(time.Second * 2)

	go zeromq.Send("test2")

	time.Sleep(time.Second * 10)
	fmt.Println("\n\tClosing!")
}
