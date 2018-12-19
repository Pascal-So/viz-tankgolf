#include <tg-parser/parser.hpp>
#include <tg-types/point.hpp>
#include <tg-types/state.hpp>

#include <nlohmann/json.hpp>
#include <stdexcept>
using json = nlohmann::json;


namespace tg {

point parse_json_point(const json& j) {
    return point(j[0], j[1]);
}

orientation parse_json_orientation(const json& j) {
    return orientation {parse_json_point(j["pos"]), j["rot"]};
}

physics_state parse_json_physics_state(const json& j) {
    const std::array<orientation, 2> tanks = {
        parse_json_orientation(j["tanks"][0]),
        parse_json_orientation(j["tanks"][1])
    };
    return physics_state {tanks, parse_json_point(j["bullet"])};
}

std::vector<physics_state> parse_json_trajectory(const json& j) {
    std::vector<physics_state> out;
    for (auto const& s:j) {
        out.push_back(parse_json_physics_state(s));
    }
    return out;
}

event_body_t parse_json_event_body(const json& j) {
    if (j.find("type") == j.end())
        throw std::invalid_argument("Event type missing while parsing json.");

    const std::string type = j["type"];

    if (type == "respawn")
        return respawn_event {j["x_position"]};
    else if (type == "shoot")
        return shoot_event { tank_aim{j["angle"], j["intensity"]} };
    else if (type == "fall_off_map")
        return fall_off_map_event {j["player_id"]};
    else if (type == "impact")
        return impact_event {parse_json_point(j["pos"])};
    else if (type == "motion")
        return motion_event {parse_json_trajectory(j["trajectory"])};
    else
        throw std::invalid_argument("Unknown event type '" + type + "' while parsing json.");
}

event parse_json_event(const json& j) {
    if (j.find("event") == j.end())
        throw std::invalid_argument("Event field missing while parsing json.");

    return event {parse_json_event_body(j["event"]), j["active_player_id"], j["simulated"]};
}

std::vector<event> parse_events(std::istream& json_log_stream) {
    std::vector<event> out;

    std::string line;
    while (std::getline(json_log_stream, line)) {
        if (line == "") continue;
        out.push_back(parse_json_event(json::parse(line)));
    }

    return out;
}

} // namespace tg
