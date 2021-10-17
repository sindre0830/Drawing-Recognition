/* library */
#include "functionality.h"
#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <curl/curl.h>
#include <filesystem>
#include <mlpack/core/data/split_data.hpp>

int readFile(const std::vector<std::string> filenames, std::vector<std::vector<std::string>>& urls) {
    //open file and exit upon error
    for(int i = 0; i < filenames.size(); i++) {
        std::ifstream file("../../Data-collection/Data/" + filenames[i] + ".txt");
        if (!file) {
            return -1;
        }
        //read each line in the file and push it to the vector
        std::vector<std::string> bufferUrl;
        std::string url;
        while (getline(file, url)) {
            bufferUrl.push_back(url);
        }
        urls.push_back(bufferUrl);
    }
    return 0;
}

int downloadDataset(const std::vector<std::vector<std::string>> urls, const std::vector<std::string> datasetNames) {
    for (int i = 0; i < datasetNames.size(); i++) {
        //create directory
        std::filesystem::create_directories("../Data/" + datasetNames[i]);
        //download images and exit upon error
        for (int j = 0; j < urls[i].size(); j++) {
            int err = downloadImage(urls[i][j], "../Data/" + datasetNames[i] + "/" + std::to_string(j + 1) + ".jpg");
            if (err != 0) {
                return -1;
            }
        }
    }
    return 0;
}

int downloadImage(const std::string url, const std::string filename) {
    CURL *curlImage;
    CURLcode res;
    FILE *fp;
    //initiate curl pipeline and exit upon error
    curlImage = curl_easy_init();
    if (!curlImage) {
        std::cout << "Failed to initiate curl..." << std::endl;
        return -1;
    }
    //create/open file and exit upon error
    fp = fopen(filename.c_str(), "wb");
    if (!fp) {
        std::cout << "Failed to create/open file..." << std::endl;
        curl_easy_cleanup(curlImage);
        return -1;
    }
    //configure curl pipeline
    curl_easy_setopt(curlImage, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlImage, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curlImage, CURLOPT_WRITEDATA, fp);
    //run curl pipeline and exit upon error
    res = curl_easy_perform(curlImage);
    if (res != CURLE_OK) {
        fprintf(stderr, "\nlibcurl: (%d) ", res);
        std::cout << "Failed to receive image from URL..." << std::endl;
        curl_easy_cleanup(curlImage);
        fclose(fp);
        return -1;
    }
    //perform cleanup
    curl_easy_cleanup(curlImage);
    fclose(fp);
    return 0;
}

void getDatasetPaths(const std::vector<std::string> datasets, std::vector<std::string> &datasetPaths) {
    for (int i = 0; i < datasets.size(); i++) {
        for (int j = 1; j <= 100; j++) {
            datasetPaths.push_back("../Data/" + datasets[i] + "/" + std::to_string(j) + ".jpg");
        }
    }
}

bool model_exists (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

int parseImageToMatrix(const std::vector<std::string> datasetPaths, arma::mat &matrix, mlpack::data::ImageInfo &imageMetadata) {
    bool err = mlpack::data::Load(datasetPaths, matrix, imageMetadata);
    if (err != true) {
        return -1;
    }
    return 0;
}

void getLabels(const std::map<std::string, int> mapLabel, arma::rowvec &labels) {
    auto it = mapLabel.begin();
    std::vector<int> arrLabels;
    for (auto& [key, value]: mapLabel) {  
        std::vector<int> bufferLabels(100, value);
        arrLabels.insert(arrLabels.end(), bufferLabels.begin(), bufferLabels.end());
    }
    labels = arma::conv_to<arma::rowvec>::from(arrLabels);
}

void trainTestSplit(const arma::mat data, const arma::rowvec labels, arma::mat &trainData, arma::mat &testData, arma::rowvec &trainLabel, arma::rowvec &testLabel, const double ratio, const bool flagShuffle) {
    mlpack::math::RandomSeed(100);
    mlpack::data::Split(data, labels, trainData, testData, trainLabel, testLabel, ratio, flagShuffle);
}

void defineModel(mlpack::ann::FFN<mlpack::ann::NegativeLogLikelihood<>, mlpack::ann::RandomInitialization> &model, const mlpack::data::ImageInfo imageMetadata) {
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
}

void trainModel(mlpack::ann::FFN<mlpack::ann::NegativeLogLikelihood<>, mlpack::ann::RandomInitialization> &model, arma::mat trainData, arma::rowvec trainLabel, arma::mat testData, arma::rowvec testLabel) {
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
}
