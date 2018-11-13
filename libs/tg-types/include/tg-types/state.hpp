#ifndef STATE_HPP
#define STATE_HPP

#include <tg-types/point.hpp>
#include <array>

namespace tg {

struct orientation {
    point pos;
    float rot;
};

struct state {
    std::array<orientation, 2> tanks;
    point bullet;
};

} // namespace tg

#endif // STATE_HPP
