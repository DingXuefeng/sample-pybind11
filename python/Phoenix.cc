#include "Fit.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

PYBIND11_MODULE(Phoenix, m) {
    m.doc() = "first function"; // Optional module docstring
    py::class_<Fit>(m, "Fit")
        .def(py::init())
        .def("setNdata", &Fit::setNdata)
        .def("setNmodel", &Fit::setNmodel)
        .def("setPar", &Fit::setPar)
        .def("setData", [](Fit &instance,py::array_t<int, py::array::c_style | py::array::forcecast> data) {
            int tmp[Phoenix::data_maxN];
            for(int i = 0;i<data.shape(0);++i)
            tmp[i] = data.at(i);
            instance.setData(tmp);
            })
        .def("setModel", [](Fit &instance,int i,py::array_t<double, py::array::c_style | py::array::forcecast> model) {
            Phoenix::pArray tmp;
            for(int i = 0;i<model.shape(0);++i)
            tmp[i] = model.at(i);
            instance.setModel(i,tmp);
            });
}
