package zeromq

// Very basic because I spent all my time testing in separate project with client + server
// and it's midnight sunday + we need to discuss how to implement
import (
	"fmt"

	zmq "github.com/pebbe/zmq4"
)

/*
/ Send()
/ I am not sure how we want to pass the data to this function - stored on file, in array, etc, so will need to modify
*/
func Server(exit chan<- bool) error {
	ctx, err := zmq.NewContext()
	if err != nil {
		return err
	}

	socket, err := ctx.NewSocket(zmq.REP)
	if err != nil {
		return err
	}

	defer ctx.Term()
	defer socket.Close()

	fmt.Printf("Running server...")
	socket.Bind("tcp://*:5555")

	for {
		msg, err := socket.Recv(0)
		if err != nil {
			return err
		}

		// This is where we start working instead of just receiving!
		println("\nReceived ", string(msg))

		// returns on channel when contact is made
		exit <- true
	}
}
