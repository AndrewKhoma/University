from keras.models import Sequential
from keras.layers import Dense
import numpy as np
import matplotlib.pyplot as plt


def train_model(local_model, x, y, x_test, epoch_number, batch_number, f, picture_name):
    x = x.reshape(x.shape[0], 1)
    y = y.reshape(y.shape[0], 1)
    x_test = x_test.reshape(x_test.shape[0], 1)
    local_model.fit(x, y, epochs=epoch_number, batch_size=batch_number)

    y_test = local_model.predict(x_test).reshape(-1)
    for it in range(0, y_test.shape[0]):
        print("Real value =", f(x_test[it]), ", model value =", y_test[it])

    # Make a nice graphic!
    plt.plot(x, y, '.', label='Raw noisy input data')
    plt.plot(x, y, label='Actual function, not noisy', linewidth=4.0, c='black')
    plt.plot(x_test, y_test, label='Output of the Neural Net', linewidth=4.0, c='red')
    plt.legend()
    plt.savefig(picture_name)
    plt.close()


if __name__ == '__main__':
    # Model creation: adding layers and compilation
    model = Sequential()
    model.add(Dense(12, input_dim=1, activation='relu'))
    model.add(Dense(1, activation='linear'))
    model.compile(optimizer='sgd', loss='mse', metrics=['mse'])

    train_model(model,
                np.array([-2, -1.8, -1.5, -0.9, 0.1, 0.3, 0.6, 1.9, 2]),
                np.array([1.33, 1.08, 0.75, 0.27, 0.003, 0.03, 0.12, 1.2, 1.33]),
                np.array([-1, -0.2, 1, 2]),
                128,
                9,
                lambda value: value ** 2 / 3,
                'neural-network-keras-function-interpolation-1.png')

    train_model(model,
                np.array([-1, -0.8, -0.5, -0.2, 0.1, 0.3, 0.6, 0.8, 1]),
                np.array([0, 0.488, 0.875, 0.992, 1.001, 1.027, 1.216, 1.512, 2]),
                np.array([-1, -0.2, 1, 2]),
                128,
                3,
                lambda value: value ** 3 + 1,
                'neural-network-keras-function-interpolation-2.png')

    train_model(model,
                np.array([-3, -2.8, -1.5, -0.2, 0, 1.3, 2.6, 2.9, 3]),
                np.array([15, 12.88, 3, -0.12, 0, 4.68, 16.12, 19.72, 21]),
                np.array([-1, -0.2, 1, 2]),
                128,
                3,
                lambda value: 2 * value ** 2 + value,
                'neural-network-keras-function-interpolation-3.png')
