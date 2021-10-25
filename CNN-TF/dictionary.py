# dataset to integer code
DATASET_INTEGER_CONVERTER = {
    "apple_drawing": 1,
    "banana": 2,
    "pear": 3,
    "strawberry": 4,
    "clock": 5,
    "ghost_drawing": 6
}
# status messages
DONE = 'DONE'
SUCCESS = 'SUCCESS'
FAILED = 'FAILED'
# set parameters
IMAGE_SIZE = 128
SHAPE = (IMAGE_SIZE, IMAGE_SIZE, 3)
DATASET_AMOUNT = len(DATASET_INTEGER_CONVERTER) + 1
LEARNING_RATE = 0.01
TRAIN_SIZE = 0.80
BATCH_SIZE = 500
EPOCHS = 50


# Print operation that allows status message on the same line.
def printOperation(message):
    print('{:<40s}'.format(message), end="", flush=True)


# Print divider in console.
def printDivider():
    print("\n")
