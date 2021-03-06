#ifndef JUDGE_HPP
#define JUDGE_HPP

#include <tg-types/event.hpp>

namespace tg {

std::uint8_t compute_winner(const match_t& match);

// higher style score => higher chance that we might want to
// show parts of this match at soi-day
double compute_style_score(const match_t& match);

unsigned longest_motion(const match_t& match);

} // namespace tg

#endif // JUDGE_HPP
