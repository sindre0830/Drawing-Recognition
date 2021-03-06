# import local modules
import dictionary as dict
# import foreign modules
import requests
import os
import cv2
import numpy as np
import skimage.transform
import pickle
import zmq


# Get dataset list of urls from API.
def getDatasets(datasets):
    context = zmq.Context()
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://localhost:5555")
    for dataset in datasets:
        socket.send_string(dataset)
        socket.recv()


# Parses dataset file to a list of URLs.
def parseDatasetFile(dataset):
    # open file in read-mode and output each line to a list
    file = open("../Data/Thumbnails/" + dataset + ".txt", "r")
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


# Resize images.
def resizeImages(images):
    dict.printOperation("Resizing images to " + str(dict.IMAGE_SIZE) + "x" + str(dict.IMAGE_SIZE) + "...")
    for index, image in enumerate(images):
        images[index] = np.array(skimage.transform.resize(image, (dict.IMAGE_SIZE, dict.IMAGE_SIZE), mode="constant"))
    print(dict.DONE)
    return np.array(images)


# Cache data.
def cacheData(data, labels):
    dict.printOperation("Caching data...")
    np.save("Data/cachedData.npy", data)
    with open("Data/cachedLabels.txt", "wb") as file:
        pickle.dump(labels, file)
    print(dict.DONE)


# Load cached data.
def loadCachedData():
    dict.printOperation("Loading cached data...")
    data = np.load("Data/cachedData.npy")
    with open("Data/cachedLabels.txt", "rb") as file:
        labels = pickle.load(file)
    print(dict.DONE)
    return data, labels


# Check if data is cached
def isCached():
    dict.printOperation("Checking if data is cached...")
    if os.path.exists("Data/cachedData.npy") and os.path.exists("Data/cachedLabels.txt"):
        print(dict.SUCCESS)
        return True
    else:
        print(dict.FAILED)
        return False
