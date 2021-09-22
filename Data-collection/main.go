package main

import (
	"fmt"
	"log"
	dict "main/Dict"
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
	fmt.Println("Hello world!")
}
