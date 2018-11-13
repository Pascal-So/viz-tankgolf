#include <tg-types/point.hpp>
#include <tg-parser/parser.hpp>
#include <tg-renderer/renderer.hpp>
#include <iostream>

int main() {
    std::cout << tg::point(2,5.3) << '\n';

    tg::parse_events("{}");
}
