#ifndef STATE_HPP
#define STATE_HPP

#include <tg-types/point.hpp>
#include <array>
#include <ostream>

namespace tg {

struct orientation {
    point pos {-1, -1};
    float rot = 0;
};

struct physics_state {
    std::array<orientation, 2> tanks;
    point bullet {-1, -1};
};

struct tank_aim {
    float angle = 0;
    float intensity = 0;
};

struct frontend_state {
    std::array<tank_aim, 2> tank_aims;
    bool bullet_exploding = false;
};

struct state {
    physics_state physics;
    frontend_state frontend;
    std::array<unsigned, 2> scores {0, 0};
};

std::ostream& operator<<(std::ostream& stream, const state& st);

} // namespace tg

#endif // STATE_HPP
