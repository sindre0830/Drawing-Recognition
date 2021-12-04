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

labels = ["Unknown", "Apple", "Banana", "Strawberry", "Campfire", "Watermelon", "Umbrella", "Blueberry", "Star"]

while True:
    #  Wait for next request from client
    message = socket.recv()

    if message == b"terminate":
        socket.send(b"")
        break

    img = cv2.imread("../Data/test.jpg")
    if img is None:
        print("ERROR: Unable to read image...")
        socket.send(b"")
        continue
    
    img = np.array(skimage.transform.resize(img, (128, 128), mode="constant"))
    img = np.expand_dims(img, axis=0)
    predictions = model.predict(img)
    prediction = labels[np.argmax(predictions)]

    #  Send reply back to client
    socket.send(prediction.encode())
