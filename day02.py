from functools import reduce

LIMITS = dict(red=12, green=13, blue=14)


def part_1(puzzle_input: str) -> int:
    result = 0
    for game in puzzle_input.splitlines():
        if game and is_possible(game, LIMITS):
            result += parse_game_num(game)
    return result


def part_2(puzzle_input: str) -> int:
    return sum([game_power(game) for game in puzzle_input.splitlines() if game])


def parse_game_num(game: str) -> int:
    return int(game.split(":")[0].split()[1])


def parse_rounds(game: str) -> dict[str, int]:
    rounds = game.split(":")[1].split(";")
    result = {}
    for round in rounds:
        for hand in round.split(","):
            num, color = hand.strip().split()
            result[color] = max(int(num), result.get(color, 0))

    return result


def is_possible(game: str, limits: dict[str, int]) -> bool:
    game_result = parse_rounds(game)
    for key in game_result.keys():
        if game_result[key] > limits[key]:
            return False
    return True


def game_power(game: str) -> int:
    minimums = parse_rounds(game).values()
    return reduce(lambda x, y: x * y, minimums)


if __name__ == "__main__":
    with open("inputs/02", "r") as infile:
        puzzle_input = infile.read()
    print(f"Part 1: {part_1(puzzle_input)}")
    print(f"Part 2: {part_2(puzzle_input)}")
