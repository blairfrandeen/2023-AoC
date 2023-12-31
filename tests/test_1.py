import pytest

import day01

from aocmodule import part1, part2


@pytest.fixture
def puzzle_input():
    with open("inputs/01", "r") as input_file:
        puzzle_input = input_file.read()
    return puzzle_input


class TestBenchmarks:
    def test_part_1_extension(self, benchmark, puzzle_input):
        result = benchmark(part1, puzzle_input)
        assert result == 54953

    def test_part_1_python(self, benchmark, puzzle_input):
        result = benchmark(day01.part_1, puzzle_input)
        assert result == 54953

    def test_part_2_extension(self, benchmark, puzzle_input):
        result = benchmark(part2, puzzle_input)
        assert result == 53868

    def test_part_2_python(self, benchmark, puzzle_input):
        result = benchmark(day01.part_2, puzzle_input)
        assert result == 53868


@pytest.mark.parametrize("word, expected", [("abc123", 1)])
def test_first_digit(word, expected):
    assert day01.first_digit(word) == expected


@pytest.mark.parametrize(
    "line, expected",
    [
        ("abc123", 13),
        ("nine10eleven12", 12),
        ("se7en", 77),
        ("", 0),
    ],
)
class TestCalVal:
    def test_cal_value(self, line, expected):
        assert day01.cal_value(line) == expected

    def test_cal_ext(self, line, expected):
        assert part1(line) == expected


SAMPLE_INPUT = """\
1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet
"""


def test_sample_1():
    assert day01.part_1(SAMPLE_INPUT) == 142


def test_sample1_ext():
    assert part1(SAMPLE_INPUT) == 142


@pytest.mark.parametrize(
    "line, expected",
    [
        ("two1nine", "219"),
        ("eightwothree", "823"),
        ("abcone2threexyz", "123"),
        ("xtwone3four", "2134"),
        ("4nineeightseven2", "49872"),
        ("fivefiveeight99", "55899"),
        ("zoneight234", "18234"),
        ("7pqrstsixteen", "76"),
    ],
)
def test_replace_word(line, expected):
    assert day01.replace_word(line) == expected


SAMPLE_INPUT_2 = """\
two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen
"""


def test_sample_2():
    assert day01.part_2(SAMPLE_INPUT_2) == 281


def test_sample2_ext():
    assert part2(SAMPLE_INPUT_2) == 281


@pytest.mark.parametrize(
    "line, substr, expected",
    [
        ("fivefive3eight", "five", [0, 4]),
        ("nine999", "9", [4, 5, 6]),
        ("dollars", "sense", []),
    ],
)
def test_findall(line, substr, expected):
    assert day01.findall(line, substr) == expected
