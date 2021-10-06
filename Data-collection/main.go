package main

import (
	"fmt"
	"log"
	dict "main/Dict"
	zeromq "main/Zeromq"
)

// init runs once at startup.
func init() {
	var err error
	//read API key and branch if an error occurred
	dict.GOOGLEIMAGES_KEY, err = dict.GetGoogleImagesKey()
	if err != nil {
		log.Fatalln(err)
	}
}

// We use the channel to keep server running until it receives contact - might change
var exit = make(chan bool)

// Main program.
func main() {
	fmt.Println("Starting...")

	go zeromq.Server(exit)
	<-exit

	fmt.Println("\n\tClosing!")
}
