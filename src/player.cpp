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


#include <SFML/Graphics.hpp>
#include <iostream>
#include "../includes/player.h"
#include <fstream>
#include <chrono>
#include <thread>


void Player::startPlayer(sf::RectangleShape& rectangle, sf::Texture& playerTexture)
{
 // Rectangle for player
    rectangle.setSize(sf::Vector2f(30.f, 30.f));
    rectangle.setOutlineColor(sf::Color::Black);
    //rectangle.setOutlineThickness(5.f); // Do we need this?
    rectangle.setPosition(400.f, 500.f);

    // Load player texture

    if (!playerTexture.loadFromFile("/home/roman/CS151/Final/assets/HqCreature.png")) // Absolute path seems to work
    {
        std::cerr << "There was an issue loading the player texture...\n";
    }
    else
    {
        std::cout << "Success loading player texture...\n";

    }

    // Apply texture to rectangle
    rectangle.setTexture(&playerTexture);

    


}




void Player::movePlayer(sf::RectangleShape &playerRectangle, float deltaTime)
{
    sf::Vector2f pos = playerRectangle.getPosition();
    float speed = 500.f; 

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        pos.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        pos.x += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        pos.y -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        pos.y += speed * deltaTime;

    float left = 0.f;
    float right = 1200.f - playerRectangle.getSize().x;
    float top = 600.f;
    float bottom = 800.f - playerRectangle.getSize().y;

    if (pos.x < left) pos.x = left;
    if (pos.x > right) pos.x = right;
    if (pos.y < top) pos.y = top;
    if (pos.y > bottom) pos.y = bottom;

    playerRectangle.setPosition(pos);
}







bool Player::boundsChecking(int x, int y)
{
    if(x >= 795 || y <= 405 || x <= 5 || y <= 595)
    {
       return 0;
    }
    return 1;
}

/*
bool Player::playerShoot(sf::RectangleShape& playerRect,sf::RectangleShape& bulletShape ,sf::Texture& bulletTexture,Bullet &projectile)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        return true;
    }
    else
    {
        return false;
    }
   
    


}

*/
