cmake_minimum_required(VERSION 3.8)

project(tg-parser
    LANGUAGES CXX
)

add_library(tg-parser
    src/parser.cpp
)
target_compile_features(tg-parser PRIVATE cxx_std_17)

target_include_directories(tg-parser
    PUBLIC include
)

add_subdirectory(../json ${CMAKE_CURRENT_BINARY_DIR}/json EXCLUDE_FROM_ALL)
target_link_libraries(tg-parser
    PRIVATE
        nlohmann_json::nlohmann_json
    PUBLIC
        tg-types
)
