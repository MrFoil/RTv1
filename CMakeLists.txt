cmake_minimum_required(VERSION 3.9)
project(RTv1)
set(CMAKE_C_STANDARD 99)

if (WIN32)

set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${PROJECT_SOURCE_DIR}/SDL2/include)

endif()

link_directories(${PROJECT_SOURCE_DIR}/includes)
include_directories(${PROJECT_SOURCE_DIR}/includes)

set(SOURCE_FILES src/main.c includes/rtv1.h
        includes/vector_math.h
        src/math/math_constructors.c
        src/math/math_vec3_opeartors.c
        src/math/math_vec4_opeartors.c
        src/math/math_mat4_operators.c
        src/math/math_transformations.c
        src/camera.c
        src/vec_tools.c
        src/primitives.c )

add_executable(RTv1 ${SOURCE_FILES})

if (WIN32)
target_link_libraries(RTv1
        #	${SDL2MAIN_LIBRARY}
        ${SDL2_LIBRARY}
        -lm)
endif ()

if (UNIX)

    find_package(SDL2 REQUIRED)

    target_link_libraries(RTv1 -lm -lSDL2)
endif()