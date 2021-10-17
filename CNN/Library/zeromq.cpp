#include "zeromq.h"
#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#include <../zeromqConfig.h>

#define sleep(n)	Sleep(n)
#endif

void getDataset(std::string term) {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);
    socket.connect ("tcp://localhost:5555");

    zmq::message_t request(&term, term.size());

    //  Send request
    socket.send(zmq::buffer(term), zmq::send_flags::none);

    // wait for reply
    zmq::message_t reply;
    socket.recv (reply, zmq::recv_flags::none);
}