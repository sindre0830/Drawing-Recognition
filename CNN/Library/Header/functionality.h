#ifndef __FUNCTIONALITY_H
#define __FUNCTIONALITY_H
/* library */
#include <string>
#include <vector>

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

int getImageSize(const std::string path);

#endif
