cmake_minimum_required(VERSION 3.8)

project(tg-judge
    LANGUAGES CXX
)

add_library(tg-judge
    src/judge.cpp
)
target_compile_features(tg-judge PRIVATE cxx_std_17)

target_include_directories(tg-judge
    PUBLIC include
)
target_link_libraries(tg-judge
    PUBLIC tg-types
)
