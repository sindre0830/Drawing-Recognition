/* library */
#include "functionality.h"
#include <iostream>

arma::Row<size_t> getLabels(arma::mat predOut) {
    arma::Row<size_t> predLabels(predOut.n_cols);
    for (arma::uword i = 0; i < predOut.n_cols; ++i) {
        predLabels(i) = predOut.col(i).index_max();
    }
    return predLabels;
}

/**
 * @brief Main program.
 */
int main() {
    int err;
    std::vector<std::string> datasets = { "apple_drawing", "banana" };
    //read file and exit upon error
    // std::vector<std::vector<std::string>> urls;
    // err = readFile(datasets, urls);
    // if (err != 0) {
    //     std::cout << "Failed to open file. Exiting program..." << std::endl;
    //     return -1;
    // }
    // //download dataset and exit upon error
    // err = downloadDataset(urls, datasets);
    // if (err != 0) {
    //     std::cout << "Failed to download datasets. Exiting program..." << std::endl;
    //     return -1;
    // }
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
        model.Add<mlpack::ann::Convolution<> >(1, 8, 5, 5, 1, 1, 0, 0, static_cast<int>(imageMetadata.Width()), static_cast<int>(imageMetadata.Height()));
        model.Add<mlpack::ann::ReLULayer<> >();
        model.Add<mlpack::ann::MaxPooling<> >(8, 8, 2, 2);
        model.Add<mlpack::ann::Convolution<> >(8, 12, 2, 2);
        model.Add<mlpack::ann::ReLULayer<> >();
        model.Add<mlpack::ann::MaxPooling<> >(2, 2, 2, 2);
        model.Add<mlpack::ann::Linear<> >(33408, 20);
        model.Add<mlpack::ann::ReLULayer<> >();
        model.Add<mlpack::ann::Linear<> >(20, 10);
        model.Add<mlpack::ann::ReLULayer<> >();
        model.Add<mlpack::ann::Linear<> >(10, 2);
        model.Add<mlpack::ann::LogSoftMax<> >();                   
        //define optimizer
        constexpr int MAX_ITERATIONS = 500; // set to zero to allow infinite iterations.
        constexpr double STEP_SIZE = 1.2e-3;// step size for Adam optimizer.
        constexpr int BATCH_SIZE = 50;
        constexpr size_t EPOCH = 2;
        ens::Adam optimizer(
            STEP_SIZE,  // Step size of the optimizer.
            BATCH_SIZE, // Batch size. Number of data points that are used in each iteration.
            0.9,        // Exponential decay rate for the first moment estimates.
            0.999, // Exponential decay rate for the weighted infinity norm estimates.
            1e-8,  // Value used to initialise the mean squared gradient parameter.
            MAX_ITERATIONS, // Max number of iterations.
            1e-8, // Tolerance.
            true
        );
        //train on model
        model.Train(
            trainData,
            trainLabel,
            optimizer,
            ens::PrintLoss(),
            ens::ProgressBar(),
            ens::EarlyStopAtMinLoss(EPOCH),
            ens::EarlyStopAtMinLoss(
                [&](const arma::mat& /* param */) {
                    double validationLoss = model.Evaluate(testData, testLabel);
                    std::cout << "Validation loss: " << validationLoss << "." << std::endl;
                    return validationLoss;
                }
            )
        );
        mlpack::data::Save("../Data/model.txt", "model", model);
    }

    std::cout << "Predicting dataset..." << std::endl;
    //results
    arma::mat predOut;
    model.Predict(trainData, predOut);
    arma::Row<size_t> predLabels = getLabels(predOut);
    double trainAccuracy = arma::accu(predLabels == trainLabel) / (double)trainLabel.n_elem * 100;
    model.Predict(testData, predOut);
    predLabels = getLabels(predOut);
    double validAccuracy = arma::accu(predLabels == testLabel) / (double)testLabel.n_elem * 100;
    std::cout << "Accuracy: train = " << trainAccuracy << "%,"<< "\t valid = " << validAccuracy << "%" << std::endl;
    return 0;
}
