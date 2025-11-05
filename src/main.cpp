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
#include "../includes/player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Centipede");
    window.setFramerateLimit(60);
    

    sf::RectangleShape player; // Initialize a player object
    sf::RectangleShape bullet; // Initialize a bullet object
    sf::Texture playerTexture;  // Initialize a player texture
    sf::Texture bulletTexture;  // Initialize a bullet texture
    //sf::Vector2f bulletPath = player.getPosition();
    startPlayer(player,playerTexture); // Pass the player rectangle object and the player texture
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        // execute with g++ main.cpp player.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
        // execute with g++ main.cpp player.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
        // execute with g++ main.cpp player.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
        // execute with g++ main.cpp player.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
        // execute with g++ main.cpp player.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
        // execute with g++ main.cpp player.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
        // execute with g++ main.cpp player.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
        // execute with g++ main.cpp player.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
        // execute with g++ main.cpp player.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
        // execute with g++ main.cpp player.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system



        movePlayer(player);
        //playerShoot(bulletPath,bullet,bulletTexture);
        window.clear(sf::Color::Black);
        window.draw(player);
        //window.draw(bullet);

        // Game rendering will go here
        window.display();
    }

    std::cout << "Game closed successfully!" << std::endl;
    return 0;
}