#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#include "../client/client.h"
#else
#include <windows.h>

#include <../zeromqConfig.h>

#define sleep(n)	Sleep(n)
#endif

// Basic ZMQ server!
int main () {
    client();
}
