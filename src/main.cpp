#include <tg-types/point.hpp>
#include <tg-parser/parser.hpp>
#include <tg-renderer/renderer.hpp>
#include <tg-renderer/animation.hpp>
#include <tg-judge/judge.hpp>

#include <iostream>
#include <variant>
#include <fstream>

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "usage: " << std::string(argv[0]) << " logfile name1 name2 output_path\n";
        return 1;
    }
    const std::string logfile(argv[1]);
    std::ifstream match_stream(logfile);
    const auto match = tg::parse_events(match_stream);
    std::cerr << "parsed file (" << match.size() << " events)\n";

    const auto longest_motion = tg::longest_motion(match);
    std::cerr << "Longest motion: " << longest_motion << '\n';
    if (longest_motion > 300) {
        std::cerr << "probably contains physics errors. please rerun.\n";
        return 1;
    }

    std::array<std::string,2> names;
    names[0] = argv[2];
    names[1] = argv[3];

    const std::string output_path(argv[4]);

    // auto anim = tg::animation{match};
    // auto frame = anim.next_frame();
    // std::cerr << frame;
    tg::render_match(match, output_path, names);
}
