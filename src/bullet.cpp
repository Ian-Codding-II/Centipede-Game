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

// /**
//  * @brief Constructor - create a bullet
//  *
//  * @param grid Pointer to GameGrid
//  * @param texture Reference to bullet sprite texture
//  * @param startGridX Starting grid X
//  * @param startGridY Starting grid Y
//  * @param speed Cells per second
//  */
// Bullet::Bullet(GameGrid* grid, sf::Texture& texture, int startGridX, int startGridY, float speed)
//     : grid(grid),
//       texture(texture),
//       positionX(static_cast<float>(startGridX)),
//       positionY(static_cast<float>(startGridY)),
//       velocityY(-speed),  // Negative = moving up
//       alive(true) {

//     std::cout << "[Bullet] Created at grid (" << startGridX << ", " << startGridY << ")" << std::endl;
// }

// /**
//  * @brief Destructor
//  */
// Bullet::~Bullet() {
//     std::cout << "[Bullet] Destroyed" << std::endl;
// }

// // ===== MOVEMENT =====

// /**
//  * @brief Update bullet position
//  *
//  * Moves upward by velocityY * dt cells.
//  * Marks as dead if off-screen.
//  */
// void Bullet::update(float dt) {
//     if (!alive) {
//         return;
//     }

//     // Move upward
//     positionY += velocityY * dt;

//     // Check if off-screen (top boundary)
//     if (positionY < 0) {
//         alive = false;
//         std::cout << "[Bullet] Off-screen - destroyed" << std::endl;
//     }
// }

// // ===== COLLISION =====

// /**
//  * @brief Check if alive
//  */
// bool Bullet::isAlive() const {
//     return alive;
// }

// /**
//  * @brief Get current grid position
//  */
// std::pair<int, int> Bullet::getPosition() const {
//     int gridX = static_cast<int>(positionX);
//     int gridY = static_cast<int>(positionY);

//     return std::make_pair(gridX, gridY);
// }

// /**
//  * @brief Get pixel position
//  */
// sf::Vector2f Bullet::getPixelPosition() const {
//     float pixelX = positionX * GameGrid::CELL_SIZE + GameGrid::CELL_SIZE / 2;
//     float pixelY = positionY * GameGrid::CELL_SIZE + GameGrid::CELL_SIZE / 2;

//     return sf::Vector2f(pixelX, pixelY);
// }

// /**
//  * @brief Get collision bounds
//  */
// sf::FloatRect Bullet::getGlobalBounds() const {
//     auto [gridX, gridY] = getPosition();

//     float pixelX = grid->gridToPixelX(gridX);
//     float pixelY = grid->gridToPixelY(gridY);

//     return sf::FloatRect(pixelX, pixelY, GameGrid::CELL_SIZE, GameGrid::CELL_SIZE);
// }

// /**
//  * @brief Check cell content at bullet position
//  */
// int Bullet::checkCellContent() const {
//     auto [gridX, gridY] = getPosition();

//     if (!grid->isInBounds(gridX, gridY)) {
//         return EMPTY;
//     }

//     // Get content at this cell (this would need to be added to GameGrid)
//     // For now, return empty
//     return EMPTY;
// }

// /**
//  * @brief Kill bullet
//  */
// void Bullet::kill() {
//     alive = false;
//     std::cout << "[Bullet] Killed by collision" << std::endl;
// }

// // ===== RENDERING =====

// /**
//  * @brief Draw bullet
//  */
// void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//     if (!alive) {
//         return;  // Don't draw dead bullets
//     }

//     sf::Sprite sprite(texture);

//     // Set texture rect for bullet in atlas - TODO: Adjust to match your atlas
//     sprite.setTextureRect(sf::IntRect(64, 32, 32, 32));  // Bullet position in atlas

//     sf::Vector2f pixelPos = getPixelPosition();
//     sprite.setPosition(pixelPos);

//     // Center sprite on position
//     sprite.setOrigin(16, 16);  // 32x32 / 2 = 16

//     target.draw(sprite, states);
// }

void Bullet::startBullet(sf::RectangleShape &bulletObj, sf::Texture &atlasTexture) {
    bulletObj.setSize(sf::Vector2f(10.f, 10.f));
    bulletObj.setOutlineColor(sf::Color::Black);
    bulletObj.setOutlineThickness(0.f);

    // Use atlas texture (already loaded in Game::loadTextures)
    bulletObj.setTexture(&atlasTexture);

    // Pick the bullet sprite from the atlas
    bulletObj.setTextureRect(sf::IntRect(8 * 12, 8 * 1, 8, 8));

    // Start off-screen or default location
    bulletObj.setPosition(100.f, 100.f);
}


int Bullet::isShooting(sf::RectangleShape &playerRect, sf::RectangleShape &bulletShape, sf::Texture &bulletTexture, Bullet &projectile, float deltaTime) {

    timeSinceLastShot += deltaTime;
    int *vectorSize;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeSinceLastShot >= shootCooldown) {
        sf::Vector2f pos = playerRect.getPosition();
        bulletShape.setPosition(pos.x + 9, pos.y);
        projectile.bullets.push_back(bulletShape);
        std::cout << "New bullet created." << '\n';
        timeSinceLastShot = 0.0f;
    }
    for (int i = bullets.size() - 1; i >= 0; i--) {
        sf::Vector2f del = bullets[i].getPosition();
        if (del.y <= 5) {
            bullets.erase(bullets.begin() + i);
            std::cout << "Bullet deleted #" << i << '\n';
        }
    }

    return bullets.size();
}