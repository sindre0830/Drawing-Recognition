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
        mapLabel.insert(std::make_pair(datasets[i], i));
    }
    //get labels
    arma::rowvec labels;
    getLabels(mapLabel, labels);
    //train test split
    arma::mat trainData, testData;
    arma::rowvec trainLabel, testLabel;
    trainTestSplit(matrix, labels, trainData, testData, trainLabel, testLabel, 0.3, true);
    // Defines model
    constexpr int MAX_ITERATIONS = 0; // set to zero to allow infinite iterations.
    constexpr double STEP_SIZE = 1.2e-3;// step size for Adam optimizer.
    constexpr int BATCH_SIZE = 50;
        constexpr size_t EPOCH = 2;
    // Width = 245, Height = 205
    mlpack::ann::FFN<mlpack::ann::NegativeLogLikelihood<>, mlpack::ann::RandomInitialization> model;
    model.Add<mlpack::ann::Convolution<> >(1, 8, 5, 5, 1, 1, 0, 0, static_cast<int>(imageMetadata.Width()), static_cast<int>(imageMetadata.Height()));
    model.Add<mlpack::ann::ReLULayer<> >();
    model.Add<mlpack::ann::MaxPooling<> >(8, 8, 2, 2);
    model.Add<mlpack::ann::Convolution<> >(8, 12, 2, 2);
    model.Add<mlpack::ann::ReLULayer<> >();
    model.Add<mlpack::ann::MaxPooling<> >(2, 2, 2, 2);
    model.Add<mlpack::ann::Linear<> >(62, 52);
    model.Add<mlpack::ann::ReLULayer<> >();
    model.Add<mlpack::ann::Linear<> >(20, 10);
    model.Add<mlpack::ann::ReLULayer<> >();
    model.Add<mlpack::ann::Linear<> >(10, 2);
    model.Add<mlpack::ann::LogSoftMax<> >();
    // model.Add<mlpack::ann::Convolution<>>(1,  // Number of input activation maps.
    //                         6,  // Number of output activation maps.
    //                         5,  // Filter width.
    //                         5,  // Filter height.
    //                         1,  // Stride along width.
    //                         1,  // Stride along height.
    //                         0,  // Padding width.
    //                         0,  // Padding height.
    //                         imageMetadata.Width(), // Input width.
    //                         imageMetadata.Height()  // Input height.
    // );

    // model.Add<mlpack::ann::ReLULayer<>>();

    // model.Add<mlpack::ann::MaxPooling<>>(2, // Width of field.
    //                         2, // Height of field.
    //                         2, // Stride along width.
    //                         2, // Stride along height.
    //                         true);

    // model.Add<mlpack::ann::Convolution<>>(6, // Number of input activation maps.
    //                         16, // Number of output activation maps.
    //                         5, // Filter width.
    //                         5, // Filter height.
    //                         1, // Stride along width.
    //                         1, // Stride along height.
    //                         0, // Padding width.
    //                         0, // Padding height.
    //                         imageMetadata.Width() / 2, // Input width.
    //                         imageMetadata.Height() / 2  // Input height.
    // );

    // model.Add<mlpack::ann::ReLULayer<>>();
                            
    // model.Add<mlpack::ann::MaxPooling<>>(2, 2, 2, 2, true);
                            
    // model.Add<mlpack::ann::Linear<>>(16 * 4 * 4, 10);
                        
    // model.Add<mlpack::ann::LogSoftMax<>>();                         
    //Train model on dataset
    ens::Adam optimizer(
    STEP_SIZE,  // Step size of the optimizer.
    BATCH_SIZE, // Batch size. Number of data points that are used in each iteration.
    0.9,        // Exponential decay rate for the first moment estimates.
    0.999, // Exponential decay rate for the weighted infinity norm estimates.
    1e-8,  // Value used to initialise the mean squared gradient parameter.
    MAX_ITERATIONS, // Max number of iterations.
    1e-8, // Tolerance.
    true);

    model.Train(trainData,
            trainLabel,
            optimizer,
            ens::PrintLoss(),
            ens::ProgressBar(),
            ens::EarlyStopAtMinLoss(EPOCH),
            ens::EarlyStopAtMinLoss(
                [&](const arma::mat& /* param */)
                {
                    double validationLoss = model.Evaluate(testData, testLabel);
                    std::cout << "Validation loss: " << validationLoss
                        << "." << std::endl;
                    return validationLoss;
                }));
    // Results
    //arma::mat predOut;
    //model.Predict(trainData, predOut);
    // predOut.print();
    // arma::Row<size_t> predLabels = getLabels(predOut);
    // double trainAccuracy = arma::accu(predLabels == trainLabel) / ( double )trainLabel.n_elem * 100;
    // model.Predict(testData, predOut);
    // predLabels = getLabels(predOut);
    // double validAccuracy = arma::accu(predLabels == testLabel) / ( double )testLabel.n_elem * 100;
    // std::cout << "Accuracy: train = " << trainAccuracy << "%,"<< "\t valid = " << validAccuracy << "%" << std::endl;

    // mat testPredOut;
    // model.Predict(testData,testPredOut);
    // arma::Row<size_t> testPred = getLabels(testPredOut)
    // double testAccuracy = arma::accu(testPredOut == testLabel) /( double )trainLabel.n_elem * 100;
    // std::cout<<"Test Accuracy = "<< testAccuracy;
    return 0;
}
