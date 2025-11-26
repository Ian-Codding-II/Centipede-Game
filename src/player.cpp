/**
 * @file player.cpp
 * @author Ian Codding II
 * @brief
 * @version 0.1
 * @date 2025-10-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../includes/player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

void Player::startPlayer(sf::RectangleShape &rectangle, sf::Texture &playerTexture) {
    // Rectangle for player
    rectangle.setSize(sf::Vector2f(30.f, 30.f));
    rectangle.setOutlineColor(sf::Color::Black);
    // rectangle.setOutlineThickness(5.f); // Do we need this?
    rectangle.setPosition(400.f, 500.f);

    // Load player texture
    if (!playerTexture.loadFromFile("/home/roman/CS151/Final/assets/HqCreature.png")) {
        std::cerr << "There was an issue loading the player texture...\n";
    }
    std::cout << "Success loading player texture...\n";

    // Apply texture to rectangle
    rectangle.setTexture(&playerTexture);
}

void Player::movePlayer(sf::RectangleShape &playerRectangle) {
    sf::Vector2f pos = playerRectangle.getPosition();
    std::cout << "The current player position is equal to x: " << pos.x << " and y: " << pos.y << '\n';

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) && boundsChecking(pos.x, pos.y)) {
        if (boundsChecking(pos.x - 15, pos.y))
            ;
        playerRectangle.setPosition(pos.x - 15, pos.y); // Move left 20 pixels

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && boundsChecking(pos.x, pos.y)) {
        if (boundsChecking(pos.x + 15, pos.y))
            ;
        playerRectangle.setPosition(pos.x + 15, pos.y); // Move right 20 pixels

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) && boundsChecking(pos.x, pos.y)) {
        if (boundsChecking(pos.x, pos.y + 15))
            ;
        playerRectangle.setPosition(pos.x, pos.y + 15); // Move down 20 pixels
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) && boundsChecking(pos.x, pos.y)) {
        if (boundsChecking(pos.x, pos.y - 15))
            ;
        playerRectangle.setPosition(pos.x, pos.y - 15); // Move up 20 pixels
    }

    // This is temporary bounds checking. Intentionally rough
    if (pos.x <= 5 && pos.y > 405) {
        playerRectangle.setPosition(6, pos.y); // Seems to work
    } else if (pos.x <= 5 && pos.y <= 405) {
        playerRectangle.setPosition(pos.x + 1, 406);
    } else if (pos.y < 405) {
        playerRectangle.setPosition(pos.x, 406);

    } else if (pos.x > 795 && pos.y <= 595) {
        playerRectangle.setPosition(770, pos.y);
    } else if (pos.x > 795 && pos.y >= 595) {
        playerRectangle.setPosition(pos.x - 1, pos.y - 1);
    } else if (pos.y >= 595) {
        playerRectangle.setPosition(pos.x, 570);
    }
}

bool Player::boundsChecking(int x, int y) {
    if (x >= 795 || y <= 405 || x <= 5 || y <= 595) {
        return 0;
    }
    return 1;
}

void Player::playerShoot(sf::RectangleShape &playerRect, sf::RectangleShape &bulletShape, sf::Texture &bulletTexture, Bullet &projectile) {
    sf::Vector2f pos;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        pos = playerRect.getPosition();
        std::cout << "Current bullet position x: " << pos.x << " y: " << pos.y << '\n';
        projectile.bullets.push_back(bulletShape);
        // std::cout << projectile.bullets.size();
        bulletShape.setPosition(pos.x, pos.y);
    }
}
