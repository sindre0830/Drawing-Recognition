# import local modules
import dictionary as dict
from datasetParser import (
    isCached,
    loadCachedData,
    downloadDatasets,
    parseDatasets,
    resizeImages,
    cacheData,
    getDatasets
)
from model import (
    generateModel,
    splitData,
    trainModel,
    predictModel,
    calculateCrossValidation,
    plotResults,
    saveModel,
    predictImage
)
# import foreign modules
import os
import tensorflow as tf

# suppress info and warnings outputted by tensorflow
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
tf.compat.v1.logging.set_verbosity(tf.compat.v1.logging.ERROR)
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
if isCached():
    data, labels = loadCachedData()
else:
    # get dataset files with URLs from API
    getDatasets(datasets)
    downloadDatasets(datasets)
    data, labels = parseDatasets(datasets)
    data = resizeImages(data)
    cacheData(data, labels)
dict.printDivider()

model = generateModel()
model.summary()
dict.printDivider()

calculateCrossValidation(data, labels)
dict.printDivider()

# split data into training- and testing set
xTrain, xTest, yTrain, yTest = splitData(data, labels)
model, results = trainModel(model, xTrain, xTest, yTrain, yTest)
dict.printDivider()

# predict on testing set and output results
predictModel(model, xTest, yTest, datasets)
plotResults(results)
dict.printDivider()

# test model on dummy data
predictImage(model, "apple.jpg")
predictImage(model, "strawberry.jpg")
predictImage(model, "banana.jpg")
dict.printDivider()

# prompt user to save the model
saveModel(model)
