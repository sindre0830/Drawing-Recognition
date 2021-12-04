# import foreign modules
import zmq
import cv2
import numpy as np
import skimage.transform
import keras.models
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

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5959")

model = keras.models.load_model("../../Data/model")

labels = [
    "Unknown", 
    "Green Apple", 
    "Banana", 
    "Strawberry", 
    "Campfire", 
    "Watermelon", 
    "Umbrella", 
    "Blueberry", 
    "Cheese",
    "Star"
]

lastGuessedIndex = 0

while True:
    # wait for next request from client
    message = socket.recv()
    # branch if terminate command is sent and break loop
    if message == b"terminate":
        socket.send(b"")
        break
    # read image and predict
    img = cv2.imread("../Data/test.jpg")
    if img is None:
        print("ERROR: Unable to read image...")
        socket.send(b"")
        continue
    img = np.array(skimage.transform.resize(img, (128, 128), mode="constant"))
    img = np.expand_dims(img, axis=0)
    predictions = model.predict(img)
    # branch if last prediction is the same as this prediction and go for the next one
    if lastGuessedIndex == np.argmax(predictions):
        lastGuessedIndex = (-predictions).argsort()[0][1]
    else:
        lastGuessedIndex = np.argmax(predictions)
    prediction = labels[lastGuessedIndex]
    # send reply back to client with prediction
    socket.send(prediction.encode())
