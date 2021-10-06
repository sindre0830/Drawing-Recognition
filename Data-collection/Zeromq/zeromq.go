package zeromq

// Very basic because I spent all my time testing in separate project with client + server
// and it's midnight sunday + we need to discuss how to implement
import (
	"fmt"

	zmq "github.com/pebbe/zmq4"
)

/*
/ Server()
/ Waits for contact
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

		// We want to wait for work to be done

		// replies with path to text-file with urls
		reply := "/home/test/fake-path/imagefile.txt"
		socket.Send(reply, 0)

		// returns on channel when reply is made
		exit <- true
	}
}
