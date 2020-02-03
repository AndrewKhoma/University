import time
import typing

import numpy as np

NUMBER_OF_ITERATIONS = 100000


def do_markov_calculation(iter_num: int, inp_matrix: np.array, inp_vert: np.array) -> typing.Tuple[np.array, np.array]:
    cur = np.identity(inp_matrix.shape[0], float)
    last = None
    pre_last = None
    for i in range(iter_num + 1):
        next_matrix = np.dot(cur, inp_matrix)
        if i == iter_num:
            last = np.dot(inp_vert, cur)
        elif i + 1 == iter_num:
            pre_last = np.dot(inp_vert, cur)
        cur = np.copy(next_matrix)
    return pre_last, last


if __name__ == '__main__':
    with open("input.txt") as f:
        n, m, iter_num = [int(x) for x in f.readline().split()]
        matrix = []
        for i in range(n):
            new_row = [float(x) for x in f.readline().split()]
            assert len(new_row) == m
            matrix.append(new_row)
        vert_size = int(f.readline())
        vert = [float(x) for x in f.readline().split()]
        np_matrix = np.array(matrix)
        np_vert = np.array(vert).reshape(1, vert_size)
        overall = 0
        for num_modeling in range(NUMBER_OF_ITERATIONS):
            begin = time.time_ns()
            pre_last, last = do_markov_calculation(iter_num, np_matrix, np_vert)
            end = time.time_ns()
            overall += end - begin

        print("Overall time: {0} microseconds".format(overall / (1000 * NUMBER_OF_ITERATIONS)))
        print(pre_last.flatten())
        print(last.flatten())
