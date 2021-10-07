/* library */
#include "functionality.h"
#include <iostream>
#include <filesystem>
/**
 * @brief Main program.
 */
int main () {
    //read file and exit upon error
    std::string filename = "apple_drawing";
    std::vector<std::string> urls;
    int err = readFile(filename, urls);
    if (err != 0) {
        std::cout << "Failed to read file '" + filename + "'. Exiting program..." << std::endl;
        return -1;
    }
    //print each element in the list
    // for (auto const &url: urls) {
    //     std::cout << "'" + url + "'" << std::endl;
    // }
    //download data
    std::filesystem::create_directories("../Data/" + filename);
    err = downloadImage(urls[0], "../Data/" + filename + "/1.png");
    if (err != 0) {
        return -1;
    }
    return 0;
}
