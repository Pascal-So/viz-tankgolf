#ifndef PARSER_HPP
#define PARSER_HPP

#include <tg-types/event.hpp>
#include <vector>
#include <istream>

namespace tg {

std::vector<event> parse_events(std::istream& json_log_stream);

} // namespace tg

#endif // PARSER_HPP
