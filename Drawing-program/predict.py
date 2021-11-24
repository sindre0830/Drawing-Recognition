import zmq
import cv2
import numpy as np
import skimage.transform
import keras.models

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5959")

model = keras.models.load_model("../../Data/model")

labels = ["unknown", "apple", "banana", "strawberry", "clock", "ghost", "cupcake"]

while True:
    #  Wait for next request from client
    message = socket.recv()

    if message == b"terminate":
        print("Terminating program...")
        break

    img = cv2.imread("../Data/test.jpg")
    if img is None:
        print("error")
        socket.send(b"")
        continue
    
    img = np.array(skimage.transform.resize(img, (128, 128), mode="constant"))
    img = np.expand_dims(img, axis=0)
    predictions = model.predict(img)
    prediction = labels[np.argmax(predictions)]

    print(prediction)

    #  Send reply back to client
    socket.send(b"")
