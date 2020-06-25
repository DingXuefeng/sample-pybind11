#include "add.h"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(Phoenix, m) {
    m.doc() = "first function"; // Optional module docstring
    m.def("add", &add, "take sum of two int and return an int");
}
