cmake_minimum_required(VERSION 3.8)

project(viz-tankgolf
    VERSION 0.1
    LANGUAGES CXX
)

# The library tg-types is required by the other libs, so it has to be added first.
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/tg-types)

# These libs are independent, so the order doesn't matter.
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/tg-parser)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/tg-judge)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/tg-renderer)

if(CMAKE_CXX_COMPILER_ID STREQUAL GNU OR
   CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -Wpedantic -O3")
endif()

add_executable(viz-tankgolf
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
target_link_libraries(viz-tankgolf
    PRIVATE
        tg-types
        tg-parser
        tg-renderer
        tg-judge
)
