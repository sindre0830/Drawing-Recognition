/* library */
#include "functionality.h"
#include <fstream>

int readFile(const std::string filename, std::list<std::string>& urls) {
    //reset list
    urls.clear();
    //open file and exit upon error
    std::ifstream file("../../Data-collection/Data/" + filename);
    if (!file) {
        return -1;
    }
    //read each line in the file and push it to the list
    std::string url;
    while (getline(file, url)) {
        urls.push_back(url);
    }
    return 0;
}
