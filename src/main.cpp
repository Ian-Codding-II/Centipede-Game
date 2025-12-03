/**
 * @file main.cpp
 * @author Ian Codding II
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../includes/grid.h"
#include "../includes/mushroom.h"
#include "../includes/centipede.h"
#include "../includes/animated_object.h"
#include "../includes/collision_object.h"

int main() {
    sf::Texture atlas;
    if (!atlas.loadFromFile("assets/sprites/centipede_atlas_revised_1.png")) {
        std::cerr << "Cannot load textures!" << std::endl;
    }

    Grid grid(sf::FloatRect(160, 0, 360, 360), 16);
    centipede newCenti(atlas, 8, grid.GetPosition(sf::Vector2f(200, 200)), sf::Vector2i(2, 2));

    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(640, 360), "Centipede");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }
            
        window.clear(sf::Color::Black);
        // Game rendering will go here
        newCenti.update(clock.restart().asSeconds());
        newCenti.move();
        window.draw(newCenti);
        // std::cout << newMushroom.getPosition().x << ' ' << newMushroom.getPosition().y << std::endl;
        window.display();
    }

    std::cout << "Game closed successfully!" << std::endl;
    return 0;
}