project(main)

include_directories(include)

set(MAIN_SOURCES
    app/main.cpp
    src/model.cpp
    src/view.cpp
    src/controller.cpp
)

add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

target_link_libraries(${PROJECT_NAME}
    sub::lib1
    sub::lib2
)