/* library */
#include "functionality.h"
#include <iostream>
/**
 * @brief Main program.
 */
int main () {
    //read file and exit upon error
    std::string filename = "apple_drawing.txt";
    std::list<std::string> urls;
    int err = readFile(filename, urls);
    if (err != 0) {
        std::cout << "Failed to read file '" + filename + "'. Exiting program..." << std::endl;
        return 0;
    }
    //print each element in the list
    for (auto const &url: urls) {
        std::cout << "'" + url + "'" << std::endl;
    }
    return 0;
}
