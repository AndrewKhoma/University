import numpy as np

if __name__ == '__main__':
    inputs = np.array([4, 5, 6, 7])
    initDelay = np.array([3, 2, 1])
    output = np.array([10, 15, 20, 25])
    weights = np.array([1, 1, 1])
    bias = 1
    epoch = 10
    for it in range(epoch):
        delay = initDelay
        dw = np.zeros(3)
        db = 0
        for inputIter in range(len(inputs)):
            delay = np.concatenate([np.array([inputs[inputIter]]), delay[:2]])
            res = np.dot(delay, weights) + bias
            dw += 2 * (res - output[inputIter]) * delay
            db += 2 * (res - output[inputIter])
        dw /= len(inputs)
        weights = weights - 0.01 * dw
        bias -= 0.01 * (db / len(inputs))

    delay = initDelay
    for inputIter in range(len(inputs)):
        delay = np.concatenate([np.array([inputs[inputIter]]), delay[:2]])
        res = np.dot(delay, weights) + bias
        print("Expected = ", output[inputIter], ", actual =", res)

    delay = np.array([8, 7, 6])
    print(np.dot(delay, weights) + bias)
