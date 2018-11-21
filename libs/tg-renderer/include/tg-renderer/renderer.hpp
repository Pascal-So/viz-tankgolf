#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <tg-types/event.hpp>
#include <filesystem>
namespace fs = std::filesystem;

namespace tg {

void render_frame(const state& st);
void render_match(const match_t& match, const fs::path& outpath);

} // namespace tg

#endif // RENDERER_HPP
