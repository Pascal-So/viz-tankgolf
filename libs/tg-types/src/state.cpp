#include <tg-types/state.hpp>

namespace tg {

std::ostream& operator<<(std::ostream& stream, const state& st) {
    stream << "\nTanks:\n";
    for (std::size_t i = 0; i < 2; ++i) {
        const auto& tank = st.physics.tanks[i];
        stream << "    Pos:   " << tank.pos << '\n';
        stream << "    Rot:   " << tank.rot << '\n';
        const auto& aim = st.frontend.tank_aims[i];
        stream << "    Angle: " << aim.angle << '\n';
        stream << "    Int.:  " << aim.intensity << '\n';
    }
    stream << "Bullet:\n";
    stream << "    " << st.physics.bullet << '\n';

    stream << "Explosion:\n";
    stream << "    Int.:  " << st.frontend.explosion_intensity << '\n';
    stream << "    Pos:   " << st.frontend.explosion_position << '\n';

    return stream;
}

} // namespace tg
