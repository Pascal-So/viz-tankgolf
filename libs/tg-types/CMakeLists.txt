cmake_minimum_required(VERSION 3.8)

project(tg-types
    LANGUAGES CXX
)

add_library(tg-types
    src/point.cpp
    src/state.cpp
)
target_compile_features(tg-types PUBLIC cxx_std_17)

target_include_directories(tg-types
    PUBLIC include
)
