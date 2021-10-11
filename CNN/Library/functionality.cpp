/* library */
#include "functionality.h"
#include "CImg.h"
#include <fstream>
#include <iostream>
#include <curl/curl.h>
#include <filesystem>

int readFile(const std::string filename, std::vector<std::string>& urls) {
    //reset list
    urls.clear();
    //open file and exit upon error
    std::ifstream file("../../Data-collection/Data/" + filename + ".txt");
    if (!file) {
        return -1;
    }
    //read each line in the file and push it to the vector
    std::string url;
    while (getline(file, url)) {
        urls.push_back(url);
    }
    return 0;
}

int downloadDataset(const std::vector<std::string> urls, const std::string datasetName) {
    //create directory
    std::filesystem::create_directories("../Data/" + datasetName);
    //download images and exit upon error
    for (int i = 0; i < urls.size(); i++) {
        int err = downloadImage(urls[i], "../Data/" + datasetName + "/" + std::to_string(i + 1) + ".jpg");
        if (err != 0) {
            return -1;
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

int getImageSize(const std::string path) {
    cimg_library::CImg<float> image;
    std::string fullPath = "../Data/" + path + ".jpg";
    image.load(fullPath.c_str());
    std::cout << std::to_string(image.height()) + "x" + std::to_string(image.width()) << std::endl;
    return 0;
}
