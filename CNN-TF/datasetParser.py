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
