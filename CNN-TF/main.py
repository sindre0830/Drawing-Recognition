# import local modules
import dictionary as dict
import datasetParser
from model import (
    generateModel,
    splitData,
    trainModel,
    predictModel,
    calculateCrossValidation
)
# import foreign modules
import os
import tensorflow as tf

# suppress info and warnings outputted by tensorflow
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
# enable memory growth for gpu devices
# source: https://stackoverflow.com/a/55541385/8849692
gpu_devices = tf.config.experimental.list_physical_devices('GPU')
if gpu_devices:
    for devices in gpu_devices:
        tf.config.experimental.set_memory_growth(devices, True)
dict.printDivider()
# get dataset names from dictionary
datasets = []
for dataset in dict.DATASET_INTEGER_CONVERTER:
    datasets.append(dataset)
# check if data is cached
if datasetParser.isCached():
    data, labels = datasetParser.loadCachedData()
else:
    # download datasets
    datasetParser.downloadDatasets(datasets)
    # parse datasets
    data, labels = datasetParser.parseDatasets(datasets)
    # resize images
    data = datasetParser.resizeImages(data)
    # cache data
    datasetParser.cacheData(data, labels)
dict.printDivider()
# generate model
model = generateModel()
model.summary()
dict.printDivider()
# calculate cross validation on dataset
calculateCrossValidation(data, labels)
# split data into training- and testing set
xTrain, xTest, yTrain, yTest = splitData(data, labels)
# train model
model, results = trainModel(model, xTrain, xTest, yTrain, yTest)
dict.printDivider()
# output prediction results
predictModel(model, xTest, yTest, datasets)
