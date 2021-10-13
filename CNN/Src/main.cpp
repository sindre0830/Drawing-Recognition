/* library */
#include "functionality.h"
#include <iostream>
/**
 * @brief Main program.
 */
int main() {
    int err;
    std::vector<std::string> datasets = { "apple_drawing", "banana" };
    //read file and exit upon error
    std::vector<std::vector<std::string>> urls;
    err = readFile(datasets, urls);
    if (err != 0) {
        std::cout << "Failed to open file. Exiting program..." << std::endl;
        return -1;
    }
    //download dataset and exit upon error
    err = downloadDataset(urls, datasets);
    if (err != 0) {
        std::cout << "Failed to download datasets. Exiting program..." << std::endl;
        return -1;
    }
    //get image paths for the dataset
    std::vector<std::string> datasetPaths;
    getDatasetPaths(datasets, datasetPaths);
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
    for(int i = 0; i < datasets.size(); i++) {
        mapLabel.insert(std::make_pair(datasets[i], i));
    }
    //get labels
    arma::rowvec labels;
    getLabels(mapLabel, labels);
    //train test split
    arma::mat trainData, testData;
    arma::rowvec trainLabel, testLabel;
    trainTestSplit(matrix, labels, trainData, testData, trainLabel, testLabel, 0.3, true);
    return 0;
}
