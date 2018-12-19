#include <tg-types/point.hpp>
#include <tg-parser/parser.hpp>
#include <tg-renderer/renderer.hpp>
#include <tg-renderer/animation.hpp>
#include <tg-judge/judge.hpp>

#include <iostream>
#include <variant>
#include <fstream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: " << std::string(argv[0]) << " logfile\n";
        return 1;
    }
    const std::string logfile(argv[1]);
    std::ifstream match_stream(logfile);
    const auto match = tg::parse_events(match_stream);
    std::cerr << "parsed file (" << match.size() << " events)\n";
    std::cout << "Winner: player " << (char)('A' + tg::compute_winner(match)) << '\n';

    // auto anim = tg::animation{match};
    // auto frame = anim.next_frame();
    // std::cerr << frame;
    tg::render_match(match, "out", {"nicolas.camenisch d3i_bot", "chnuspi angry_bot"});
}
