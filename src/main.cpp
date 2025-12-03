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
#include "../includes/animated_object.h"
#include "../includes/collision_object.h"


int main() {
    sf::Texture atlas;
    if (!atlas.loadFromFile("assets/sprites/centipede_atlas_revised_1.png")) {
        std::cerr << "Cannot load textures!" << std::endl;
    }

    Grid grid(sf::FloatRect(160, 0, 360, 360), 16);
    Mushroom newMushroom(atlas, sf::IntRect(8*8, 8*2, 8, 8), sf::Vector2f(100, 100));
    Mushroom newMushroom2(atlas, sf::IntRect(8*8, 8*2, 8, 8), sf::Vector2f(100, 100));
    anim_obj newObject(atlas, sf::IntRect(0, 0, 8, 8), 4);

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
        newMushroom.setPosition(grid.GetPosition(sf::Vector2f(1, 1)));
        newMushroom.setScale(sf::Vector2i(2, 2));
        newMushroom.update();

        newMushroom2.setPosition(grid.GetPosition(sf::Vector2f(210, 1)));
        newMushroom2.setScale(sf::Vector2i(2, 2));
        newMushroom2.update();
        
        newObject.update(clock.restart().asSeconds());
        newObject.setPosition(grid.GetPosition(sf::Vector2f(700, 800)));
        newObject.setScale(sf::Vector2i(2, 2));
        window.draw(newObject);
        window.draw(newMushroom);
        window.draw(newMushroom2);

        // std::cout << newMushroom.getPosition().x << ' ' << newMushroom.getPosition().y << std::endl;
        window.display();
    }

    std::cout << "Game closed successfully!" << std::endl;
    return 0;
}