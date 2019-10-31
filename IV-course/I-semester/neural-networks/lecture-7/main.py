import math
import random

from matplotlib import pyplot as plt
from sklearn.cluster import KMeans


def get_input():
    inputs = list()
    for it0 in range(100):
        x = random.randint(0, 600) / 1000
        y = random.randint(0, 600) / 1000
        inputs.append([x, y])
    return inputs


def get_input_2():
    inputs = list()
    for it1 in range(100):
        x = random.randint(0, 1000) / 1000
        y = math.sqrt(1 - x * x)
        inputs.append([x, y])
    return inputs


def get_input_3():
    inputs = list()
    for it2 in range(500):
        x = random.randint(0, 1000) / 500 - 1
        y = random.randint(0, 1000) / 500 - 1
        inputs.append([x, y])
    return inputs


if __name__ == '__main__':
    # 1st task
    X = get_input()
    k_means = KMeans(n_clusters=3, random_state=0).fit(X)
    print(k_means.predict([[0.3, 0.3], [0.6, 0.9]]))
    print(k_means.cluster_centers_)

    # 2nd task
    for it in range(len(X)):
        value = X[it]
        plt.plot(value[0], value[1], 'bo',
                 color='green' if k_means.labels_[it] == 0 else 'blue' if k_means.labels_[it] == 1 else 'red')

    plt.show()
    plt.close()

    # 3rd task
    X = get_input_2()
    k_means = KMeans(n_clusters=10, random_state=0).fit(X)
    print(k_means.cluster_centers_)

    colors = ['#FA1191', '#FB2222', '#33AA33', '#44BB44', '#5555AA', '#6666BB', '#A7A777', '#8BAA8B', '#9999FF',
              '#11FFAA']

    for it in range(len(X)):
        value = X[it]
        plt.subplots_adjust(top=2.01, bottom=0.9, left=0, right=2.1)
        plt.plot(value[0], value[1], 'bo', color=colors[k_means.labels_[it]])

    plt.plot(k_means.cluster_centers_[:, 0], k_means.cluster_centers_[:, 1], 'bo', color='#000000')
    plt.show()
    plt.close()

    X = get_input_3()
    k_means = KMeans(n_clusters=6, random_state=0).fit(X)
    print(k_means.cluster_centers_)

    for it in range(len(X)):
        value = X[it]
        plt.plot(value[0], value[1], 'bo', color=colors[k_means.labels_[it]])

    plt.show()
    plt.close()
