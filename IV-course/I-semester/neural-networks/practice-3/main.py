import numpy as np
from matplotlib import pyplot as plt


def hard_limit(arg):
    return 1 if arg >= 0 else 0


def hard_limit_array(array_argument: np.array):
    res = np.full_like(array_argument, 1)
    for i in range(0, array_argument.shape[0]):
        res[i] = hard_limit(array_argument[i])
    return res


def make_out(weight, bias, first_param, second_param):
    inner_output = first_param * weight[0] + second_param * weight[1] + bias
    return hard_limit(inner_output)


def run_all_variants(weight, bias):
    print("weights =", weight, ", b =", bias)
    for it1 in range(0, 2):
        for it2 in range(0, 2):
            print(it1, it2, "output", make_out(weight, bias, it1, it2))


def func(k, value, bias):
    return k * value + bias


if __name__ == '__main__':
    # 1st task
    print(hard_limit(arg=-1))
    print(hard_limit(arg=0))
    print(hard_limit(arg=1))
    print(hard_limit_array(np.array([-1, 0, 1])))
    # 2nd task
    print("A")
    run_all_variants(np.array([1, 0]), -1)
    print("B")
    run_all_variants(np.array([-1, -1]), 1)
    print("Variants C and D don't have solutions")
    print("Proof for C: on 00 we have 0 class then b is less than 0,"
          " also 01 and 10 have 1 class, then w1 and w2 bigger than -b.")
    print("But 11 has 0 class that means w1 + w2 should be less than -b but this is impossible.")
    # 3rd task
    w1 = 5
    w2 = -10
    b = 2
    x = np.arange(0, 6, 0.1)
    y = np.array([func(-(w1 / w2), elem, -(b / w2)) for elem in x])
    plt.plot(x, y)
    for it in range(100):
        p1 = np.random.uniform() * 6
        p2 = np.random.uniform() * 6
        plt.plot([p1], [p2], 'bo', color='green' if hard_limit(p1 * w1 + p2 * w2 + b) else 'red')
    plt.savefig('division')
