package main

import (
	"fmt"
	"main/zeromq"
)

// We use the channel to keep server running until it receives contact - might change
var exit = make(chan bool)

// Main program.
func main() {
	fmt.Println("Starting...")

	go zeromq.Server(exit)
	<-exit

	fmt.Println("\n\tClosing!")
}
