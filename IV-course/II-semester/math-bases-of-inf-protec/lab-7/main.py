import numpy as np
from tabulate import tabulate

if __name__ == '__main__':
    with open("input.txt") as f:
        mat_size = int(f.readline().strip())
        matrix = []
        for i in range(mat_size):
            new_row = [int(x.strip()) for x in f.readline().split()]
            assert len(new_row) == mat_size
            matrix.append(new_row)
        matrix_np = np.array(matrix)
        alphabet = f.readline().strip() + ' '
        coded_word = f.readline().strip()
        encoded_word = [int(x.strip()) for x in f.readline().split()]
    inv_matrix = np.linalg.inv(matrix_np)
    print(tabulate(matrix, tablefmt="latex"))
    print(tabulate(inv_matrix, tablefmt="latex"))
    alphabet_encoding = {ch: (i + 1) for i, ch in enumerate(alphabet)}
    inverse_alphabet = {(i + 1): ch for i, ch in enumerate(alphabet)}
    if len(coded_word) % 3:
        coded_word += ' ' * (3 - len(coded_word) % 3)
    id = 0
    while id < len(coded_word):
        text = coded_word[id:id + 3]
        column = [alphabet_encoding[ch] for ch in text]
        np_column = np.array(column)
        print(np.dot(matrix_np, np_column.T), end=' ')
        id += 3
    id = 0
    decoded_word = ''
    print()
    while id < len(encoded_word):
        column = np.array(encoded_word[id:id + 3])
        decoded = np.dot(column, inv_matrix.T)
        for x in decoded:
            correct_x = int(round(x))
            decoded_word += str(inverse_alphabet[correct_x])
        id += 3
    print(decoded_word)
