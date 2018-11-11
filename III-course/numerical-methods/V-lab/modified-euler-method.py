import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error


def integrate(der, x_st, y_st, x_right, h):
    def mod_euler(der, x, y, h):
        k0 = h * der(x, y)
        k1 = h * der(x + h / 2.0, y + k0 / 2.0)
        return k1

    x = []
    y = []
    x_i = np.arange(x_st, x_right + h, h)
    x_i[-1] = x_right
    for i in range(1, len(x_i)):
        h = x_i[i] - x_i[i - 1]
        y_st = y_st + mod_euler(der, x_st, y_st, h)
        x_st += h
        x.append(x_st)
        y.append(y_st)
    return np.array(x), np.array(y)


def der(x, y):
    der_y = np.zeros(2)
    der_y[0] = y[1]
    der_y[1] = -0.1 * y[1] - x
    return der_y


if __name__ == '__main__':
    x_st = 0.
    x_r = 2.
    y = np.array([0., 1.])
    h = 0.2

    x_func, y_func = integrate(der, x_st, y, x_r, h)
    y_exact = 100.0 * x_func - 5.0 * x_func ** 2 + 990.0 * (np.exp(-0.1 * x_func) - 1.0)
    print('Mean square error: ', mean_squared_error(y_exact, y_func[:, 0]))

    plt.plot(x_func, y_func[:, 0], 'o', x_func, y_exact, '-')
    plt.grid(True)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend(('Numerical', 'Exact'), loc=0)
    plt.show()
