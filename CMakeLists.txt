cmake_minimum_required(VERSION 3.9)
project(RTv1)

set(CMAKE_C_STANDARD 99)



    link_directories(${PROJECT_SOURCE_DIR}/includes)
    include_directories(${PROJECT_SOURCE_DIR}/includes)

find_package(SDL2 REQUIRED)


set(SOURCE_FILES src/main.c includes/rtv1.h
        includes/vector_math.h
        src/math_constructors.c
        src/math_vec3_opeartors.c
        src/math_vec4_opeartors.c
        src/math_mat4_operators.c
        src/math_transformations.c
        src/camera.c
        src/vec_tools.c
        src/primitives.c )

add_executable(RTv1 ${SOURCE_FILES})

    target_link_libraries(RTv1 -lm -lSDL2)
