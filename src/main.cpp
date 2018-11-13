#include <tg-types/point.hpp>
#include <tg-parser/parser.hpp>
#include <tg-renderer/renderer.hpp>

#include <iostream>
#include <variant>

int main() {
    const auto events = tg::parse_events("{\"active_player_id\":0,\"event\":{\"trajectory\":[{\"bullet\":[14.0188570022583,3.080839157104492],\"tanks\":[{\"pos\":[13.122803688049316,3.5434622764587402],\"rot\":5.002345561981201},{\"pos\":[6.1661882400512695,3.014461040496826],\"rot\":0.0003762245178222656}]},{\"bullet\":[14.046335220336914,3.0],\"tanks\":[{\"pos\":[13.122803688049316,3.5434622764587402],\"rot\":5.002345561981201},{\"pos\":[6.1661882400512695,3.014461040496826],\"rot\":0.0003762245178222656}]}],\"type\":\"motion\"},\"simulated\":false}");
    const auto frame = std::get<tg::motion_event>(events[0].event_body).trajectory[0];
    tg::render_frame(frame);
}
