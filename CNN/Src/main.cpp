/* library */
#include "functionality.h"
#include <iostream>
/**
 * @brief Main program.
 */
int main () {
    //read file and exit upon error
    std::string filename = "apple_drawing";
    std::vector<std::string> urls;
    int err = readFile(filename, urls);
    if (err != 0) {
        std::cout << "Failed to read file '" + filename + ".txt'. Exiting program..." << std::endl;
        return -1;
    }
    //download dataset and exit upon error
    err = downloadDataset(urls, filename);
    if (err != 0) {
        std::cout << "Failed to download dataset '" + filename + "'. Exiting program..." << std::endl;
        return -1;
    }
    //get image size
    err = getImageSize(filename + "/1");
    return 0;
}
