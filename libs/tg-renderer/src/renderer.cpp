#include <tg-renderer/renderer.hpp>

#include <iostream>
#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace tg {

void render_frame(const state& st) {
    const unsigned width = 500, height = 400;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow win(sf::VideoMode(width, height), "TankGolf",
                         sf::Style::Default, settings);
    win.setFramerateLimit(30);

    sf::Texture texture;
    if (!texture.loadFromFile("../libs/tg-renderer/resources/tank.png")) {
        std::cerr << "Could not load tank texture.\n";
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

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

        sprite.setPosition(sf::Vector2f(100.0 + std::sin(time) * 50, 200.0));
        win.draw(sprite);
        win.display();
    }
}

void render_match(const std::vector<event>& match, const fs::path& outpath) {
}

} // namespace tg
