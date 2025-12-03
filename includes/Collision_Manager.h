// /**
//  * @file CollisionManager.h
//  * @author Ian Codding II
//  * @brief Collision detection system
//  * @version 1.0 - Grid-Based
//  * @date 2025-11-26
//  *
//  * @copyright Copyright (c) 2025
//  *
//  * COLLISION SYSTEM:
//  *
//  * Handles all collision detection between game objects.
//  * Uses the grid system for efficient collision checking.
//  *
//  * COLLISION TYPES:
//  * - Bullet vs Centipede: Bullet destroyed, segment damaged
//  * - Bullet vs Mushroom: Bullet destroyed, mushroom damaged
//  * - Player vs Centipede: Player dies, loses life
//  * - Centipede vs Mushroom: Centipede bounces (handled by centipede)
//  * - Centipede vs Wall: Centipede bounces (handled by centipede)
//  */

// #ifndef COLLISION_MANAGER_H
// #define COLLISION_MANAGER_H

// #include <SFML/Graphics.hpp>
// #include "GameGrid.h"
// #include "Centipede.h"
// #include "player.h"
// #include "bullet.h"
// #include "mushroom.h"
// #include <vector>

// /**
//  * @struct CollisionResult
//  * @brief Information about a collision
//  */
// struct CollisionResult {
//     bool collided;           // Did collision occur?
//     std::string type;        // Type of collision (e.g., "BulletCentipede")
//     int data;                // Additional data (e.g., segment index)

//     CollisionResult(bool c = false, std::string t = "", int d = -1)
//         : collided(c), type(t), data(d) {}
// };

// /**
//  * @class CollisionManager
//  * @brief Manages all collision detection in the game
//  *
//  * Responsibilities:
//  * - Check bullet vs centipede collisions
//  * - Check bullet vs mushroom collisions
//  * - Check player vs centipede collisions
//  * - Return collision results to game logic
//  */
// class CollisionManager {
// public:
//     /**
//      * @brief Constructor
//      *
//      * @param grid Pointer to GameGrid for spatial queries
//      */
//     CollisionManager(GameGrid* grid);

//     /**
//      * @brief Destructor
//      */
//     ~CollisionManager();

//     // ===== BULLET COLLISIONS =====

//     /**
//      * @brief Check if bullet hits centipede
//      *
//      * If collision occurs:
//      * - Returns which segment was hit
//      * - Game should destroy bullet and damage segment
//      *
//      * @param bullet Pointer to bullet
//      * @param centipede Pointer to centipede
//      * @return CollisionResult with collision info
//      */
//     CollisionResult checkBulletCentipede(Bullet* bullet, Centipede* centipede);

//     /**
//      * @brief Check if bullet hits any mushroom
//      *
//      * @param bullet Pointer to bullet
//      * @param mushrooms Vector of mushroom pointers
//      * @return Pointer to mushroom hit, or nullptr if no collision
//      */
//     Mushroom* checkBulletMushroom(Bullet* bullet, const std::vector<Mushroom*>& mushrooms);

//     // ===== PLAYER COLLISIONS =====

//     /**
//      * @brief Check if player collides with centipede
//      *
//      * @param player Pointer to player
//      * @param centipede Pointer to centipede
//      * @return true if collision occurred
//      */
//     bool checkPlayerCentipede(Player* player, Centipede* centipede);

//     /**
//      * @brief Check if player collides with any centipedes
//      *
//      * Useful for checking against multiple centipedes (from splits).
//      *
//      * @param player Pointer to player
//      * @param centipedes Vector of centipede pointers
//      * @return true if any collision occurred
//      */
//     bool checkPlayerCentipedes(Player* player, const std::vector<Centipede*>& centipedes);

//     // ===== BATCH OPERATIONS =====

//     /**
//      * @brief Check all bullet collisions in one call
//      *
//      * Checks all bullets against all centipedes and mushrooms.
//      * Returns list of collisions that occurred.
//      *
//      * @param bullets Vector of bullet pointers
//      * @param centipedes Vector of centipede pointers
//      * @param mushrooms Vector of mushroom pointers
//      * @return Vector of CollisionResults
//      */
//     std::vector<CollisionResult> checkAllBulletCollisions(
//         std::vector<Bullet*>& bullets,
//         std::vector<Centipede*>& centipedes,
//         std::vector<Mushroom*>& mushrooms
//     );

//     // ===== DEBUG =====

//     /**
//      * @brief Enable/disable debug output
//      *
//      * @param enable true to print collision info
//      */
//     void setDebug(bool enable) { debugEnabled = enable; }

// private:
//     // Grid reference
//     GameGrid* grid;

//     // Debug flag
//     bool debugEnabled;

//     /**
//      * @brief Check AABB (Axis-Aligned Bounding Box) collision
//      *
//      * Simple rectangle overlap check.
//      *
//      * @param rect1 First rectangle
//      * @param rect2 Second rectangle
//      * @return true if rectangles overlap
//      */
//     bool checkAABBCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) const;
// };

// #endif // COLLISION_MANAGER_H