package zeromq

// Very basic because I spent all my time testing in separate project with client + server
// and it's midnight sunday + we need to discuss how to implement
import (
	"fmt"
	"time"

	zmq "github.com/pebbe/zmq4"
)

/*
/ Server()
/ Waits for contact
*/
func Server() error {

	context, _ := zmq.NewContext()
	socket, _ := context.NewSocket(zmq.REP)

	defer context.Term()
	defer socket.Close()

	fmt.Printf("\nConnecting to server...")
	socket.Bind("tcp://*:5555")

	for {
		msg, _ := socket.Recv(0)
		println("\nReceived ", string(msg))

		time.Sleep(time.Second)

		socket.Send("World", 0)
	}
}

// ctx, err := zmq.NewContext()
// if err != nil {
// 	return err
// }

// socket, err := ctx.NewSocket(zmq.REQ)
// if err != nil {
// 	return err
// }

// defer ctx.Term()
// defer socket.Close()

// fmt.Printf("Connecting to server...")
// socket.Connect("tcp://localhost:5555")

// socket.Send(message, 0)

// reply, _ := socket.Recv(0)
// println("Received ", string(reply))

// return nil
//}
