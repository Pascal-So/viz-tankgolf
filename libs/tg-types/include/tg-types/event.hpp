#ifndef EVENT_HPP
#define EVENT_HPP

#include <tg-types/point.hpp>
#include <tg-types/state.hpp>

#include <variant>
#include <vector>

namespace tg {

struct respawn_event { float x_position; };
struct shoot_event { tank_aim aim; };
struct fall_off_map_event { std::uint8_t player_id; };
struct impact_event { point pos; };
struct motion_event { std::vector<physics_state> trajectory; };

using event_body_t = std::variant <
    respawn_event,
    shoot_event,
    fall_off_map_event,
    impact_event,
    motion_event>;

struct event {
    event_body_t event_body;
    int active_player_id;
    bool simulated;
};

using match_t = std::vector<event>;

} // namespace tg

#endif // EVENT_HPP
