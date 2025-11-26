/**
 * @file Player.h
 * @author Ian Codding II
 * @brief Player class - the player-controlled character
 * @version 1.0 - Grid-Based
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 *
 * PLAYER MECHANICS:
 *
 * The player is a single character that moves on the grid.
 * - Positioned at the bottom of the screen
 * - Can move left/right/up/down one grid cell per input
 * - Shoots bullets upward
 * - Dies if hit by centipede
 * - Respawns at starting position after death
 *
 * MOVEMENT:
 * - Grid-based (one cell at a time)
 * - WASD or Arrow keys to move
 * - Bounded within playable area
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