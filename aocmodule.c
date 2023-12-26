#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdbool.h>

/* Determine if a character is a digit. Return that character
 * as an integer if so, otherwise return -1 */
int8_t
_is_digit(char chr)
{
    int8_t res = chr - '0';
    if (res <= 9) {
        return res;
    }
    return -1;
}

static PyObject *
aoc_part1(PyObject *self, PyObject *args)
{
    Py_buffer puzzle_input;

    if (!PyArg_ParseTuple(args, "s*", &puzzle_input))
        return NULL;

    int result = 0;  // final result we'll return
    // flag to indicate that we've found the first digit in a line
    bool first_digit = 0;
    uint8_t second_digit = 0;
    int8_t current_digit;
    char *current_chr = (char *)puzzle_input.buf;

    // read every byte in the buffer
    for (Py_ssize_t i = 0; i < puzzle_input.len; i++) {
        if ((current_digit = _is_digit(*current_chr)) > 0) {
            // if we haven't yet found the first digit in a line, set the
            // first_digit flag to indicate that we have, and add 10 times that
            // digit to the result
            if (!first_digit) {
                first_digit = 1;
                result += current_digit * 10;
            }
            // to the result once we know it's the last digit in the line. This
            // also covers the case where a line has only one digit, e.g.
            // "se7en" should yield 77.
            second_digit = current_digit;
        }
        // if we're at the end of a line, add the second digit, and reset the
        // flag to indicate we haven't found the first digit
        if (*current_chr == '\n') {
            result += second_digit;
            first_digit = 0;
            second_digit = 0;
        }
        current_chr++;
    }
    result += second_digit;  // allow for input without trailing newline

    // release the buffer
    PyBuffer_Release(&puzzle_input);

    return PyLong_FromLong(result);
}

static PyObject *
aoc_part2(PyObject *self, PyObject *args)
{
    Py_buffer puzzle_input;

    if (!PyArg_ParseTuple(args, "s*", &puzzle_input))
        return NULL;

    int result = 0;  // final result we'll return
    // flag to indicate that we've found the first digit in a line
    bool first_digit = 0;
    uint8_t second_digit = 0;
    int8_t current_digit;

    bool match = 0;
    char *current_chr = (char *)puzzle_input.buf;
    char *next_match;

    // hard-code the numbers we're looking for
    const char NUMS[9][6] = {"one", "two",   "three", "four", "five",
                             "six", "seven", "eight", "nine"};

    // read every byte in the file
    for (Py_ssize_t i = 0; i < puzzle_input.len; i++) {
        if ((current_digit = _is_digit(*current_chr)) > 0) {
            if (!first_digit) {
                first_digit = 1;
                result += current_digit * 10;
                /* printf("a: %d\n", result); */
            }
            /* printf("D: %d - %d\n", current_digit, result); */
            second_digit = current_digit;
        }
        else {
            for (int j = 0; j < 9; j++) {  // loop through the possible words
                // for each word, go through letter by letter and see
                // if the word matches
                for (size_t k = 0; k < strlen(NUMS[j]); k++) {
                    // check that we're not at the end of the input
                    if ((Py_ssize_t)k + i >= puzzle_input.len) {
                        match = 0;
                        break;
                    }
                    // point to the kth position forward in the buffer
                    next_match = current_chr + k;

                    if (*next_match != NUMS[j][k]) {
                        match = 0;
                        break;
                    }
                    /* printf("%c", *next_match); */
                    // if we get to the end of the loop, we found a match.
                    match = 1;
                }
                if (match) {
                    current_digit = j + 1;
                    if (!first_digit) {
                        first_digit = 1;
                        result += current_digit * 10;
                        /* printf("b: %d\n", result); */
                    }
                    second_digit = current_digit;
                    /* printf("W: %d - %d\n", current_digit, result); */
                    break;
                }
            }
        }
        if (*current_chr == '\n') {
            result += second_digit;
            /* printf("c: %d\n", result); */
            first_digit = 0;
            match = 0;
        }
        current_chr++;
    }
    if (*(current_chr - 1) != '\n') {
        /* printf("errs: %c\n", *(current_chr - 1)); */
        result += second_digit;  // allow for input without trailing newline
    }
    // release the buffer
    PyBuffer_Release(&puzzle_input);

    return PyLong_FromLong(result);
}
// these are the functions available from this module
static PyMethodDef aocMethods[] = {
    {"part1", aoc_part1, METH_VARARGS, "solve part 1"},
    {"part2", aoc_part2, METH_VARARGS, "solve part 2"},
    {NULL, NULL, 0, NULL}  // sentinel
};

// this is the module definition
static struct PyModuleDef aocmodule = {PyModuleDef_HEAD_INIT,
                                       "aoc",  // module name
                                       NULL,  // documentation, nothing for now
                                       -1, aocMethods};

// this creates a new module and allows it to be imported
PyMODINIT_FUNC
PyInit_aocmodule(void)
{
    return PyModule_Create(&aocmodule);
}
