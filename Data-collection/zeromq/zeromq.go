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
func Send(message string) error {
	ctx, err := zmq.NewContext()
	if err != nil {
		return err
	}

	socket, err := ctx.NewSocket(zmq.REQ)
	if err != nil {
		return err
	}

	defer ctx.Term()
	defer socket.Close()

	fmt.Printf("Connecting to server...")
	socket.Connect("tcp://localhost:5555")

	socket.Send(message, 0)

	reply, _ := socket.Recv(0)
	println("Received ", string(reply))

	return nil
}
