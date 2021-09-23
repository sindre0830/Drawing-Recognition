package main

import (
	"fmt"
	"log"
	dict "main/Dict"
	"main/zeromq"
	"time"
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
