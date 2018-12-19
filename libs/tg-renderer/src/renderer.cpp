#include <tg-renderer/renderer.hpp>
#include <tg-renderer/animation.hpp>

#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace tg {

class renderer {
    sf::Texture background_texture;
    sf::Sprite background_sprite;

    std::array<sf::Texture, 2> tank_textures;
    std::array<sf::Sprite, 2> tank_sprites;

    std::array<sf::Texture, 2> barrel_textures;
    std::array<sf::Sprite, 2> barrel_sprites;

    sf::Texture bullet_texture;
    sf::Sprite bullet_sprite;

    sf::Font font;
    std::array<sf::Text, 2> player_name_texts;
    sf::Text score_text;

    std::array<sf::RectangleShape, 3> blockers;

public:

    const float map_width = 20, map_height = 12;

    const int map_pixel_width = 1544, map_pixel_height = 926;
    const float scale = map_pixel_width / map_width;

private:

    sf::Vector2f transform_coordinates(const point& p) {
        const sf::Vector2f offset {188, 138};
        return sf::Vector2f(p.x * scale, p.y * scale) + offset;
    }

public:
    renderer(const std::array<std::string, 2>& player_names) {
        background_texture.loadFromFile("resources/tg-world-empty.png");
        background_sprite.setTexture(background_texture);

        tank_textures[0].loadFromFile("resources/tg-tank-blue-body-small.png");
        tank_sprites[0].setTexture(tank_textures[0]);
        tank_textures[1].loadFromFile("resources/tg-tank-red-body-small.png");
        tank_sprites[1].setTexture(tank_textures[1]);

        barrel_textures[0].loadFromFile("resources/tg-tank-blue-barrel-small.png");
        barrel_sprites[0].setTexture(barrel_textures[0]);
        barrel_textures[1].loadFromFile("resources/tg-tank-red-barrel-small.png");
        barrel_sprites[1].setTexture(barrel_textures[1]);

        bullet_texture.loadFromFile("resources/bullet.png");
        bullet_sprite.setTexture(bullet_texture);

        font.loadFromFile("resources/NotoSansSC-Light.otf");

        background_sprite.setScale(1, -1);
        background_sprite.setOrigin(0, 1080);

        for(int i = 0; i < 2; ++i) {
            tank_sprites[i].setOrigin(114/2, 110);
            barrel_sprites[i].setOrigin(114/2, 110 - 52);
            tank_sprites[i].setScale(1, -1);
            player_name_texts[i].setFont(font);
            player_name_texts[i].setCharacterSize(35);
            player_name_texts[i].setString(player_names[i]);
            player_name_texts[i].setFillColor(sf::Color::White);
            player_name_texts[i].setScale(1, -1);
        }
        player_name_texts[0].setPosition(188, 80);
        const float text1_width = player_name_texts[1].getLocalBounds().width;
        player_name_texts[1].setPosition(1920-188-text1_width, 80);

        for(auto& blocker : blockers) {
            blocker.setFillColor(sf::Color(0x22, 0x22, 0x22));
        }
        blockers[0].setSize(sf::Vector2f(188, 1080 - 138));
        blockers[1].setSize(sf::Vector2f(188, 1080 - 138));
        blockers[2].setSize(sf::Vector2f(1920, 138));

        blockers[0].setPosition(sf::Vector2f(0, 138));
        blockers[1].setPosition(sf::Vector2f(1920-188, 138));
        blockers[2].setPosition(sf::Vector2f(0, 0));

        score_text.setFont(font);
        score_text.setCharacterSize(55);
        score_text.setFillColor(sf::Color::White);
        score_text.setScale(1, -1);

        score_text.setPosition(890, 110);
    }

    template <typename Buffer>
    void render_state(Buffer& buf, const state& st) {
        buf.draw(background_sprite);

        for (std::size_t i = 0; i < st.physics.tanks.size(); ++i) {
            const auto& tank = st.physics.tanks[i];
            if (tank.pos != point{-1, -1}) {
                auto const screen_coords = transform_coordinates(tank.pos);
                tank_sprites[i].setPosition(screen_coords);
                tank_sprites[i].setRotation(tank.rot * 180. / M_PI);

                const sf::Transform tank_transform = tank_sprites[i].getTransform();
                sf::Transform local_barrel_transform;
                local_barrel_transform.translate(0.7 * scale, 0.7 * scale);
                local_barrel_transform.rotate(- st.frontend.tank_aims[i].angle * 180. / M_PI);
                buf.draw(barrel_sprites[i], tank_transform * local_barrel_transform);

                buf.draw(tank_sprites[i]);
            }
        }

        if (st.physics.bullet != point{-1, -1}) {
            bullet_sprite.setPosition(transform_coordinates(st.physics.bullet));
            buf.draw(bullet_sprite);
        }

        for (auto& blocker : blockers) {
            buf.draw(blocker);
        }

        for (auto& text : player_name_texts) {
            buf.draw(text);
        }

        std::stringstream score_stream;
        score_stream << st.scores[0] << " - " << st.scores[1];
        score_text.setString(score_stream.str());
        buf.draw(score_text);
    }

};

void render_frame(const state& st) {
    renderer r ({"asdf", "jjjjj"});

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow win(sf::VideoMode(1920, 1080), "TankGolf",
                         sf::Style::Default, settings);
    win.setFramerateLimit(30);

    win.clear(sf::Color(30, 30, 30));
    r.render_state(win, st);
    win.display();

    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed)
                win.close();
        }
    }
}

template <typename Buffer>
void save_to_file(const Buffer& buf, const fs::path& outpath, const unsigned image_id) {
    std::stringstream ss;
    ss << "frame_" << std::setw(4) << std::setfill('0') << image_id << ".jpg";
    const std::string filename = ss.str();

    std::cerr << "saving file " << filename << '\n';

    buf.getTexture().copyToImage().saveToFile(outpath / filename);
}

void render_match(const match_t& match, const fs::path& outpath, const std::array<std::string, 2>& player_names) {
    renderer r (player_names);
    animation anim(match);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderTexture buf;
    buf.create(1920, 1080); //, settings);

    for (unsigned i = 0;; ++i) {
        if (!anim.next_frame())
            break;

        // buf.clear(sf::Color(30, 30, 30));
        r.render_state(buf, anim.current_state);

        save_to_file(buf, outpath, i);
    }
}

} // namespace tg
