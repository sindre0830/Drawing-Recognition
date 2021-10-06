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

void client() {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);
    socket.connect ("tcp://localhost:5555");

    zmq::message_t request;

    //  Send request
    socket.send(zmq::str_buffer("Exec"), zmq::send_flags::none);
}