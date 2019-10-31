import math
import random

import numpy as np
from sklearn import svm


def get_data():
    inputs = list()
    outputs = list()
    for x in range(-10, 10):
        for y in range(50):
            for z in range(10, 50):
                inputs.append([x / 10, y / 10, z / 10])
                outputs.append([math.pow(x / 10, 2) + 2 * (x / 10) * (y / 10) - math.sqrt(z / 10)])
    return np.array(inputs), np.array(outputs)


if __name__ == '__main__':
    X, y = get_data()
    y = y.ravel()

    clf = svm.SVR(gamma='scale', kernel='rbf')
    clf.fit(X, y)

    for itr in range(10):
        x = random.randint(0, 100) / 100 * 2 - 1
        y = random.randint(0, 100) / 100 * 5
        z = random.randint(0, 100) / 100 * 4 + 1
        pred = clf.predict([[x, y, z]])
        res = (x * x + 2 * x * y - math.sqrt(z))
        er = abs(pred[0] - res)
        print("Arguments: x = %.2f, y = %.2f, z = %.2f, net predict = %f, actual result = %f, error = %f" % (
            x, y, z, pred[0], res, er))
