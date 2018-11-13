#ifndef EVENT_HPP
#define EVENT_HPP

#include <tg-types/point.hpp>
#include <tg-types/state.hpp>

#include <variant>
#include <vector>

namespace tg {

struct respawn_event { float x_position; };
struct shoot_event { float angle; float intensity; };
struct fall_off_map_event { std::uint8_t player_id; };
struct impact_event { point pos; };
struct motion_event { std::vector<state> trajectory; };

using event = std::variant <
    respawn_event,
    shoot_event,
    fall_off_map_event,
    impact_event,
    motion_event>;

} // namespace tg

#endif // EVENT_HPP
