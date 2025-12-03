// /**
//  * @file CollisionManager.cpp
//  * @author Ian Codding II
//  * @brief Implementation of CollisionManager
//  * @version 2.0 - Grid-Based
//  * @date 2025-11-26
//  *
//  * @copyright Copyright (c) 2025
//  */

// #include "../includes/Collision_Manager.h"
// #include <iostream>

// /**
//  * @brief Constructor
//  */
// CollisionManager::CollisionManager(GameGrid* grid)
//     : grid(grid), debugEnabled(false) {
//     std::cout << "[CollisionManager] Created" << std::endl;
// }

// /**
//  * @brief Destructor
//  */
// CollisionManager::~CollisionManager() {
//     std::cout << "[CollisionManager] Destroyed" << std::endl;
// }

// // ===== BULLET COLLISIONS =====

// /**
//  * @brief Check bullet vs centipede collision
//  *
//  * Uses grid coordinates for efficient checking.
//  * Returns which segment was hit.
//  */
// CollisionResult CollisionManager::checkBulletCentipede(Bullet* bullet, Centipede* centipede) {
//     if (!bullet || !centipede || !bullet->isAlive()) {
//         return CollisionResult(false);
//     }

//     auto [bulletX, bulletY] = bullet->getPosition();

//     // Check each centipede segment
//     for (int i = 0; i < centipede->getLength(); i++) {
//         auto [segX, segY] = centipede->getSegmentPosition(i);

//         // Check if bullet is at same grid position as segment
//         if (bulletX == segX && bulletY == segY) {
//             if (debugEnabled) {
//                 std::cout << "[Collision] Bullet hit Centipede segment " << i << std::endl;
//             }

//             return CollisionResult(true, "BulletCentipede", i);
//         }
//     }

//     return CollisionResult(false);
// }

// /**
//  * @brief Check bullet vs mushrooms collision
//  *
//  * Returns pointer to mushroom hit, or nullptr.
//  */
// Mushroom* CollisionManager::checkBulletMushroom(Bullet* bullet, const std::vector<Mushroom*>& mushrooms) {
//     if (!bullet || !bullet->isAlive()) {
//         return nullptr;
//     }

//     auto [bulletX, bulletY] = bullet->getPosition();

//     // Check each mushroom
//     for (auto mushroom : mushrooms) {
//         if (!mushroom) continue;

//         auto [mushX, mushY] = mushroom->getPosition();

//         // Check if bullet is at same grid position as mushroom
//         if (bulletX == mushX && bulletY == mushY) {
//             if (debugEnabled) {
//                 std::cout << "[Collision] Bullet hit Mushroom at (" << mushX << ", " << mushY << ")" << std::endl;
//             }

//             return mushroom;
//         }
//     }

//     return nullptr;
// }

// // ===== PLAYER COLLISIONS =====

// /**
//  * @brief Check player vs centipede collision
//  *
//  * Returns true if player touches any segment.
//  */
// bool CollisionManager::checkPlayerCentipede(Player* player, Centipede* centipede) {
//     if (!player || !centipede || !centipede->isAlive()) {
//         return false;
//     }

//     auto [playerX, playerY] = player->getPosition();

//     // Check each centipede segment
//     for (int i = 0; i < centipede->getLength(); i++) {
//         auto [segX, segY] = centipede->getSegmentPosition(i);

//         if (playerX == segX && playerY == segY) {
//             if (debugEnabled) {
//                 std::cout << "[Collision] Player hit Centipede segment " << i << std::endl;
//             }

//             return true;
//         }
//     }

//     return false;
// }

// /**
//  * @brief Check player vs multiple centipedes
//  */
// bool CollisionManager::checkPlayerCentipedes(Player* player, const std::vector<Centipede*>& centipedes) {
//     for (auto centipede : centipedes) {
//         if (checkPlayerCentipede(player, centipede)) {
//             return true;
//         }
//     }

//     return false;
// }

// // ===== BATCH OPERATIONS =====

// /**
//  * @brief Check all bullet collisions
//  *
//  * Processes all bullets and returns collisions that occurred.
//  */
// std::vector<CollisionResult> CollisionManager::checkAllBulletCollisions(
//     std::vector<Bullet*>& bullets,
//     std::vector<Centipede*>& centipedes,
//     std::vector<Mushroom*>& mushrooms) {

//     std::vector<CollisionResult> results;

//     // Check each bullet
//     for (int b = 0; b < static_cast<int>(bullets.size()); b++) {
//         if (!bullets[b] || !bullets[b]->isAlive()) {
//             continue;
//         }

//         // Check vs all centipedes
//         for (auto centipede : centipedes) {
//             CollisionResult collision = checkBulletCentipede(bullets[b], centipede);

//             if (collision.collided) {
//                 results.push_back(collision);
//                 bullets[b]->kill();  // Destroy bullet
//                 break;  // Bullet destroyed, check next bullet
//             }
//         }

//         // Only check mushrooms if bullet still alive
//         if (bullets[b]->isAlive()) {
//             Mushroom* mushroom = checkBulletMushroom(bullets[b], mushrooms);

//             if (mushroom) {
//                 results.push_back(CollisionResult(true, "BulletMushroom", -1));
//                 bullets[b]->kill();  // Destroy bullet
//             }
//         }
//     }

//     return results;
// }

// // ===== PRIVATE =====

// /**
//  * @brief Check AABB collision
//  *
//  * Simple rectangle overlap check (not used in grid system, but kept for reference).
//  */
// bool CollisionManager::checkAABBCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) const {
//     return rect1.intersects(rect2);
// }