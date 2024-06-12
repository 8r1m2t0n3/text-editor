project(my_string)

include_directories(include)

set(SOURCES src/my_string.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)