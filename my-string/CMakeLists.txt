project(my_string)
add_executable(${PROJECT_NAME} main.cpp)

add_library(my_string_library STATIC 
    my_string/src/my-string.cpp
)