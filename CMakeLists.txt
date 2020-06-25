cmake_minimum_required(VERSION 2.8.12)
project(Phoenix)

set(CMAKE_CXX_STANDARD 14)

find_package(ROOT REQUIRED Minuit)
include(${ROOT_USE_FILE})

include_directories(.)
add_subdirectory(pybind11)

add_subdirectory(python)
add_library(FCN FCN.cc)
add_library(Fit Fit.cc)
target_link_libraries(Fit PRIVATE FCN ${ROOT_LIBRARIES})

configure_file(setup/setup.sh.in setup/setup.sh @ONLY)
install(PROGRAMS ${CMAKE_BINARY_DIR}/setup/setup.sh TYPE BIN)
install(DIRECTORY python/ DESTINATION ${CMAKE_INSTALL_PREFIX}/share USE_SOURCE_PERMISSIONS FILES_MATCHING PATTERN "python/*.py")
install(TARGETS Phoenix LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
