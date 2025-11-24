/**
 * @file bullet.cpp
 * @author Ian Codding II
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "../includes/bullet.h"
 
void Bullet::startBullet(sf::RectangleShape& bulletObj, sf::Texture& bulletTexture)
{
    bulletObj.setSize(sf::Vector2f(10.f, 10.f));
    bulletObj.setOutlineColor(sf::Color::Black);
    bulletObj.setPosition(10.f, 20.f);

    if (!bulletTexture.loadFromFile("/home/roman/CS151/Final/assets/purpleLaser.png"))
    {
        std::cerr << "There was an issue loading the player texture...\n";
    }
    else
    {
        bulletObj.setTexture(&bulletTexture);
    }
   bulletObj.setOutlineThickness(5.f);
   bulletObj.setPosition(10.f, 20.f);


}