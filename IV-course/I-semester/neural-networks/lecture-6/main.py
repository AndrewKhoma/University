import numpy as np
from sklearn import svm

if __name__ == '__main__':
    x = np.array([[0], [1], [2], [3]])
    y = np.array([0, 2, 4.1, 5.9])
    clf = svm.SVR(gamma='scale', kernel='rbf')
    clf.fit(x, y)

    print(clf.predict(np.array([[0.5], [1.5], [2.5], [3.1], [4.1]])))
