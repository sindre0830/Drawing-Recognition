# import local modules
import dictionary as dict
# import foreign modules
import keras.models
import keras.layers.convolutional
import keras.layers.pooling
import keras.layers.core
import tensorflow.keras.optimizers


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
        optimizer=tensorflow.keras.optimizers.Adam(learning_rate=0.01),
        loss='categorical_crossentropy',
        metrics=['accuracy']
    )
    return model
