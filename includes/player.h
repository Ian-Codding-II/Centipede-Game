/**
 * @file player.h
 * @author Ian Codding II Roman Salazar
 * @brief Player class - the player-controlled character
 * @version 1.0 - Grid-Based
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 *
 * MOVEMENT:
 * - Grid-based (one cell at a time)
 * - WASD or Arrow keys to move
 * - Bounded within playable area
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.h"
#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * @class Player
 * @brief Player-controlled character
 */
class Player {
  public:
    static void startPlayer(sf::RectangleShape &rectangle, sf::Texture &playerTexture);
    static void movePlayer(sf::RectangleShape &playerRectangle, float deltaTime);
    bool boundsChecking(int x, int y);
    bool playerShoot(sf::RectangleShape &playerRect, sf::RectangleShape &bulletShape, sf::Texture &bulletTexture, Bullet &projectile);

  private:
};

#endif

// #ifndef PLAYER_H
// #define PLAYER_H

// #include <SFML/Graphics.hpp>
// #include "GameGrid.h"

// /**
//  * @class Player
//  * @brief Player-controlled character
//  *
//  * Responsibilities:
//  * - Store player position and state
//  * - Handle movement input (bounded to grid)
//  * - Fire bullets
//  * - Handle collision with centipede
//  * - Track lives
//  */
// class Player : public sf::Drawable {
// public:
//     /**
//      * @brief Constructor - create the player
//      *
//      * @param grid Pointer to GameGrid for movement and collision
//      * @param texture Reference to player sprite texture
//      */
//     Player(GameGrid* grid, sf::Texture& texture);

//     /**
//      * @brief Destructor
//      */
//     ~Player();

//     // ===== MOVEMENT =====

//     /**
//      * @brief Move player left
//      *
//      * Moves one grid cell left if not at left boundary.
//      * Updates grid occupancy.
//      *
//      * @return true if movement was successful
//      */
//     bool moveLeft();

//     /**
//      * @brief Move player right
//      *
//      * Moves one grid cell right if not at right boundary.
//      *
//      * @return true if movement was successful
//      */
//     bool moveRight();

//     /**
//      * @brief Move player up
//      *
//      * Moves one grid cell up if not at top boundary.
//      *
//      * @return true if movement was successful
//      */
//     bool moveUp();

//     /**
//      * @brief Move player down
//      *
//      * Moves one grid cell down if not at bottom boundary.
//      *
//      * @return true if movement was successful
//      */
//     bool moveDown();

//     /**
//      * @brief Reset player to starting position
//      *
//      * Called after player dies or game resets.
//      */
//     void reset();

//     // ===== POSITION & COLLISION =====

//     /**
//      * @brief Get current grid position
//      *
//      * @return Pair of (gridX, gridY)
//      */
//     std::pair<int, int> getPosition() const;

//     /**
//      * @brief Get player bounds for collision detection
//      *
//      * @return FloatRect in pixel coordinates
//      */
//     sf::FloatRect getGlobalBounds() const;

//     /**
//      * @brief Check if player overlaps with centipede at grid position
//      *
//      * @param gridX Grid X position to check
//      * @param gridY Grid Y position to check
//      * @return true if player is at that position
//      */
//     bool isAt(int gridX, int gridY) const;

//     // ===== SHOOTING =====

//     /**
//      * @brief Fire a bullet from player position
//      *
//      * Creates a new bullet moving upward from player position.
//      * Bullet is added to game's bullet list (not managed by player).
//      *
//      * @return Position where bullet should spawn (grid coordinates)
//      */
//     std::pair<int, int> shoot();

//     /**
//      * @brief Check if player can shoot (cooldown expired)
//      *
//      * @return true if enough time has passed since last shot
//      */
//     bool canShoot() const;

//     /**
//      * @brief Set shoot cooldown
//      *
//      * @param cooldown Time in seconds before player can shoot again
//      */
//     void setShootCooldown(float cooldown);

//     // ===== RENDERING =====

//     /**
//      * @brief Draw player sprite
//      *
//      * Inherited from sf::Drawable.
//      *
//      * @param target Render target
//      * @param states Render states
//      */
//     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

//     // ===== UPDATE =====

//     /**
//      * @brief Update player state each frame
//      *
//      * Decrements shoot cooldown timer.
//      *
//      * @param dt Delta time since last frame
//      */
//     void update(float dt);

//     // ===== DEBUG =====

//     /**
//      * @brief Print player state to console
//      */
//     void debugPrint() const;

// private:
//     // Grid reference
//     GameGrid* grid;

//     // Texture
//     sf::Texture& texture;

//     // Position (grid coordinates)
//     int gridX;
//     int gridY;

//     // Starting position
//     int startGridX;
//     int startGridY;

//     // Shoot cooldown
//     float shootCooldown;
//     float shootCooldownMax;

//     /**
//      * @brief Try to move to new position
//      *
//      * @param newX New grid X
//      * @param newY New grid Y
//      * @return true if movement was successful
//      */
//     bool tryMove(int newX, int newY);

//     /**
//      * @brief Update grid to reflect current position
//      */
//     void updateGridOccupancy();

//     /**
//      * @brief Clear player from grid
//      */
//     void clearFromGrid();
// };

// #endif // PLAYER_H