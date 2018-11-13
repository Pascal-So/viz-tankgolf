#ifndef PARSER_HPP
#define PARSER_HPP

#include <tg-types/event.hpp>
#include <vector>

namespace tg {

std::vector<event> parse_events(const std::string& json_log_data);

} // namespace tg

#endif // PARSER_HPP
