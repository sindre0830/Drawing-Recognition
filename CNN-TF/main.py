# import local modules
import dictionary as dict
import datasetParser
from model import (
    generateModel
)


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
# generate model and print design
model = generateModel()
model.summary()
