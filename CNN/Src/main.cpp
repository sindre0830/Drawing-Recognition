/* library */
#include "functionality.h"
#include <iostream>
/**
 * @brief Main program.
 */
int main() {
    int err;
    std::string filename = "apple_drawing";
    //read file and exit upon error
    std::vector<std::string> urls;
    err = readFile(filename, urls);
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
    //get image paths for the dataset
    std::vector<std::string> datasetPaths;
    getDatasetPaths(filename, datasetPaths);
    //parse dataset to matrixes
    arma::mat matrix;
    mlpack::data::ImageInfo imageMetadata;
    err = parseImageToMatrix(datasetPaths, matrix, imageMetadata);
    if (err != 0) {
        std::cout << "Failed to parse image to matrix. Exiting program..." << std::endl;
        return -1;
    }
    return 0;
}
