# import foreign modules
import requests
import os


# Parses datasets files to lists of URLs.
def parseDatasetsFiles(datasets):
    arrDatasetsURL = []
    # iterate through datasets and parses their list of URLs
    for dataset in datasets:
        arrDatasetsURL.append(parseDatasetFile(dataset))
    return arrDatasetsURL


# Parses dataset file to a list of URLs.
def parseDatasetFile(dataset):
    # open file in read-mode and output each line to a list
    file = open("../Data-collection/Data/" + dataset + ".txt", "r")
    arrDatasetURL = file.read().splitlines()
    return arrDatasetURL


# Download dataset from list of URLs.
def downloadDataset(dataset, urls):
    # create directories if needed
    path = "Data/" + dataset + "/"
    os.makedirs(path, exist_ok=True)
    # iterate through urls and request each image
    for index, url in enumerate(urls, start=1):
        req = requests.get(url)
        open(path + str(index) + ".jpg", "wb").write(req.content)
