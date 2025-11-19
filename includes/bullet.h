/**
 * @file bullet.h
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
#ifndef BULLET_H
#define BULLET_H
// - Move upward at constant speed
// - Check if off-screen (deactivate)
// - Simple rectangular collision bounds
class Bullet
{
    public:
        void startBullet(sf::RectangleShape& bulletObj, sf::Texture& bulletTexture);
        int getPlayerPosition();
        sf::Vector2f bulletPath{0.f, -1.f};
        std::vector<sf::RectangleShape> bullets;

    private:
};



#endif