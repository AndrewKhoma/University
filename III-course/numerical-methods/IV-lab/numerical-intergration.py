import numpy as np


def f(x):
    return 2. * np.sin(x) + x + x ** 2 * np.cos(x)


def left_rectangle(left_range: float, right_range: float, eps: float, f) -> float:
    integral = (right_range - left_range) * f(left_range)
    error = 1.
    point_num = 1
    while error > eps:
        prev_integral = integral
        point_num *= 2
        x = np.linspace(left_range, right_range - (right_range - left_range) / point_num, point_num)
        integral = (right_range - left_range) / point_num * np.sum(f(x))
        error = np.abs(integral - prev_integral) / 3.
    return integral


def simpsons(left_range: float, right_range: float, eps: float, f) -> float:
    integral = (right_range - left_range) * (
            f(left_range) + f(right_range) + 4. * f((left_range + right_range) / 2.)) / 6.
    error = 1.
    point_num = 1
    while error > eps:
        prev_integral = integral
        point_num *= 2
        delta = (right_range - left_range) / point_num
        x = np.linspace(left_range, right_range - delta, point_num)
        integral = delta / 6. * (np.sum(f(x)) + np.sum(f(x + delta)) + 4. * np.sum(f(x + delta / 2.)))
        error = np.abs(integral - prev_integral) / 15.
    return integral


if __name__ == '__main__':
    print('Left rectangle method: ', left_rectangle(1, 3, 1e-5, f))
    print('Simpson\'s method: ', simpsons(1, 3, 1e-16, f))
