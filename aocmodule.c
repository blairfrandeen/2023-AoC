#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *
aoc_part1(PyObject *self, PyObject *args)
{
    // for now, don't take any args, and just return
    // everyone's favorite integer
    return PyLong_FromLong(42);
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
