cmake_minimum_required(VERSION 3.8)

project(tg-renderer
    LANGUAGES CXX
)

add_library(tg-renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer.cpp
)
target_compile_features(tg-renderer PRIVATE cxx_std_17)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

target_include_directories(tg-renderer
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(tg-renderer
    PUBLIC tg-types
    PRIVATE sfml-graphics
)
