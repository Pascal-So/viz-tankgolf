cmake_minimum_required(VERSION 3.8)

project(tg-renderer
    LANGUAGES CXX
)

add_library(tg-renderer
    src/renderer.cpp
    src/animation.cpp
)
target_compile_features(tg-renderer PRIVATE cxx_std_17)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

target_include_directories(tg-renderer
    PUBLIC include
)

target_link_libraries(tg-renderer
    PRIVATE
        sfml-graphics
    PUBLIC
        tg-types
        stdc++fs
)

add_custom_command(TARGET tg-renderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_LIST_DIR}/resources
        ${CMAKE_BINARY_DIR}/resources
)
