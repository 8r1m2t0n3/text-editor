project(pdcurses)

include_directories(include)

set(SOURCES src/curses_wrapped.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
add_library(sub::lib2 ALIAS ${PROJECT_NAME})

set(LIB_PATH ${CMAKE_SOURCE_DIR}/pdcurses/lib/pdcurses.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_PATH})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)