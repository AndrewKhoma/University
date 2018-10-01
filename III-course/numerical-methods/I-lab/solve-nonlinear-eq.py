def f(x: float) -> float:
    return x ** 3 - 4 * x ** 2 - 7 * x + 13


def f_derivative(x: float) -> float:
    return 6 * x - 8


if __name__ == '__main__':
    print('Working')
