cmake_minimum_required(VERSION 2.8.12)
project(Phoenix)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
add_subdirectory(pybind11)

add_subdirectory(python)
add_library(add add.cc)

configure_file(setup/setup.sh.in setup/setup.sh @ONLY)
install(PROGRAMS ${CMAKE_BINARY_DIR}/setup/setup.sh TYPE BIN)
install(PROGRAMS ${CMAKE_SOURCE_DIR}/python/test.py DESTINATION ${CMAKE_INSTALL_PREFIX}/share)
install(TARGETS Phoenix LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
