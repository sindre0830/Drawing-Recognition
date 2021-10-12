#ifndef __FUNCTIONALITY_H
#define __FUNCTIONALITY_H
/* library */
#include <string>
#include <vector>
#include <mlpack/core.hpp>
#include <armadillo>

/**
 * @brief Reads file generated by data-collection and parse it to list of strings. 
 * 
 * @param filename  Name of the file to read. 
 * @param urls      List to output file content.
 * @return Error code 
 */
int readFile(const std::string filename, std::vector<std::string>& urls);

/**
 * @brief Downloads a set of images.
 * 
 * @param urls          List of URLs.
 * @param datasetName   Name of path location.
 * @return Error code
 */
int downloadDataset(const std::vector<std::string> urls, const std::string datasetName);

/**
 * @brief Downloads image from URL to file location.
 * 
 * @param url       Location to image to download.
 * @param filename  Path to save image.
 * @return Error code  
 */
int downloadImage(const std::string url, const std::string filename);

/**
 * @brief Stores image paths for specified dataset.
 * 
 * @param dataset       Dataset to create paths for.
 * @param datasetPaths  List to save dataset paths to.
 */
void getDatasetPaths(const std::string dataset, std::vector<std::string> &datasetPaths);

/**
 * @brief Parses images to a matrix.
 * 
 * @param datasetPaths  Paths to images in dataset.
 * @param matrix        Matrix to save output to.
 * @param imageMetadata Structure to save image metadata to.
 * @return Error code 
 */
int parseImageToMatrix(const std::vector<std::string> datasetPaths, arma::mat &matrix, mlpack::data::ImageInfo &imageMetadata);

#endif
