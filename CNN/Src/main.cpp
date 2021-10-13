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
    //store labels
    std::map<std::string, int> mapLabel;
    mapLabel.insert(std::make_pair("apple", 0));
    //get labels
    arma::rowvec labels;
    err = getLabels(mapLabel, "apple", labels);
    if (err != 0) {
        return -1;
    }
    //train test split
    arma::mat trainData, testData;
    arma::rowvec trainLabel, testLabel;
    trainTestSplit(matrix, labels, trainData, testData, trainLabel, testLabel, 0.3, true);
    return 0;
}
