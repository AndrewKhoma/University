import numpy as np


def boundary_check(x_inside: float, x_left: float, x_right: float) -> None:
    if not (x_left <= x_inside <= x_right):
        raise ValueError(
            "Starting approximation: {0}, doesn't belong search interval: [{1}, {2}]".format(x_inside, x_left, x_right))


def simple_iteration(f: np.poly1d, x_left: float, x_right: float, x_start: float, trans_f: np.poly1d,
                     eps: float = 1e-4) -> float:
    """

    :param f: desired function
    :param x_left: left border where root belong
    :param x_right: right border where root belong
    :param x_start: starting approximation
    :param trans_f: transition function
    :param eps: method accuracy
    :return: approximated root
    """

    boundary_check(x_start, x_left, x_right)

    x_values = np.linspace(x_left, x_right, min(int(1. / eps), 10 ** 5))

    trans_der = np.polyder(trans_f)

    max_value = np.max(np.abs(trans_der(x_values)))

    if max_value > 1:
        raise ValueError('Absolute value of phi derivative should be less than 1, but you have {0}.'.format(max_value)
                         + 'Choose another [left_x, right_x]')

    estimated_num_iteration = int(
        np.ceil(np.log(np.abs(trans_f(x_start) - x_start) / (eps * (1. - max_value))) / np.log(1. / max_value))) + 1

    x_i, x_prev = x_start, x_start - 2 * eps
    num_iteration = 0

    while abs(x_i - x_prev) >= eps:
        x_i, x_prev = trans_f(x_i), x_i
        num_iteration += 1

    print('Simple iteration method. Apriori iteration number: {0}, aposteriori iteration number: {1}'.format(
        estimated_num_iteration, num_iteration))

    return x_i


def relaxation(f: np.poly1d, x_left: float, x_right: float, x_start: float, eps: float = 1e-4) -> float:
    """

    :param f: desired function
    :param x_left: left border where root belong
    :param x_right: right border where root belong
    :param x_start: starting approximation
    :param eps: method accuracy
    :return: approximated root
    """

    boundary_check(x_start, x_left, x_right)

    x_values = np.linspace(x_left, x_right, min(int(1. / eps), 10 ** 5))
    f_der = np.polyder(f)

    min_value, max_value = np.min(np.abs(f_der(x_values))), np.max(np.abs(f_der(x_values)))

    tau = 2. / (min_value + max_value)
    q = (max_value - min_value) / (min_value + max_value)

    x_i, x_prev = x_start, x_start - 2 * eps
    num_iteration = 0

    while abs(x_i - x_prev) >= eps:
        x_i, x_prev = x_i - np.sign(f_der(x_i)) * f(x_i) * tau, x_i
        num_iteration += 1

    estimated_num_iteration = int(np.ceil(np.log(np.abs(x_start - x_i) / eps) / np.log(1. / q))) + 1

    print('Relaxtion method. Apriori iteration number: {0}, aposteriori iteration number: {1}'.format(
        estimated_num_iteration, num_iteration))

    return x_i


if __name__ == '__main__':
    f = np.poly1d([1, -4, -7, 13])
    phi = np.poly1d([1. / 7., -4. / 7., 0, 13. / 7.])

    simple_iter_root = simple_iteration(f, 1., 2., 1.5, phi)
    print('Simple iteration root: ', simple_iter_root)

    relaxation_root = relaxation(f, 1., 2., 1.5)
    print('Relaxation root: ', relaxation_root)
