import argparse
import random

DIGITS = list("123456789")
CHARS = list("abcdefghijklmnopqrstuvwxyz")
WORDS = "one two three four five six seven eight nine".split()


def main(args):
    with open(args.outfile, "w") as outfile:
        for _ in range(args.num_lines):
            line = ""
            line_len = 0
            line_target_len = random.randint(args.line_len_min, args.line_len_max)
            while line_len < line_target_len:
                rand = random.random()
                if rand < args.digit_chance:
                    line += random.choice(DIGITS)
                    line_len += 1
                elif rand >= args.digit_chance and rand < (
                    args.word_chance + args.digit_chance
                ):
                    word = random.choice(WORDS)
                    line += word
                    line_len += len(word)
                else:
                    line += random.choice(CHARS)
                    line_len += 1
            line += "\n"
            outfile.write(line)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--num_lines", default=5, type=int, required=False)
    parser.add_argument("-w", "--word_chance", default=0.2, type=float, required=False)
    parser.add_argument("-d", "--digit_chance", default=0.2, type=float, required=False)
    parser.add_argument("--line_len_min", default=5, type=int, required=False)
    parser.add_argument("--line_len_max", default=50, type=int, required=False)
    parser.add_argument("outfile", type=str)

    args = parser.parse_args()
    main(args)
