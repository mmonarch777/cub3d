cmake_minimum_required(VERSION 3.21)
project(cub3D C)

set(CMAKE_C_STANDARD 99)

file(GLOB
        FC  "src/*.c")

include_directories(.)

link_directories(${CMAKE_SOURCE_DIR}/libmini)
link_directories(${CMAKE_SOURCE_DIR}/minilibx_macos)

add_executable(${PROJECT_NAME} ${FC})

target_link_libraries(${PROJECT_NAME} mini)
target_link_libraries(${PROJECT_NAME} mlx)

target_link_libraries(${PROJECT_NAME} "-framework AppKit" "-framework OpenGL")