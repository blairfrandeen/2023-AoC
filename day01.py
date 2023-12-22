from typing import Optional


def first_digit(word: str) -> int:
    for char in word:
        if char.isdigit():
            return int(char)
    return 0


def cal_value(line: str) -> int:
    return first_digit(line) * 10 + first_digit(line[::-1])


def part_1(puzzle_input: str) -> int:
    return sum(map(cal_value, puzzle_input.splitlines()))


SPELLED_DIGITS = dict(
    zip("one two three four five six seven eight nine".split(), range(1, 10))
)


def replace_word(line: str) -> str:
    matches = []
    for number, digit in SPELLED_DIGITS.items():
        number_matches = findall(line, number)
        for match in number_matches:
            matches.append((match, str(digit)))
        digit_matches = findall(line, str(digit))
        for match in digit_matches:
            matches.append((match, str(digit)))
    matches = sorted([m for m in matches if m[0] >= 0])
    return "".join([m[1] for m in matches])


def findall(line: str, substr: str) -> list[int]:
    start_index = 0
    results = []
    while True:
        res = line.find(substr, start_index)
        if res < 0:
            break
        start_index = res + 1
        results.append(res)
    return results


def part_2(puzzle_input: str) -> int:
    return sum(map(cal_value, map(replace_word, puzzle_input.splitlines())))
