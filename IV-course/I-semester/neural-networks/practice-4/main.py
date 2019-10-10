import numpy as np
from keras.layers import Dense
from keras.models import Sequential
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split


def generate_output(input_arr):
    if input_arr[-1]:
        return np.min(input_arr[:3]) >= 3
    elif np.min(input_arr[:2]) >= 4:
        return np.sum(input_arr[:3]) >= 11
    else:
        return 0


def generate_inputs():
    input_arr = []
    for math in range(1, 6):
        for physics in range(1, 6):
            for russian in range(1, 6):
                for disabled in range(2):
                    input_arr.append([math, physics, russian, disabled])
    return input_arr


def generate_inputs_and_outputs():
    input_arr = generate_inputs()
    output = []
    for grades in input_arr:
        output.append(generate_output(grades))
    return np.array(input_arr), np.array(output)


def generate_model(layers):
    model = Sequential()
    model.add(Dense(layers[0], input_dim=4, activation='relu'))
    for layer in layers[1:]:
        model.add(Dense(layer, activation='relu'))
    model.add(Dense(1, activation='sigmoid'))
    model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
    return model


def train_model(local_model, x_train, y_train, x_test, y_test, epoch_number, batch_number):
    local_model.fit(x_train, y_train, epochs=epoch_number, batch_size=batch_number, verbose=False)
    y_predicted_test = (local_model.predict(x_test).reshape(-1) > 0.5).astype(int)
    return accuracy_score(y_test, y_predicted_test)


if __name__ == '__main__':
    x, y = generate_inputs_and_outputs()
    train_x, test_x, train_y, test_y = train_test_split(x, y, test_size=0.33, random_state=42)
    first_model = generate_model([12])
    print(train_model(first_model, train_x, train_y, test_x, test_y, 128, 8))
    print(train_model(first_model, train_x, train_y, test_x, test_y, 256, 8))
    second_model = generate_model([12, 12])
    print(train_model(second_model, train_x, train_y, test_x, test_y, 128, 8))
    print(train_model(second_model, train_x, train_y, test_x, test_y, 256, 8))
