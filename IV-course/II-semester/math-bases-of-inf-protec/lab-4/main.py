def vigenere_decipher(input_text: str, key: str, letter_to_pos: dict, pos_to_letter: dict):
    decipher_str = ""
    while len(decipher_str) < len(input_text):
        decipher_str += key
    deciphered_text = ""
    for i in range(len(input_text)):
        pos_decipher = letter_to_pos[decipher_str[i]]
        pos_input = letter_to_pos[input_text[i]]
        decipher_pos = (pos_input - pos_decipher) % len(letter_to_pos)
        deciphered_text += pos_to_letter[decipher_pos]
    print(deciphered_text)


if __name__ == '__main__':
    with open("input.txt") as f:
        input_text, alphabet, ciphers = [line.rstrip() for line in f.readlines()]
        ciphers = ciphers.split(',')
        letter_to_position = dict((alphabet[i], i) for i in range(len(alphabet)))
        position_to_letter = dict((i, alphabet[i]) for i in range(len(alphabet)))
        for key in ciphers:
            vigenere_decipher(input_text, key, letter_to_position, position_to_letter)
