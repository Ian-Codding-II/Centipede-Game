/**
 * @file bullet.cpp
 * @author Roman Salazar Ian Codding II
 * @brief Implementation of Bullet class
 * @version 1.0 - Grid-Based
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 */

#include "../includes/bullet.h"
#include <cmath>
#include <iostream>


std::vector<Bullet*> Bullet::bullets;

// The actual shoot function
void Bullet::shoot(sf::Vector2i playerPos, float deltaTime, sf::Texture& bulletTex)
{
    //timeSinceLastShot += deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        // Center bullet on player
        sf::Vector2i bulletStart(
            playerPos.x + 16,  // assuming player is ~32px wide
            playerPos.y
        );

        Bullet* newBullet = new Bullet(bulletTex, bulletStart, 500.0f);  
        bullets.push_back(newBullet);

        std::cout << "New bullet created at (" 
                  << bulletStart.x << ", " << bulletStart.y << ")\n";

        //timeSinceLastShot = 0.0f;
    }
}