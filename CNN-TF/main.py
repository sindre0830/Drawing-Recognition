# import local modules
import dictionary as dict
import datasetParser


# get dataset names from dictionary
datasets = []
for dataset in dict.DATASET_INTEGER_CONVERTER:
    datasets.append(dataset)
# download datasets
datasetParser.downloadDatasets(datasets)
# parse datasets
data, labels = datasetParser.parseDatasets(datasets)
# resize images
data = datasetParser.resizeImages(data)
# cache data
datasetParser.cacheData(data)
