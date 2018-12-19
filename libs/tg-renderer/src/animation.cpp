#include <tg-renderer/animation.hpp>
#include <tg-types/util.hpp>
#include <iostream>

namespace tg {

const float respawn_height = 7.;

animation::animation(const match_t& match)
    : match (match) {}

bool animation::next_frame() {
    current_state.frontend.bullet_exploding = false;
    bool something_happened = false;

    while (!something_happened || event_counter == match.size()) {
        const event& ev = match[event_counter];
        std::visit(overloaded {
            [&](const respawn_event& e) {
                if (!ev.simulated) {
                    current_state.physics.tanks[ev.active_player_id].pos = {e.x_position, respawn_height};
                    // something_happened = true;
                }
                ++ event_counter;
            },
            [&](const shoot_event& e) {
                if (!ev.simulated) {
                    current_state.frontend.tank_aims[ev.active_player_id] = e.aim;
                    // something_happened = true;
                }
                ++ event_counter;
            },
            [&](const fall_off_map_event& e) {
                if (!ev.simulated) {
                    current_state.physics.tanks[e.player_id].pos = {-1, -1};
                    ++ current_state.scores[1 ^ e.player_id];
                    something_happened = true;
                }
                ++ event_counter;
            },
            [&](const impact_event& e) {
                if (!ev.simulated) {
                    current_state.frontend.bullet_exploding = true;
                    // something_happened = true;
                }
                ++ event_counter;
            },
            [&](const motion_event& e) {
                if (!ev.simulated) {
                    current_state.physics = e.trajectory[event_frame_counter];
                    ++ event_frame_counter;
                    something_happened = true;
                    if (event_frame_counter == e.trajectory.size()) {
                        ++ event_counter;
                        event_frame_counter = 0;
                    }
                } else {
                    ++ event_counter;
                    event_frame_counter = 0;
                }
            }
        }, ev.event_body);
    }

    return something_happened;
}


} // namespace tg
