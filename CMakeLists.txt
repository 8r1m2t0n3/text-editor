cmake_minimum_required (VERSION 3.5)

project(TextEditor)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(my-string)
add_subdirectory(pdcurses)
add_subdirectory(main)