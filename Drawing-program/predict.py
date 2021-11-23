import zmq

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5959")

while True:
    #  Wait for next request from client
    message = socket.recv()
    print("Received request: %s" % message)

    if message == b"terminate":
        print("Terminating program...")
        break

    #  Send reply back to client
    socket.send(b"")
