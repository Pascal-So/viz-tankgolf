#include <tg-judge/judge.hpp>


#include <algorithm>
#include <array>
#include <cmath>
#include <tg-types/util.hpp>

namespace tg {

std::uint8_t compute_winner(const match_t& match) {
    std::array<unsigned, 2> scores;

    std::for_each(match.begin(), match.end(), [&](const event& ev){
        if (ev.simulated) return;
        std::visit(overloaded {
            [&](const fall_off_map_event& e) {
                scores[e.player_id ^ 1] ++;
            },
            [](const auto&) {/* ignore */}
        }, ev.event_body);
    });

    return std::max_element(scores.begin(), scores.end()) - scores.begin();
}

double compute_style_score(const match_t& match) {
    // count flips
    double flip_score = 0;
    // todo

    // reward fast motion or rotation
    double motion_score = 0;
    {
        unsigned ticks = 0;
        std::for_each(match.begin(), match.end(), [&](const event& ev){
            if (ev.simulated) return;

            std::visit(overloaded {
                [&](const motion_event& e) {
                    std::array<orientation, 2> last_tanks = e.trajectory[0].tanks;
                    for (const physics_state& st : e.trajectory) {
                        ticks ++;
                        const auto& tanks = st.tanks;
                        for (std::size_t i = 0; i < 2; ++i) {
                            motion_score += std::fmod(std::abs(last_tanks[i].rot - tanks[i].rot), M_PI * 2);
                            motion_score += (last_tanks[i].pos - tanks[i].pos).sqmag();
                        }
                        last_tanks = tanks;
                    }
                },
                [](const auto&) {/* ignore */}
            }, ev.event_body);
        });

        motion_score /= ticks;
    }

    // reward quick wins
    double quick_win_score = 0;
    {
        unsigned turns_to_win;
        std::for_each(match.begin(), match.end(), [&](const event& ev){
            if (!ev.simulated) turns_to_win ++;
        });
        quick_win_score = (turns_to_win > 0) ? (1.0 / turns_to_win) : 0;
    }

    // detect overly long motions so we can punish that
    double long_motion_score = 0;
    {
        const unsigned limit = 30 /* fps */ * 15 /* seconds */;

        std::for_each(match.begin(), match.end(), [&](const event& ev){
            if (ev.simulated) return;

            std::visit(overloaded {
                [&](const motion_event& e) {
                    if (e.trajectory.size() > limit) {
                        long_motion_score ++;
                    }
                },
                [](const auto&) {/* ignore */}
            }, ev.event_body);
        });
    }

    // Adjust here to tune the linear combination
    // of score components. Add negative weights
    // to discurage components.
    return
        flip_score        *     1.0 +
        motion_score      *    10.0 +
        quick_win_score   *    80.0 +
        long_motion_score * -1000.0;
}

} // namespace tg
