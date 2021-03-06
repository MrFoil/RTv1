cmake_minimum_required(VERSION 3.9)
project(RTv1)

if (WIN32)

set(CMAKE_VERBOSE_MAKEFILE ON)

#set(SDL2_PATH ${PROJECT_SOURCE_DIR}/Library/bin)

include_directories(${PROJECT_SOURCE_DIR}/Library/include)

endif()

link_directories(${PROJECT_SOURCE_DIR}/includes)
link_directories(${PROJECT_SOURCE_DIR}/Libft)
include_directories(${PROJECT_SOURCE_DIR}/includes)
include_directories(${PROJECT_SOURCE_DIR}/Libft)

set(LIBFT_FILES Libft/ft_memset.c
        Libft/ft_bzero.c
        Libft/ft_memcpy.c
        Libft/ft_memccpy.c
        Libft/ft_memmove.c
        Libft/ft_memchr.c
        Libft/ft_memcmp.c
        Libft/ft_strlen.c
        Libft/ft_strdup.c
        Libft/ft_strndup.c
        Libft/ft_strcpy.c Libft/ft_strncpy.c
        Libft/ft_strcat.c Libft/ft_strncat.c Libft/ft_strlcat.c
        Libft/ft_strchr.c Libft/ft_strrchr.c
        Libft/ft_strstr.c Libft/ft_strnstr.c
        Libft/ft_strcmp.c Libft/ft_strncmp.c
        Libft/ft_atoi.c
        Libft/ft_isalpha.c
        Libft/ft_isdigit.c
        Libft/ft_isalnum.c
        Libft/ft_isascii.c
        Libft/ft_isprint.c
        Libft/ft_toupper.c
        Libft/ft_tolower.c
        Libft/ft_lstnew.c Libft/ft_lstdelone.c Libft/ft_lstdel.c Libft/ft_lstadd.c Libft/ft_lstiter.c
        Libft/ft_lstmap.c
        Libft/ft_itoa.c
        Libft/ft_memalloc.c
        Libft/ft_memdel.c
        Libft/ft_putchar.c
        Libft/ft_putchar_fd.c
        Libft/ft_putendl.c
        Libft/ft_putendl_fd.c
        Libft/ft_putnbr.c
        Libft/ft_putnbr_fd.c
        Libft/ft_putstr.c
        Libft/ft_putstr_fd.c
        Libft/ft_strclr.c
        Libft/ft_strdel.c
        Libft/ft_strequ.c
        Libft/ft_strnequ.c
        Libft/ft_striter.c
        Libft/ft_striteri.c
        Libft/ft_strjoin.c
        Libft/ft_strmap.c
        Libft/ft_strmapi.c
        Libft/ft_strnew.c
        Libft/ft_strsplit.c
        Libft/ft_strsub.c
        Libft/ft_strtrim.c
        Libft/ft_manywords.c
        Libft/ft_isupper.c
        Libft/ft_islower.c
        Libft/get_next_line.c)

set(SOURCE_FILES src/main.c includes/rtv1.h
        includes/vector_math.h
        src/math/math_constructors.c
        src/math/math_vec3_opeartors.c
        src/camera.c
        src/ray.c
        src/material_scatters.c
        src/math/math_utils.c
        src/render_objects/sphere.c src/to_libft/ft_lstadd_end.c src/render_objects/cube.c)

add_executable(RTv1 ${SOURCE_FILES} ${LIBFT_FILES})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)

if (WIN32)
    target_link_libraries(RTv1 ${SDL2_LIBRARY} -lm)
endif ()

if(APPLE)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
    target_link_libraries(RTv1 ${SDL2_LIBRARY} -lm)
elseif(UNIX)
    find_package(SDL2 REQUIRED)
    target_link_libraries(RTv1 -lm -lSDL2)
endif()
