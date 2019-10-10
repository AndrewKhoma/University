from sklearn.linear_model import Perceptron
from sklearn.metrics import accuracy_score
import numpy as np


def generate(count):
    x = []
    y = []
    for ir in range(0, count):
        math = np.random.randint(1, 6)
        physics = np.random.randint(1, 6)
        russian = np.random.randint(1, 6)
        disabled = np.random.randint(0, 2)
        x.append([math, physics, russian, disabled])
        math_plus = math >= 4
        physics_plus = physics >= 4
        sum_plus = math + physics + russian >= 11
        y.append(1 if disabled == 1 or (math_plus and physics_plus and sum_plus) else 0)
    return np.array(x), np.array(y)


if __name__ == '__main__':
    X, y = generate(100)
    X_test, y_test = generate(20)
    perceptron = Perceptron(tol=0.0000001)
    perceptron.fit(X, y)
    predict = perceptron.predict(X_test)
    accuracy_score(predict, y_test)

    x_example = [[3, 3, 5, 1]]
    print("Passed" if perceptron.predict(x_example) == 1 else "Not passed")
