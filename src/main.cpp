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
#include "../includes/mushroom.h"


int main() {
    sf::Texture atlas;
    if (!atlas.loadFromFile("assets/centipede_atlas_revised_1.png")) {
        std::cerr << "Cannot load textures!" << std::endl;
    }

    Mushroom newMushroom(atlas, sf::IntRect(8*8, 8*2, 8, 8), sf::Vector2i(100, 100));

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
        newMushroom.hit(3);
        newMushroom.update();
        window.draw(newMushroom);
        window.display();
    }

    std::cout << "Game closed successfully!" << std::endl;
    return 0;
}