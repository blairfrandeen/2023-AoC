#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdbool.h>

/* Determine if a character is a digit. Return that character
 * as an integer if so, otherwise return -1 */
int8_t is_digit(char chr) {
    int8_t res = chr - '0';
    if(res <= 9) {
        return res;
    }
    return -1;
}

static PyObject *
aoc_part1(PyObject *self, PyObject *args)
{
    const char *puzzle_input;

    if (!PyArg_ParseTuple(args, "s", &puzzle_input))
        return NULL;

    int result = 0; // final result we'll return
    bool first_digit = 0;  // flag to indicate that we've found the first digit in a line
    uint8_t second_digit = 0;
    int8_t current_digit;
    
    // read every byte in the file
    for(size_t i=0; i < strlen(puzzle_input); i++) {
        if((current_digit = is_digit(puzzle_input[i])) > 0) {
            // if we haven't yet found the first digit in a line, set the first_digit
            // flag to indicate that we have, and add 10 times that digit to the result
            if (!first_digit) {
                first_digit = 1;
                result += current_digit * 10;
            }
            // set the second digit to the current digit regardless; we'll only add it
            // to the result once we know it's the last digit in the line. This also
            // covers the case where a line has only one digit, e.g. "se7en" should yield 77.
            second_digit = current_digit;
        }
        // if we're at the end of a line, add the second digit, and reset the 
        // flag to indicate we haven't found the first digit
        if(puzzle_input[i] == '\n') {
            result += second_digit;
            first_digit = 0;
            second_digit = 0;
        }
    }
    result += second_digit; // allow for input without trailing newline
    return PyLong_FromLong(result);
}


// these are the functions available from this module
static PyMethodDef aocMethods[] = {
    {"part1", aoc_part1, METH_VARARGS, "solve part 1"},
    {NULL, NULL, 0, NULL} // sentinel
};

// this is the module definition
static struct PyModuleDef aocmodule = {
    PyModuleDef_HEAD_INIT,
    "aoc", // module name
    NULL, // documentation, nothing for now
    -1,
    aocMethods
};

// this creates a new module and allows it to be imported
PyMODINIT_FUNC 
PyInit_aocmodule(void)
{
    return PyModule_Create(&aocmodule);
}
