cmake_minimum_required(VERSION 3.8)

project(tg-parser
    LANGUAGES CXX
)

add_library(tg-parser
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp
)
target_compile_features(tg-parser PRIVATE cxx_std_17)

target_include_directories(tg-parser
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(JSON_BuildTests "" OFF)
add_subdirectory(../json ${CMAKE_CURRENT_BINARY_DIR}/json)
target_link_libraries(tg-parser
    PRIVATE
        nlohmann_json::nlohmann_json
    PUBLIC
        tg-types
)
