/**
 * @file main.cpp
 * @author Ian Codding II
 * @brief Entry point for Centipede game - sets up window and main loop
 * @version 2.0
 * @date 2025-10-27
 * 
 * @copyright Copyright (c) 2025
 */

#include "../includes/errorHandler.h"
#include "../includes/game.h"
#include "../includes/Game_State.h"
#include "../includes/ScreenManager.h"
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Centipede");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        // Game rendering will go here
        window.display();
    }

    std::cout << "Game closed successfully!" << std::endl;
    return 0;
}