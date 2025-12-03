// /**
//  * @file mushroom.cpp
//  * @author Ian Codding II, Balin Becker
//  * @brief Implementation of Mushroom class
//  * @version 1.0 - Grid-Based
//  * @date 2025-11-26
//  *
//  * @copyright Copyright (c) 2025
//  */

// #include "../includes/mushroom.h"
// #include <iostream>

// /**
//  * @brief Constructor - create a mushroom
//  *
//  * @param grid Pointer to GameGrid
//  * @param texture Reference to mushroom sprite texture
//  * @param gridX Grid X position
//  * @param gridY Grid Y position
//  * @param health Initial health
//  * @param state Mushroom type (NORMAL or SUPER)
//  */
// Mushroom::Mushroom(GameGrid* grid, sf::Texture& texture, int gridX, int gridY, int health, MushroomState state)
//     : grid(grid),
//       texture(texture),
//       gridX(gridX),
//       gridY(gridY),
//       health(health),
//       state(state) {

//     // Clamp health to valid range
//     if (this->health > MAX_HEALTH) {
//         this->health = MAX_HEALTH;
//     }
//     if (this->health < 1) {
//         this->health = 1;
//     }

//     std::string stateStr = (state == NORMAL) ? "NORMAL" : (state == SUPER) ? "SUPER" : "DESTROYED";
//     std::cout << "[Mushroom] Created at (" << gridX << ", " << gridY 
//               << ") with health " << this->health << " - State: " << stateStr << std::endl;

//     // Mark on grid
//     updateGridOccupancy();
// }

// /**
//  * @brief Destructor
//  */
// Mushroom::~Mushroom() {
//     std::cout << "[Mushroom] Destroyed at (" << gridX << ", " << gridY << ")" << std::endl;
//     clearFromGrid();
// }

// // ===== HEALTH =====

// /**
//  * @brief Take damage
//  *
//  * Reduces health and checks if destroyed.
//  * Sets state to DESTROYED when health reaches 0.
//  *
//  * @return true if now destroyed
//  */
// bool Mushroom::takeDamage() {
//     if (health > 0) {
//         health--;
//         std::cout << "[Mushroom] Damaged! Health now: " << health << std::endl;

//         if (health <= 0) {
//             state = DESTROYED;
//             clearFromGrid();
//             return true;  // Destroyed
//         }
//     }

//     return false;
// }

// /**
//  * @brief Regenerate health
//  *
//  * Increases health up to MAX_HEALTH.
//  *
//  * @return true if regeneration occurred
//  */
// bool Mushroom::regenerate() {
//     if (health < MAX_HEALTH) {
//         health++;
//         std::cout << "[Mushroom] Regenerated! Health now: " << health << std::endl;
//         return true;
//     }

//     return false;
// }
// /**
//  * @brief Update mushroom state
//  *
//  * Currently just a placeholder for future effects.
//  *
//  * @param dt Delta time since last frame
//  */
// void Mushroom::update(float dt) {
//     // Placeholder for future effects
// }

// /**
//  * @brief Get grid position
//  */
// std::pair<int, int> Mushroom::getPosition() const {
//     return std::make_pair(gridX, gridY);
// }

// /**
//  * @brief Get collision bounds
//  */
// sf::FloatRect Mushroom::getGlobalBounds() const {
//     float pixelX = grid->gridToPixelX(gridX);
//     float pixelY = grid->gridToPixelY(gridY);

//     return sf::FloatRect(pixelX, pixelY, GameGrid::CELL_SIZE, GameGrid::CELL_SIZE);
// }

// // ===== RENDERING =====

// /**
//  * @brief Draw mushroom
//  *
//  * Visual appearance changes based on health using different frame offsets in the atlas.
//  * Assumes texture atlas has 4 horizontal frames (health 1-4 from left to right).
//  */
// void Mushroom::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//     if (health <= 0) {
//         return;  // Don't draw destroyed mushrooms
//     }

//     sf::Sprite sprite(texture);

//     // Calculate which frame to display based on health
//     // Health 1 = frame 0, Health 2 = frame 1, Health 3 = frame 2, Health 4 = frame 3
//     int frameIndex = health - 1;

//     // Assuming mushroom sprites are 32x32 and arranged horizontally in atlas
//     // TODO: Adjust Y coordinate to match your atlas position for mushrooms
//     sf::IntRect textureRect(
//         frameIndex * 32, 64,  // X = frame * 32, Y = 64 (mushroom row in atlas)
//         32, 32                // Width = 32, Height = 32
//     );

//     sprite.setTextureRect(textureRect);

//     // Position at grid cell center
//     sf::Vector2f pixelPos = grid->gridToCenterPixel(gridX, gridY);
//     sprite.setPosition(pixelPos);

//     // Center sprite on cell
//     sprite.setOrigin(16, 16);  // 32x32 / 2 = 16

//     target.draw(sprite, states);
// }

// // ===== PRIVATE =====

// /**
//  * @brief Update grid occupancy
//  */
// void Mushroom::updateGridOccupancy() {
//     if (health > 0) {
//         grid->setOccupied(gridX, gridY, MUSHROOM);
//     }
// }

// /**
//  * @brief Clear from grid
//  */
// void Mushroom::clearFromGrid() {
//     grid->clearOccupied(gridX, gridY, MUSHROOM);
// }

// ================ Mushroom from Balin to incorperate with my grid =================

/**
 * @file    mushroom.cpp
 * @author  Ian Codding II, Balin Becker
 * @brief   Mushroom Class Definitions
 * @date    2025-10-21
 */

#include "../includes/mushroom.h"
#include <iostream>
using std::cerr;
using std::endl;

const int MAXHEALTH = 4;

/**
 * @brief Construct a new Mushroom:: Mushroom object w/ float vector2 and health
 * 
 * @param pos   Vector2f position
 * @param hp    0 < hp <= 4 Number of hitpoints/health
 */
Mushroom::Mushroom(sf::Texture& texture, sf::IntRect spriteTexture, sf::Vector2f pos, int hp, bool isSuper) : c_obj(texture, spriteTexture, pos) {

    if (isSuper) {
        mShroomState = super;
    } else {
        mShroomState = normal;
    }
    
    if (hp <= 0)
        mHealth = 1;
    else if (hp >= MAXHEALTH)
        mHealth = MAXHEALTH;
    
    updateTexture();
    
}

/**
 * @brief Damages mushroom for percentage
 * 
 * @param dmg Percentage of hit points
 */
void Mushroom::hit(float dmg) {
    int hp = mHealth*dmg;
    hit(hp);
}

/**
 * @brief Damages muchroom for int points
 * 
 * @param dmg Number of hit points
 */
void Mushroom::hit(int dmg) {
    if (dmg >= mHealth) {
        mHealth -= mHealth;
    } else if (dmg <= 0) {
        mHealth -= 0;
    } else {
        mHealth -= dmg;
    }

    updateTexture();
}

/**
 * @brief Updates the texture on the mushroom
 * 
 */
void Mushroom::updateTexture() {
    // if (mHealth == 0 or mShroomState == destroy) {
    //     // Destroy
    // }

    switch (mShroomState) {
        case normal:
            if (mHealth > (MAXHEALTH * 0.75)) { // If > 75%
                // Full Mushroom
                setSpriteRect(sf::IntRect(8*8, 8*2, 8, 8));
            } else if (mHealth > (MAXHEALTH * 0.5) and mHealth <= (MAXHEALTH * 0.75)) { // If  > 50% and < 75%
                // Hit Mushroom
                setSpriteRect(sf::IntRect(8*9, 8*2, 8, 8));
            } else if (mHealth > (MAXHEALTH * 0.25) and mHealth <= (MAXHEALTH * 0.5)) { // If > 25% and < 50%
                // Damaged Mushroom
                setSpriteRect(sf::IntRect(8*10, 8*2, 8, 8));
            } else if (mHealth > 0 and mHealth <= (MAXHEALTH * 0.25)) { // If > 0 and < 25%
                // Broken Mushroom
                setSpriteRect(sf::IntRect(8*11, 8*2, 8, 8));
            }

            break;

        case super:
            if (mHealth > (MAXHEALTH * 0.75)) { // If > 75%
                // Full Mushroom
                setSpriteRect(sf::IntRect(8*8, 8*3, 8, 8));
            } else if (mHealth > (MAXHEALTH * 0.5) and mHealth < (MAXHEALTH * 0.75)) { // If > 50% and < 75%
                // Hit Mushroom
                setSpriteRect(sf::IntRect(8*9, 8*3, 8, 8));
            } else if (mHealth > (MAXHEALTH * 0.25) and mHealth < (MAXHEALTH * 0.5)) { // If > 25% and < 50%
                // Damaged Mushroom
                setSpriteRect(sf::IntRect(8*10, 8*3, 8, 8));
            } else if (mHealth > 0 and mHealth < (MAXHEALTH * 0.25)) { // If > 0 and < 25%
                // Broken Mushroom
                setSpriteRect(sf::IntRect(8*11, 8*3, 8, 8));
            }

            break;
    }
}


/**
 * @brief 
 * 
 * @param e 
 * @param window 
 */
void Mushroom::update() {
    updateTexture();
}
