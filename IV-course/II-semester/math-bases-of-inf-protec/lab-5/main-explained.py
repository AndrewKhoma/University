import random
import itertools

import numpy as np
from tabulate import tabulate
from typing import List, Dict


def encode_without_protection(text, key, alphabet, table, delimiter='|'):
    res_str = ""
    codes = []
    for i, ch in enumerate(text):
        key_ch = key[i % len(key)]

        text_pos = alphabet.index(ch) % len(table)
        key_pos = alphabet.index(key_ch)

        res = table[text_pos][key_pos]
        codes.append(res)
        res_str += f"{res[0]}{res[1]}" + delimiter
    return res_str, codes


def encode(text, key, alphabet, table, permutations, delimiter='|'):
    res_str = ""
    codes = []
    for i, ch in enumerate(text):
        key_ch = key[i % len(key)]

        text_pos = alphabet.index(ch) % len(table)
        key_pos = alphabet.index(key_ch)

        res = table[text_pos][key_pos]
        # randomize row
        row = random.randrange(len(table))
        col = table[row].index(res)

        a = permutations[row]
        b = permutations[col]
        codes.append((a, b))
        res_str += f"{a[0]}{a[1]}{b[0]}{b[1]}" + delimiter
    return res_str, codes


def decode_without_protection(key, alphabet, main_table, codes):
    res_str = ""
    for i, code in enumerate(codes):
        key_row = main_table[alphabet.index(key[i % len(key)])]
        res_str += alphabet[key_row.index(code)]
    return res_str


def decode(key, alphabet, main_table, permutations_map, codes):
    res_str = ""
    for i, code in enumerate(codes):
        key_row = main_table[alphabet.index(key[i % len(key)])]
        a = permutations_map[code[0]]
        b = permutations_map[code[1]]
        res = main_table[a][b]
        res_str += alphabet[key_row.index(res)]
    return res_str


def populate_table(element_mapping: Dict[int, int], second_row: List[int]) -> List[List[int]]:
    sum_dict = dict()
    # (x, y) -> value, which means x + y = value
    normalized_second_row = [element_mapping[x] for x in second_row]
    elements_size = len(element_mapping)
    for i in range(elements_size):
        sum_dict[(0, i)] = i
        sum_dict[(1, normalized_second_row[i])] = normalized_second_row[(i + 1) % elements_size]
    # so we have two rows in our table, then how can we expand it to fully
    # computed table, actually, it's quite simple.
    # from the first row you have the following, 1 + 1 = x, then we can
    # note, 'v' here is used for arbitrary element in our set of elements
    # generate a row for x, simply x + v = 1 + (1 + v), good, now we have three
    # rows, what can we evolve next, eeh, it's also kind'a obvious, in the second
    # row we have 1 + x = y, where x is the latest row, what've computed
    # so we can compute all row for 'y', as y + z = 1 + (x + y), that's it.
    # Now just change those 'x' and 'y' on the last row that you've computed
    # and the next row for computation till all rows won't be filled.
    processed_elements = {0, 1}
    x = sum_dict[(1, 1)]
    last = 1
    while len(processed_elements) != elements_size:
        for elem in range(elements_size):
            if (elem, x) in sum_dict:
                sum_dict[(x, elem)] = sum_dict[(elem, x)]
            else:
                sum_dict[(x, elem)] = sum_dict[(1, sum_dict[(last, elem)])]
        last = x
        processed_elements.add(x)
        x = sum_dict[(1, last)]

    res_table = []
    inv_mapping = {v: k for k, v in element_mapping.items()}
    for i in range(elements_size):
        res_row = []
        for j in range(elements_size):
            res_row.append(inv_mapping[sum_dict[(i, j)]])
        res_table.append(res_row)
    return res_table


if __name__ == '__main__':
    with open("input.txt") as f:
        # initial permutation, mapping between arbitrary elements of group and
        # values range(len(initial_perm)), so if 3 goes on the second position
        # than actually 3 is nothing more than 1 in the group with elements from
        # range(len(initial_perm))
        initial_perm = [int(x.strip()) for x in f.readline().split()]
        # we have initial permutation and column for the second element
        # string for the second element can be decoded in the following way:
        # current + 1 = next, and so on, pay attention that 1 could be
        # an arbitrary element and it's nothing more then numbers
        second_line = [int(x.strip()) for x in f.readline().split()]
        alphabet = f.readline().strip()
        text = f.readline().strip()
        key = f.readline().strip()

    element_mapping = {val: pos for (pos, val) in enumerate(initial_perm)}
    sum_table = populate_table(element_mapping, second_line)
    print(tabulate(sum_table, tablefmt="latex"))
    for i, ch in enumerate(alphabet):
        print(f"{i + 1}-{ch}", end=', ')
    print()

    permutations = [x for x in itertools.product(initial_perm, initial_perm)]
    for i, p in enumerate(permutations):
        print(str(i).ljust(7), end=' ')
    print()
    for p in permutations:
        print(str(p).ljust(7), end=' ')
    print()
    result_table = np.array(list(zip(range(len(permutations)), permutations)))
    result_table = np.resize(result_table, (6, 12))
    print(tabulate(result_table, tablefmt="latex"))

    permutations_map = {t: i for i, t in enumerate(permutations)}
    main_table = []
    for pair1 in permutations:
        main_table.append([])
        for pair2 in permutations:
            pos1 = element_mapping[pair1[0]], element_mapping[pair1[1]]
            pos2 = element_mapping[pair2[0]], element_mapping[pair2[1]]
            res = sum_table[pos1[0]][pos2[0]], sum_table[pos1[1]][pos2[1]]

            main_table[-1].append(res)

    str_1, codes = encode_without_protection(text, key, alphabet, main_table)
    print(str_1)
    de_str = decode_without_protection(key, alphabet, main_table, codes)
    print(de_str)

    str_2, codes_2 = encode(text, key, alphabet, main_table, permutations)
    print(str_2)
    de_str_2 = decode(key, alphabet, main_table, permutations_map, codes_2)
    print(de_str_2)
    result_table = []
    for i in range(len(main_table)):
        result_row = []
        for j in range(len(main_table)):
            if j + 1 != len(main_table):
                print(permutations_map[main_table[i][j]], end=', ')
            else:
                print(permutations_map[main_table[i][j]])
            result_row.append(permutations_map[main_table[i][j]])
        result_table.append(result_row)
    print(tabulate(result_table, tablefmt="latex"))
