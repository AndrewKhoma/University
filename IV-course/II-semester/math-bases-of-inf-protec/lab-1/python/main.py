import copy
import time
import typing


def recursive_gcd(x: int, y: int) -> int:
    x = copy.copy(x)
    y = copy.copy(y)

    if x < 0:
        x = abs(x)

    if y < 0:
        y = abs(y)

    if x == 0 and y == 0:
        raise ValueError("A or B should be positive")

    if x == 0:
        return y
    elif y == 0:
        return x

    if x == y:
        return y
    elif x < y:
        return recursive_gcd(x, y % x)
    else:
        return recursive_gcd(y, x % y)


def binary_gcd(x: int, y: int) -> int:
    x = copy.copy(x)
    y = copy.copy(y)

    x = abs(x)
    y = abs(y)

    if x == 0 or y == 0:
        raise ValueError("A and B should be positive")

    if x < y:
        x, y = y, x

    result = 1

    while not (x & 1) and not (y & 1):
        x >>= 1
        y >>= 1
        result <<= 1

    while x:
        while not (x & 1):
            x >>= 1
        while not (y & 1):
            y >>= 1
        t = abs(x - y) >> 1
        if x >= y:
            x = t
        else:
            y = t

    return result * y


def binary_extended_gcd(x: int, y: int) -> typing.Tuple[int, int, int]:
    x = copy.copy(x)
    y = copy.copy(y)

    x = abs(x)
    y = abs(y)

    if x == 0 or y == 0:
        raise ValueError("A and B should be positive")

    result = 1
    while not (x & 1) and not (y & 1):
        x >>= 1
        y >>= 1
        result <<= 1

    u = copy.copy(x)
    v = copy.copy(y)
    a = 1
    b = 0
    c = 0
    d = 1

    while u:
        while not (u & 1):
            u >>= 1
            if not (a & 1) and not (b & 1):
                a >>= 1
                b >>= 1
            else:
                a = ((a + y) >> 1)
                b = ((b - x) >> 1)

        while not (v & 1):
            v >>= 1
            if not (c & 1) and not (d & 1):
                c >>= 1
                d >>= 1
            else:
                c = ((c + y) >> 1)
                d = ((d - x) >> 1)

        if u >= v:
            u -= v
            a -= c
            b -= d
        else:
            v -= u
            c -= a
            d -= b

    return c, d, result * v


if __name__ == '__main__':
    with open("input.txt") as f:
        total_time_recursive = 0
        total_time_binary = 0
        total_time_extended = 0
        for line in f:
            try:
                inputs = [int(x) for x in line.split()]
                assert len(inputs) == 3
                a = inputs[0]
                b = inputs[1]
                c = inputs[2]

                start_recursive = time.time_ns()
                gcd1 = recursive_gcd(a, b)
                end_recursive = time.time_ns()

                start_binary = time.time_ns()
                gcd2 = binary_gcd(a, b)
                end_binary = time.time_ns()

                start_extended = time.time_ns()
                x, y, gcd3 = binary_extended_gcd(a, b)
                end_extended = time.time_ns()

                total_time_recursive += end_recursive - start_recursive
                total_time_binary += end_binary - start_binary
                total_time_extended += end_extended - start_extended

                assert gcd1 == gcd2
                assert gcd2 == gcd3
                assert x * a + y * b == gcd3

                print("GCD({0}, {1}) = {2}".format(a, b, gcd2))
                print("{0} * {1} + {2} * {3} = {4}".format(a, x, b, y, gcd3))

                if c % gcd2:
                    print("Can't solve equation a * s + b * t = c")
                else:
                    mult = c / gcd2
                    print("{0} * {1} + {2} * {3} = {4}".format(a, x * mult, b, y * mult, c))

            except ValueError:
                print("Couldn't calculate GCD")

        print(
            "Overall time of execution. Recursive: {0} microsecond, Binary : {1} microsecond, Extended : {2} "
            "microseconds".format(
                total_time_recursive / 1000, total_time_binary / 1000, total_time_extended / 1000))
