/**
 * @file bullet.h
 * @author Ian Codding II Roman Salazar
 * @brief Bullet class - projectiles fired by player
 * @version 1.0 - Grid-Based
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 *
 * BULLET MECHANICS:
 *
 * Bullets move upward from player position.
 * - One bullet per shot (with cooldown)
 * - Moves multiple grid cells per frame (fast)
 * - Destroyed when off-screen
 * - Destroyed on collision with centipede or mushroom
 * - Can pass through empty space
 *
 * SPEED:
 * - 5 grid cells per second (approximately)
 * - Adjustable for difficulty
 */

#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
// #include "GameGrid.h"

// /**
//  * @class Bullet
//  * @brief A single bullet projectile
//  *
//  * Responsibilities:
//  * - Store position and velocity
//  * - Move upward each frame
//  * - Check if still in bounds
//  * - Check collisions with obstacles
//  * - Draw to screen
//  */
// class Bullet : public sf::Drawable {
// public:
//     /**
//      * @brief Constructor - create a bullet
//      *
//      * @param grid Pointer to GameGrid
//      * @param texture Reference to bullet sprite texture
//      * @param startGridX Starting grid X position
//      * @param startGridY Starting grid Y position
//      * @param speed Cells per second (default 5.0)
//      */
//     Bullet(GameGrid* grid, sf::Texture& texture, int startGridX, int startGridY, float speed = 5.0f);

//     /**
//      * @brief Destructor
//      */
//     ~Bullet();

//     // ===== MOVEMENT =====

//     /**
//      * @brief Update bullet position
//      *
//      * Moves bullet upward based on speed and delta time.
//      * Automatically marks as dead if off-screen.
//      *
//      * @param dt Delta time since last frame
//      */
//     void update(float dt);

//     // ===== COLLISION =====

//     /**
//      * @brief Check if bullet is still alive (in bounds)
//      *
//      * @return true if bullet is still on screen
//      */
//     bool isAlive() const;

//     /**
//      * @brief Get current grid position
//      *
//      * @return Pair of (gridX, gridY)
//      */
//     std::pair<int, int> getPosition() const;

//     /**
//      * @brief Get pixel position
//      *
//      * @return Pixel coordinates as sf::Vector2f
//      */
//     sf::Vector2f getPixelPosition() const;

//     /**
//      * @brief Get collision bounds
//      *
//      * @return FloatRect in pixel coordinates
//      */
//     sf::FloatRect getGlobalBounds() const;

//     /**
//      * @brief Check what's at bullet position
//      *
//      * Useful for collision detection.
//      *
//      * @return CellContent flags at bullet's current location
//      */
//     int checkCellContent() const;

//     /**
//      * @brief Kill the bullet
//      *
//      * Marks bullet as dead so it will be removed from game.
//      */
//     void kill();

//     // ===== RENDERING =====

//     /**
//      * @brief Draw bullet
//      *
//      * Inherited from sf::Drawable.
//      *
//      * @param target Render target
//      * @param states Render states
//      */
//     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

// private:
//     // Grid reference
//     GameGrid* grid;

//     // Texture
//     sf::Texture& texture;

//     // Position (using floating point for smooth motion between cells)
//     float positionX;  // Grid X as float for precision
//     float positionY;  // Grid Y as float for precision

//     // Velocity (cells per second)
//     float velocityY;  // Moving upward (negative direction)

//     // State
//     bool alive;
// };

// #endif // BULLET_H

// - Move upward at constant speed
// - Check if off-screen (deactivate)
// - Simple rectangular collision bounds
class Bullet {
  public:
    float shootCooldown = 0.1f;  // Temp
    float timeSinceLastShot = 0.0f; // Temp

    static void startBullet(sf::RectangleShape &bulletObj, sf::Texture &atlasTexture);
    int isShooting(sf::RectangleShape &playerRect, sf::RectangleShape &bulletShape, sf::Texture &bulletTexture, Bullet &projectile, float deltaTime);
    int getPlayerPosition();
    sf::Vector2f bulletPath{0.f, -1.f};

    std::vector<sf::RectangleShape> bullets;

  private:
};

#endif