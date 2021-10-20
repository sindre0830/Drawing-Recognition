# import local modules
import dictionary as dict
# import foreign modules
import requests
import os
import cv2


# Parses dataset file to a list of URLs.
def parseDatasetFile(dataset):
    # open file in read-mode and output each line to a list
    file = open("../Data-collection/Data/" + dataset + ".txt", "r")
    arrDatasetURL = file.read().splitlines()
    return arrDatasetURL


# Download datasets.
def downloadDatasets(datasets):
    # iterate through datasets and request each dataset
    for dataset in datasets:
        dict.printOperation("Downloading '" + dataset + "' dataset...")
        if os.path.exists("Data/" + dataset) is False:
            # get list of URLs
            arrDatasetsURL = parseDatasetFile(dataset)
            downloadDataset(dataset, arrDatasetsURL)
        print(dict.DONE)


# Download dataset from list of URLs.
def downloadDataset(dataset, urls):
    # create directories if needed
    path = "Data/" + dataset + "/"
    os.makedirs(path, exist_ok=True)
    # iterate through urls and request each image
    for index, url in enumerate(urls, start=1):
        req = requests.get(url)
        open(path + str(index) + ".jpg", "wb").write(req.content)


# Parse datasets to a list of matrixes and labels.
def parseDatasets(datasets):
    images = []
    labels = []
    for dataset in datasets:
        dict.printOperation("Parsing '" + dataset + "' dataset...")
        for filename in os.listdir("Data/" + dataset):
            img = cv2.imread(os.path.join("Data/" + dataset, filename))
            if img is not None:
                images.append(img)
                labels.append(dict.DATASET_INTEGER_CONVERTER[dataset])
        print(dict.DONE)
    return images, labels
