#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <tg-types/state.hpp>
#include <tg-types/event.hpp>

namespace tg {

class animation {
private:
    match_t match;
    std::size_t event_counter = 0;
    std::size_t event_frame_counter = 0;

public:
    state current_state {};

    animation(const match_t& match);

    bool next_frame();
};

} // namespace tg

#endif // ANIMATION_HPP
