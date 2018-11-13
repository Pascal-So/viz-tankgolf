cmake_minimum_required(VERSION 3.8)

project(viz-tankgolf
    VERSION 0.1
    LANGUAGES CXX
)

add_executable(viz-tankgolf
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/tg-types)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/tg-parser)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/tg-renderer)
target_link_libraries(viz-tankgolf
    PRIVATE
        tg-types
        tg-parser
        tg-renderer
)
