# dataset to integer code
DATASET_INTEGER_CONVERTER = {
    "green_apple_drawing": 1,
    "single_yellow_banana_isolated": 2,
    "single_strawberry_isolated": 3,
    "campfire_cartoon": 4,
    "single_watermelon_slice": 5,
    "single_umbrella_drawing_isloated": 6,
    "single_blueberry_isolated": 7,
    "single_isolated_yellow_star": 8
}
# status messages
DONE = 'DONE'
SUCCESS = 'SUCCESS'
FAILED = 'FAILED'
# set parameters
IMAGE_SIZE = 128
SHAPE = (IMAGE_SIZE, IMAGE_SIZE, 3)
DATASET_AMOUNT = len(DATASET_INTEGER_CONVERTER) + 1
LEARNING_RATE = 0.001
TRAIN_SIZE = 0.80
BATCH_SIZE = 500
EPOCHS = 50


# Print operation that allows status message on the same line.
def printOperation(message):
    print('{:<60s}'.format(message), end="", flush=True)


# Print divider in console.
def printDivider():
    print("\n")
