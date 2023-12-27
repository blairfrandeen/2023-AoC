import pytest

import day02

game1 = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
game3 = "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red"


def test_parse_game_num():
    assert day02.parse_game_num(game1) == 1


def test_parse_rounds():
    res = day02.parse_rounds(game1)
    assert res["blue"] == 6
    assert res["red"] == 4
    assert res["green"] == 2


@pytest.fixture
def puzzle_input():
    with open("inputs/02", "r") as input_file:
        puzzle_input = input_file.read()
    return puzzle_input


TEST_INPUT = """
Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
"""


@pytest.mark.parametrize("game, power", [(game1, 48), (game3, 1560)])
def test_power(game, power):
    assert day02.game_power(game) == power


def test_part_1_sample():
    assert day02.part_1(TEST_INPUT) == 8


def test_part_2_sample():
    assert day02.part_2(TEST_INPUT) == 2286


def test_part_1(puzzle_input, benchmark):
    result = benchmark(day02.part_1, puzzle_input)
    assert result == 2528


def test_part_2(puzzle_input, benchmark):
    result = benchmark(day02.part_2, puzzle_input)
    assert result == 67363


@pytest.mark.parametrize("game, possible", [(game1, True), (game3, False)])
def test_is_possible(game, possible):
    assert day02.is_possible(game, day02.LIMITS) is possible
    # assert day02.is_possible(game1, day02.LIMITS)
