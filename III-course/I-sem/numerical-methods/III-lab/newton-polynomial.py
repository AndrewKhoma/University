import numpy as np
import matplotlib.pyplot as plt


class NewtonPolynomial:
    def __init__(self, x_coord: np.array, y_coord: np.array):
        self.__coef = np.zeros_like(x_coord)
        self.__x_coord = np.zeros_like(x_coord)
        self.load(x_coord, y_coord)

    def load(self, x_coord: np.array, y_coord: np.array):
        if (x_coord.ndim != 1) or (y_coord.ndim != 1) or (len(x_coord) != len(y_coord)):
            raise ValueError("Pass 1-dimensional array with same size")

        n = len(x_coord)
        self.__coef = y_coord.copy()
        self.__x_coord = x_coord.copy()
        for k in range(1, n):
            self.__coef[k:n] = (self.__coef[k:n] - self.__coef[k - 1]) / (x_coord[k:n] - x_coord[k - 1])

    def calculate(self, x) -> float:
        n = len(self.__coef) - 1
        value = self.__coef[n]
        for k in range(1, n + 1):
            value = (x - self.__x_coord[n - k]) * value + self.__coef[n - k]

        return value


def f(x):
    return 2. * np.sin(x) + x + x ** 2 * np.cos(x)


if __name__ == '__main__':
    # equal spacing roots
    axis_x = np.linspace(0, 100., 10)
    p_eq_space = NewtonPolynomial(axis_x, f(axis_x))
    test_x = np.linspace(0., 100., 1000)
    y = p_eq_space.calculate(test_x)

    # roots of Chebyshev polynomials
    m = 2 * len(axis_x)
    root_of_chebyshev_polynom_fs_kind = np.cos(np.pi / (2 * m) * (2 * np.arange(1, m + 1) - 1))[0:int(m + 1) // 2]
    root_of_chebyshev_polynom_sd_kind = np.cos(np.pi / (1 + m) * np.arange(1, m + 1))[0:int(m + 1) // 2]
    p_chebyshev_fs_kind = NewtonPolynomial(root_of_chebyshev_polynom_fs_kind,
                                           f(root_of_chebyshev_polynom_fs_kind))

    p_chebyshev_sd_kind = NewtonPolynomial(root_of_chebyshev_polynom_sd_kind,
                                           f(root_of_chebyshev_polynom_sd_kind))

    fig, (ax, ax1) = plt.subplots(2)
    ax.grid(True)
    ax.plot(test_x, f(test_x), 'g', label='f(x)', markevery=100)
    ax.plot(test_x, y, 'k--', label='Equal spacing x')

    legend1 = ax.legend(loc='upper left', shadow=True, fontsize='x-large')
    legend1.get_frame().set_facecolor('C0')

    test_x = np.linspace(-2.5, 4.5, 1000)

    ax1.grid(True)
    ax1.plot(test_x, f(test_x), 'r', label='f(x)', markevery=100)
    ax1.plot(test_x, p_chebyshev_fs_kind.calculate(test_x), 'k--',
             label='roots of Chebyshev polynomials first kind')
    ax1.plot(test_x, p_chebyshev_sd_kind.calculate(test_x), 'b--',
             label='roots of Chebyshev polynomials second kind')

    legend2 = ax1.legend(loc='lower center', shadow=True, )
    legend2.get_frame().set_facecolor('C0')

    plt.show()
