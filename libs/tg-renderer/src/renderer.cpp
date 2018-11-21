#include <tg-renderer/renderer.hpp>

#include <iostream>
#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace tg {


class renderer {
    sf::Texture tank_texture;
    sf::Sprite tank_sprite;

    sf::Texture bullet_texture;
    sf::Sprite bullet_sprite;

public:
    const float map_width = 20, map_height = 12;
    const int width = 1920, height = width / map_width * map_height;
    const float scale = width / map_width;

private:
    sf::Vector2f transform_coordinates(const point& p) {
        return {p.x * scale, height - p.y * scale};
    }

public:
    renderer() {
        tank_texture.loadFromFile("../libs/tg-renderer/resources/tank.png");
        tank_sprite.setTexture(tank_texture);

        bullet_texture.loadFromFile("../libs/tg-renderer/resources/bullet.png");
        bullet_sprite.setTexture(bullet_texture);
    }

    template <typename Buffer>
    void render_state(Buffer& buf, const state& st) {
        for (std::size_t i = 0; i < st.tanks.size(); ++i) {
            tank_sprite.setPosition(transform_coordinates(st.tanks[i].pos));
            tank_sprite.setRotation(st.tanks[i].rot * 180. / M_PI);

            buf.draw(tank_sprite);
        }

        bullet_sprite.setPosition(transform_coordinates(st.bullet));
        buf.draw(bullet_sprite);
    }
};

void render_frame(const state& st) {
    renderer r;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow win(sf::VideoMode(r.width, r.height), "TankGolf",
                         sf::Style::Default, settings);
    win.setFramerateLimit(30);


    double time = 0;
    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed)
                win.close();
        }

        time += 1/30.0;

        win.clear(sf::Color(30, 30, 30));

        r.render_state(win, st);

        win.display();
    }
}

void render_match(const match_t& match, const fs::path& outpath) {
}

} // namespace tg
