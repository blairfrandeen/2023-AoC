#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Determine if a character is a digit. Return that character
 * as an integer if so, otherwise return -1 */
int8_t
is_digit(char chr)
{
    int8_t res = chr - '0';
    if (res <= 9) {
        return res;
    }
    return -1;
}

int
part_1(FILE *file_stream)
{
    char current_chr;  // current character we're reading
    int result = 0;    // final result we'll return
    bool first_digit =
        0;  // flag to indicate that we've found the first digit in a line
    uint8_t second_digit;
    int8_t current_digit;

    // read every byte in the file
    while ((current_chr = fgetc(file_stream)) != EOF) {
        if ((current_digit = is_digit(current_chr)) > 0) {
            // if we haven't yet found the first digit in a line, set the
            // first_digit flag to indicate that we have, and add 10 times that
            // digit to the result
            if (!first_digit) {
                first_digit = 1;
                result += current_digit * 10;
            }
            // set the second digit to the current digit regardless; we'll only
            // add it to the result once we know it's the last digit in the
            // line. This also covers the case where a line has only one digit,
            // e.g. "se7en" should yield 77.
            second_digit = current_digit;
        }
        // if we're at the end of a line, add the second digit, and reset the
        // flag to indicate we haven't found the first digit
        if (current_chr == '\n') {
            result += second_digit;
            first_digit = 0;
        }
    }
    return result;
}

// hard-code the numbers we're looking for
const char NUMS[9][6] = {"one", "two",   "three", "four", "five",
                         "six", "seven", "eight", "nine"};

int
part_2(void *file_start, size_t file_size)
{
    int result = 0;  // final result we'll return
    // flag to indicate that we've found the first digit in a line
    bool first_digit = 0;
    uint8_t second_digit = 0;
    int8_t current_digit;

    bool match = 0;
    char *current_chr = (char *)file_start;
    char *next_match;
    // read every byte in the file
    for (size_t i = 0; i < file_size; i++) {
        if ((current_digit = is_digit(*current_chr)) > 0) {
            if (!first_digit) {
                first_digit = 1;
                result += current_digit * 10;
                printf("a: %d\n", result);
            }
            printf("D: %d - %d\n", current_digit, result);
            second_digit = current_digit;
        }
        else {
            for (int j = 0; j < 9; j++) {  // loop through the possible words
                // for each word, go through letter by letter and see
                // if the word matches
                for (size_t k = 0; k < strlen(NUMS[j]); k++) {
                    // point to the kth position forward in the file stream
                    next_match = current_chr + k;
                    if (*next_match == EOF) {
                        break;
                    }
                    else if (*next_match == '\n') {
                        match = 0;
                        break;
                    }
                    printf("%c", *next_match);
                    if (*next_match != NUMS[j][k]) {
                        match = 0;
                        break;
                    }
                    // if we get to the end of the loop, we found a match.
                    match = 1;
                }
                if (match) {
                    current_digit = j + 1;
                    if (!first_digit) {
                        first_digit = 1;
                        result += current_digit * 10;
                        printf("b: %d\n", result);
                    }
                    second_digit = current_digit;
                    printf("W: %d - %d\n", current_digit, result);
                    break;
                }
            }
        }
        if (*current_chr == '\n') {
            result += second_digit;
            printf("c: %d\n", result);
            first_digit = 0;
            match = 0;
        }
        current_chr++;
    }
    return result;
}

int
main(int argc, char *argv[])
{
    char *datafile = "inputs/01_test2";
    FILE *file_stream = fopen(datafile, "r");
    if (file_stream == NULL) {
        printf("Error: could not open file %s: %s.\n", datafile,
               strerror(errno));
        exit(-1);
    }

    int num_runs = 1;
    float total_time = 0.0;
    int result, result_2;

    clock_t start_time, end_time;
    for (int i = 0; i < num_runs; i++) {
        start_time = clock();
        result = part_1(file_stream);
        end_time = clock();
        rewind(file_stream);
        total_time += (float)(end_time - start_time) / CLOCKS_PER_SEC;
    }
    float avg_time = total_time / num_runs;
    printf("Average Runtime: %.3f ms (%d runs)\n", avg_time * 1000, num_runs);
    printf("Part 1: %d\n", result);

    void *file_start = (void *)file_stream;
    fseek(file_stream, 0, SEEK_END);
    size_t file_size = ftell(file_stream) / sizeof(char) - 1;
    rewind(file_stream);
    printf("%p - %ld\n", file_start, file_size);
    total_time = 0;
    for (int i = 0; i < num_runs; i++) {
        start_time = clock();
        result_2 = part_2(file_start, file_size);
        end_time = clock();
        rewind(file_stream);
        total_time += (float)(end_time - start_time) / CLOCKS_PER_SEC;
    }
    avg_time = total_time / num_runs;
    printf("Average Runtime: %.3f ms (%d runs)\n", avg_time * 1000, num_runs);
    printf("Part 2: %d\n", result_2);
    fclose(file_stream);
    return 0;
}
