def do_caesar_shift(shift: int, text: str, letter_to_pos: dict, pos_to_letter: dict):
    new_str = ""
    for symb in text:
        pos = letter_to_pos[symb]
        new_pos = (pos + shift) % len(letter_to_pos)
        new_str += pos_to_letter[new_pos]
    print(shift, new_str)


if __name__ == '__main__':
    with open("input.txt") as f:
        input_text, cipher = [line.rstrip() for line in f.readlines()]
        letter_to_position = dict((cipher[i], i) for i in range(len(cipher)))
        position_to_letter = dict((i, cipher[i]) for i in range(len(cipher)))
        for shift in range(len(cipher)):
            do_caesar_shift(-shift, input_text, letter_to_position, position_to_letter)
