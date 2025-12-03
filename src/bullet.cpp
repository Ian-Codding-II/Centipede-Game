/**
 * @file bullet.cpp
 * @author Roman Salazar Ian Codding II
 * @brief Implementation of Bullet class
 * @version 1.0 - Grid-Based
 * @date 2025-11-26
 * @copyright Copyright (c) 2025
 */

#include "../includes/bullet.h"
#include <cmath>
#include <iostream>

// Define static member variables
std::vector<Bullet*> Bullet::bullets;
float Bullet::timeSinceLastShot = 0.0f;
float Bullet::shootCooldown = 0.1f;

/**
 * @brief The actual shoot function
 * Handles keyboard input for space bar and creates bullets.
 * @param playerPos Player position to spawn bullet from
 * @param deltaTime Time since last frame
 * @param bulletTex Bullet texture reference
 */
void Bullet::shoot(sf::Vector2f playerPos, float deltaTime, sf::Texture& bulletTex)
{
    timeSinceLastShot += deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeSinceLastShot >= shootCooldown)
    {
        // Center bullet on player
        sf::Vector2i bulletStart(
            playerPos.x + 16,  
            playerPos.y
        );

        Bullet* newBullet = new Bullet(bulletTex, bulletStart, 500.0f);  
        bullets.push_back(newBullet);

        std::cout << "New bullet created at (" 
                  << bulletStart.x << ", " << bulletStart.y << ")\n";

        timeSinceLastShot = 0.0f;
    }
}