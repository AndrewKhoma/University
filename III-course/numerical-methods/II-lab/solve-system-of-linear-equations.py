"""
Created by ahoma at 21/10/18 12:25

Author: Andrii Khoma

File: solve-system-of-linear-equations
"""

import numpy as np
from typing import Tuple, Union


def gauss_main_by_column(a_matrix: np.ndarray, b: np.array, find_conditon_num=False) -> Union[
    Tuple[np.array, float], Tuple[np.array, float, float]]:
    """

    :param a_matrix: input matrix A[i]*x^T = b[i]
    :param b: value vector
    :param find_conditon_num: should function look for condition num
    :return: solution vector

    """

    if a_matrix.ndim != 2 or a_matrix.shape[0] != a_matrix.shape[1]:
        raise ValueError("A should be square matrix")

    if b.ndim != 1 or b.shape[0] != a_matrix.shape[0]:
        raise ValueError("b should be vector value")

    if np.isclose(np.linalg.det(a_matrix), 0):
        raise ValueError("A should have determinant not equal zero")

    n = a_matrix.shape[0]

    determinant = 1.

    id_matrix = np.identity(n)

    for iteration in range(n):
        # selecting biggest value in column
        max_col = np.argmax(np.abs(a_matrix[iteration:n, [iteration]])) + iteration

        if max_col != iteration:
            determinant *= -1.

        # forming matrix permutation
        permutation_matrix = np.identity(n)
        permutation_matrix[[iteration, max_col]] = permutation_matrix[[max_col, iteration]]
        a_matrix = permutation_matrix @ a_matrix
        b = permutation_matrix @ b
        id_matrix = permutation_matrix @ id_matrix

        determinant *= a_matrix[iteration, iteration]

        # calculating matrix M
        m_matrix = np.identity(n)
        m_matrix[iteration, iteration] = 1. / float(a_matrix[iteration, iteration])
        for i in range(iteration + 1, n):
            m_matrix[i, iteration] = float(-a_matrix[i, iteration]) / float(a_matrix[iteration, iteration])

        # forming new iteration matrix
        a_matrix = m_matrix @ a_matrix
        b = m_matrix @ b
        id_matrix = m_matrix @ id_matrix

    x = b

    for i in range(n - 1, -1, -1):
        x[i] -= sum(a_matrix[i, j] * x[j] for j in range(i + 1, n))

    if not find_conditon_num:
        return x, determinant
    else:
        a_inverse = np.ndarray(shape=(n, n), dtype=float)
        for it in range(n):
            inv_col = id_matrix[:, [it]].reshape(-1)

            for i in range(n - 1, -1, -1):
                inv_col[i] -= sum(a_matrix[i, j] * inv_col[j] for j in range(i + 1, n))

            a_inverse[:, [it]] = inv_col.reshape(n, 1)

        a_matrix_norm = np.linalg.norm(a_matrix)
        a_inverse_norm = np.linalg.norm(a_inverse)

        condition_num = a_matrix_norm * a_inverse_norm
        return x, determinant, condition_num


if __name__ == '__main__':
    a = np.array([[10, 0, 3], [3, -1, 0], [-2, 4, 1]])
    b_vec = np.array([7, 2, 1])
    (sol, det, cond_num) = gauss_main_by_column(a, b_vec, True)
    print('X: ', sol, 'Determinant: ', np.round(det, 3), 'Condition number: ', np.round(cond_num, 3))
