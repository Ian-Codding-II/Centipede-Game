/**
 * @file player.cpp
 * @author Roman Salazar Ian Codding II
 * @brief Implementation of Player class
 * @version 2.0 - Grid-Based
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 */
#include "../includes/player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

void Player::startPlayer(sf::RectangleShape &rectangle, sf::Texture &playerTexture) {
    // Rectangle for player
    rectangle.setSize(sf::Vector2f(30.f, 30.f));
    rectangle.setOutlineColor(sf::Color::Black);
    // rectangle.setOutlineThickness(5.f); // Do we need this?
    rectangle.setPosition(400.f, 500.f);

    // Load player texture

    // if (!playerTexture.loadFromFile("/home/roman/CS151/Final/assets/HqCreature.png")) // Absolute path seems to work
    // {
    //     std::cerr << "There was an issue loading the player texture...\n";
    // } else {
    //     std::cout << "Success loading player texture...\n";
    // }

    // Apply texture to rectangle
    rectangle.setTexture(&playerTexture);
    rectangle.setTextureRect(sf::IntRect(12 * 8, 0, 8, 8));
    // player->setScale(sf::Vector2f(3,3));
}

void Player::movePlayer(sf::RectangleShape &playerRectangle, float deltaTime, const sf::FloatRect &gridBounds) {
    sf::Vector2f pos = playerRectangle.getPosition();
    float speed = 500.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        pos.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        pos.x += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        pos.y -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        pos.y += speed * deltaTime;

    // Use grid bounds instead of hard-coded numbers
    float left = gridBounds.left;
    float right = gridBounds.left + gridBounds.width - playerRectangle.getSize().x;
    float top = gridBounds.top + gridBounds.height - 200; // PLAYER AREA
    float bottom = gridBounds.top + gridBounds.height - playerRectangle.getSize().y;

    // Apply clamping
    if (pos.x < left)
        pos.x = left;
    if (pos.x > right)
        pos.x = right;
    if (pos.y < top)
        pos.y = top;
    if (pos.y > bottom)
        pos.y = bottom;

    playerRectangle.setPosition(pos);
}

// #include "../includes/player.h"
// #include <iostream>

// /**
//  * @brief Constructor - create the player
//  *
//  * Initializes player at bottom center of screen.
//  *
//  * @param grid Pointer to GameGrid
//  * @param texture Reference to player sprite texture
//  */
// Player::Player(GameGrid* grid, sf::Texture& texture)
//     : grid(grid),
//       texture(texture),
//       shootCooldown(0.0f),
//       shootCooldownMax(0.2f) {

//     std::cout << "[Player] Constructor called" << std::endl;

//     // Start at bottom center
//     startGridX = grid->getGridWidth() / 2;
//     startGridY = grid->getGridHeight() - 2;  // 2 cells from bottom

//     gridX = startGridX;
//     gridY = startGridY;

//     // Mark player on grid
//     updateGridOccupancy();

//     std::cout << "[Player] Player created at (" << gridX << ", " << gridY << ")" << std::endl;
// }

// /**
//  * @brief Destructor
//  */
// Player::~Player() {
//     std::cout << "[Player] Destructor called" << std::endl;
//     clearFromGrid();
// }

// // ===== MOVEMENT =====

// /**
//  * @brief Move player left
//  */
// bool Player::moveLeft() {
//     return tryMove(gridX - 1, gridY);
// }

// /**
//  * @brief Move player right
//  */
// bool Player::moveRight() {
//     return tryMove(gridX + 1, gridY);
// }

// /**
//  * @brief Move player up
//  */
// bool Player::moveUp() {
//     return tryMove(gridX, gridY - 1);
// }

// /**
//  * @brief Move player down
//  */
// bool Player::moveDown() {
//     return tryMove(gridX, gridY + 1);
// }

// /**
//  * @brief Reset player to starting position
//  */
// void Player::reset() {
//     std::cout << "[Player] Resetting to starting position" << std::endl;
//     clearFromGrid();

//     gridX = startGridX;
//     gridY = startGridY;
//     shootCooldown = 0.0f;

//     updateGridOccupancy();
// }

// // ===== POSITION & COLLISION =====

// /**
//  * @brief Get current position
//  */
// std::pair<int, int> Player::getPosition() const {
//     return std::make_pair(gridX, gridY);
// }

// /**
//  * @brief Get global bounds
//  */
// sf::FloatRect Player::getGlobalBounds() const {
//     float pixelX = grid->gridToPixelX(gridX);
//     float pixelY = grid->gridToPixelY(gridY);

//     return sf::FloatRect(pixelX, pixelY, GameGrid::CELL_SIZE, GameGrid::CELL_SIZE);
// }

// /**
//  * @brief Check if player is at position
//  */
// bool Player::isAt(int checkX, int checkY) const {
//     return gridX == checkX && gridY == checkY;
// }

// // ===== SHOOTING =====

// /**
//  * @brief Fire a bullet
//  *
//  * Returns the grid position where bullet should spawn (one cell above player).
//  *
//  * @return (gridX, gridY - 1) where bullet spawns
//  */
// std::pair<int, int> Player::shoot() {
//     if (canShoot()) {
//         shootCooldown = shootCooldownMax;
//         std::cout << "[Player] Shot fired from (" << gridX << ", " << gridY << ")" << std::endl;
//         return std::make_pair(gridX, gridY - 1);
//     }

//     return std::make_pair(-1, -1);  // Invalid - can't shoot
// }

// /**
//  * @brief Check if can shoot
//  */
// bool Player::canShoot() const {
//     return shootCooldown <= 0.0f;
// }

// /**
//  * @brief Set shoot cooldown
//  */
// void Player::setShootCooldown(float cooldown) {
//     shootCooldownMax = cooldown;
// }

// // ===== RENDERING =====

// /**
//  * @brief Draw player
//  */
// void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//     sf::Sprite sprite(texture);

//     // Set texture rect for player in atlas - TODO: Adjust to match your atlas
//     sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));  // Player position in atlas

//     sf::Vector2f pixelPos = grid->gridToCenterPixel(gridX, gridY);
//     sprite.setPosition(pixelPos);

//     // Center sprite on cell
//     sprite.setOrigin(16, 16);  // 32x32 / 2 = 16

//     target.draw(sprite, states);
// }

// // ===== UPDATE =====

// /**
//  * @brief Update player state
//  */
// void Player::update(float dt) {
//     // Update shoot cooldown
//     if (shootCooldown > 0.0f) {
//         shootCooldown -= dt;
//         if (shootCooldown < 0.0f) {
//             shootCooldown = 0.0f;
//         }
//     }
// }

// // ===== DEBUG =====

// /**
//  * @brief Debug print
//  */
// void Player::debugPrint() const {
//     std::cout << "\n[Player] Debug Info:" << std::endl;
//     std::cout << "  Position: (" << gridX << ", " << gridY << ")" << std::endl;
//     std::cout << "  Start: (" << startGridX << ", " << startGridY << ")" << std::endl;
//     std::cout << "  Can Shoot: " << (canShoot() ? "Yes" : "No") << std::endl;
//     std::cout << "  Cooldown: " << shootCooldown << "s" << std::endl;
//     std::cout << std::endl;
// }

// // ===== PRIVATE =====

// /**
//  * @brief Try to move to new position
//  *
//  * Checks bounds and collisions before moving.
//  */
// bool Player::tryMove(int newX, int newY) {
//     // Check bounds
//     if (!grid->isInBounds(newX, newY)) {
//         return false;
//     }

//     // Check for collision (can't move through mushrooms or centipede)
//     if (grid->isOccupied(newX, newY, MUSHROOM | CENTIPEDE)) {
//         return false;
//     }

//     // Movement is valid
//     clearFromGrid();

//     gridX = newX;
//     gridY = newY;

//     updateGridOccupancy();

//     return true;
// }

// /**
//  * @brief Update grid occupancy
//  */
// void Player::updateGridOccupancy() {
//     grid->setOccupied(gridX, gridY, PLAYER);
// }

// /**
//  * @brief Clear from grid
//  */
// void Player::clearFromGrid() {
//     grid->clearOccupied(gridX, gridY, PLAYER);
// }