/* library */
#include "functionality.h"
#include "zeromq.h"
#include "dictionary.h"
#include <iostream>

/**
 * @brief Main program.
 */
int main() {
    int err;
    std::vector<std::string> datasets = { "apple_drawing", "banana", "pear" };
    for (auto dataset : datasets) {
        getDataset(dataset);
    }
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
        mapLabel.insert(std::make_pair(datasets[i], i + 1));
    }
    //get labels
    arma::rowvec labels;
    getLabels(mapLabel, labels);
    //train test split
    arma::mat trainData, testData;
    arma::rowvec trainLabel, testLabel;
    trainTestSplit(matrix, labels, trainData, testData, trainLabel, testLabel, 0.3, true);

    //define model
    mlpack::ann::FFN<mlpack::ann::NegativeLogLikelihood<>, mlpack::ann::RandomInitialization> model;
    
    // Check whether to load
    std::cout << "Looking for model..." << std::endl;
    bool test = model_exists("../Data/model.txt");
    if(test) {
        std::cout << "Loading model from file." << std::endl;
        mlpack::data::Load("../Data/model.txt", "model", model);
    } else {
        std::cout << "No model found, training new..." << std::endl;
        //define model
        defineModel(model, imageMetadata);
        //train model
        trainModel(model, trainData, trainLabel, testData, testLabel);
        mlpack::data::Save("../Data/model.txt", "model", model);
    }

    std::cout << "Predicting dataset..." << std::endl;
    //results
    double trainAccuracy, validAccuracy;
    predictModel(model, trainAccuracy, validAccuracy, trainData, trainLabel, testData, testLabel);
    std::cout << "Accuracy: train = " << trainAccuracy << "%,"<< "\t valid = " << validAccuracy << "%" << std::endl;
    return 0;
}
