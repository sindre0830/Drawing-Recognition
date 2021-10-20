# import local modules
import datasetParser


datasets = ["apple_drawing", "banana", "pear", "strawberry"]

arrDatasetsURL = datasetParser.parseDatasetsFile(datasets)

datasetParser.downloadDatasets(datasets, arrDatasetsURL)
