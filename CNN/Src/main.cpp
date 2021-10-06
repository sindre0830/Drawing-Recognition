#include "../Library/Header/zeromq.h"
#include <iostream>

int main () {

    // I considered whether to put this in its own function too, but I figured
    // better to move things later when we know how our main should fit together.
    std::string datasetpath = getDataset("Lion");

    // test it
    std::cout << "Received: " << datasetpath << std::endl;
    
    return 0;
}
