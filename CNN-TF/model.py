# import local modules
import dictionary as dict
# import foreign modules
import keras.models
import keras.layers.convolutional
import keras.layers.pooling
import keras.layers.core
import tensorflow.keras.optimizers
import tensorflow.keras.wrappers.scikit_learn
import sklearn.model_selection
import sklearn.metrics
import keras.utils.np_utils
import numpy as np
import matplotlib.pyplot as plt


# Generate convolutional neural network model.
def generateModel():
    model = keras.models.Sequential([
        # layer 1
        keras.layers.convolutional.Conv2D(filters=32, kernel_size=3, input_shape=dict.SHAPE, activation='relu'),
        keras.layers.pooling.MaxPooling2D(pool_size=(2, 2)),
        # layer 2
        keras.layers.convolutional.Conv2D(filters=32, kernel_size=3, activation='relu'),
        keras.layers.pooling.MaxPooling2D(pool_size=(2, 2)),
        # layer 3
        keras.layers.convolutional.Conv2D(filters=64, kernel_size=3, activation='relu'),
        keras.layers.pooling.MaxPooling2D(pool_size=(2, 2)),
        # flatten
        keras.layers.core.Flatten(),
        # layer 4
        keras.layers.core.Dense(units=64, activation='relu'),
        keras.layers.core.Dropout(rate=0.5),
        # layer 5
        keras.layers.core.Dense(units=dict.DATASET_AMOUNT, activation='sigmoid')
    ])
    model.compile(
        optimizer=tensorflow.keras.optimizers.Adam(learning_rate=dict.LEARNING_RATE),
        loss='categorical_crossentropy',
        metrics=['accuracy']
    )
    return model


# Perform tain-test-split.
def splitData(data, labels):
    xTrain, xTest, yTrain, yTest = sklearn.model_selection.train_test_split(data, labels, train_size=dict.TRAIN_SIZE, random_state=0)
    yTrain = keras.utils.np_utils.to_categorical(yTrain, num_classes=dict.DATASET_AMOUNT)
    yTest = keras.utils.np_utils.to_categorical(yTest, num_classes=dict.DATASET_AMOUNT)
    return xTrain, xTest, yTrain, yTest


# Train model and evaluate when finished.
def trainModel(model: keras.models.Sequential, xTrain, xTest, yTrain, yTest):
    # fit model by parameters
    results = model.fit(
        xTrain,
        yTrain,
        batch_size=dict.BATCH_SIZE,
        epochs=dict.EPOCHS,
        verbose=False,
        validation_data=(xTest, yTest)
    )
    # evaluate model and output results
    model.evaluate(xTest, yTest)
    return model, results


# Predict model and output classification report and confusion matrix.
def predictModel(model: keras.models.Sequential, xTest, yTest, datasets):
    # predict dataset on model
    yPred = model.predict(xTest)
    # flatten each array to get index of highest value
    yPred = np.argmax(yPred, axis=1)
    yTest = np.argmax(yTest, axis=1)
    # print classification report and confusion matrix
    print(sklearn.metrics.classification_report(yTest, yPred, target_names=datasets, zero_division=1))
    print(sklearn.metrics.confusion_matrix(yTest, yPred))


def calculateCrossValidation(data, labels):
    labels = keras.utils.np_utils.to_categorical(labels, num_classes=dict.DATASET_AMOUNT)
    # set parameters for cross validation model
    crossValidationModel = tensorflow.keras.wrappers.scikit_learn.KerasClassifier(
        build_fn=generateModel,
        batch_size=dict.BATCH_SIZE,
        epochs=dict.EPOCHS,
        verbose=False
    )
    kfold = sklearn.model_selection.KFold(n_splits=5, shuffle=True, random_state=0)
    # calculate cross validation and output results
    results = sklearn.model_selection.cross_val_score(crossValidationModel, data, labels, cv=kfold)
    print("Cross validation results: " + str(results))
    print("%0.2f accuracy with a standard deviation of %0.2f" % (results.mean(), results.std()))


# Plots a graph with the results from model training.
def plotResults(results):
    # get values from results
    history_dict = results.history
    loss_values = history_dict['loss']
    val_loss_values = history_dict['val_loss']
    val_accuracy = history_dict['val_accuracy']
    epochs = range(1, (len(history_dict['loss']) + 1))
    # plot training and validation loss
    plt.clf()
    plt.plot(epochs, loss_values, label='Training loss', c='lightgreen')
    plt.plot(epochs, val_loss_values, label='Validation loss')
    plt.title('Training and validation loss')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend()
    plt.show()
    # plot validation accuracy
    plt.clf()
    plt.plot(epochs, val_accuracy, label='Validation accuracy', c='red')
    plt.title('Validation accuracy')
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy')
    plt.ylim(0, 1)
    plt.legend()
    plt.show()


def saveModel(model: keras.models.Sequential):
    inp = input("Do you want to save the model? Y/N: ")
    if inp.lower() == "y":
        model.save("../Data/model.h5", save_format='h5')
