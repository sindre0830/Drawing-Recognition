# import local modules
import datasetParser

datasets = ["apple_drawing", "banana", "pear", "strawberry"]

arrDatasetsURL = datasetParser.parseDatasetsFiles(datasets)

datasetParser.downloadDataset(datasets[0], arrDatasetsURL[0])
