# Convolutional Neural Network

Requires the data-collection server to run when downloading new datasets. Add the search query in the dictionary.py and the label in Drawing-program/prediction.py in the labels array and Drawing-program/Scenes/GameScene.cpp in the words vector.

To force new datasets to be downloaded, open the Data directory and delete the .npy files.

## Installation guide

Requires Python
```sh
# Install dependencies
pip install requests opencv-python scikit-image keras tensorflow sklearn numpy pyzmq
# Build
python main.py
```