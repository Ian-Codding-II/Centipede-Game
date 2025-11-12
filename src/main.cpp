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
#include "mushroom.h"

Mushroom newMushroom(200, 200);

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 360), "Centipede");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        // Game rendering will go here
        window.draw(newMushroom);
        window.display();
    }

    std::cout << "Game closed successfully!" << std::endl;
    return 0;
}