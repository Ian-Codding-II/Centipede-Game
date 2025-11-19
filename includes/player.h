/**
 * @file player.h
 * @author Ian Codding II
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

// - Handle WASD/Arrow input
// - Update position with speed
// - Clamp to screen bounds
// - Shoot bullets on spacebar
// - Track lives
#include <SFML/Graphics.hpp>  
#include <iostream>
#ifndef PLAYER_H
#define PLAYER_H
#include "../includes/bullet.h"

class Player
{
    public:

        void startPlayer(sf::RectangleShape& rectangle, sf::Texture& playerTexture);
        void movePlayer(sf::RectangleShape &playerRectangle);
        bool boundsChecking(int x, int y);
        void playerShoot(sf::RectangleShape& playerRect,sf::RectangleShape& bulletShape ,sf::Texture& bulletTexture,Bullet &projectile);

        std::vector<sf::RectangleShape> bullets; 


    private:

};
 






#endif