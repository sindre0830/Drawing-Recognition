package zeromq

// Very basic because I spent all my time testing in separate project with client + server
// and it's midnight sunday + we need to discuss how to implement.
import (
	"fmt"
	thumbnails "main/Api/Thumbnails"

	zmq "github.com/pebbe/zmq4"
)

// Server sets up a connection and starts an endless loop waiting for requests.
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

		// this is where we start working instead of just receiving!
		println("\nReceived ", string(msg))
		var dataset thumbnails.Thumbnails
		dataset.Handler(string(msg))

		// replies with path to text-file with urls
		// only need name of file without type
		reply := "done"
		socket.Send(reply, 0)
	}
}
