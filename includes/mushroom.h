/**
 * @file    mushroom.h
 * @author  Ian Codding II, Balin Becker
 * @brief   Mushroom Class
 * @date    2025-10-21
 */

// - Store position
// - Track health (0-4)
// - Change sprite based on health
// - Remove when health reaches 0

#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <SFML/Graphics.hpp>
#include "collision_object.h"

//int MaxX = 100, MaxY = 100, MinX = 100, MinY = 100;
extern const int MAXHEALTH;

enum state {normal, super, destroy};

class Mushroom : public c_obj{
    //Texture
    //Sprite
    //Position
    //Health
    //Draw
public:

    Mushroom(sf::Texture& texture, sf::IntRect spriteTexture = sf::IntRect(0, 0, 8, 8), sf::Vector2f pos = sf::Vector2f(0, 0), int hp = MAXHEALTH, bool isSuper = false);

    // Default destructor;
    ~Mushroom() {};

    void hit(float dmg);
    void hit(int dmg);

    void update();

private:
    void updateTexture();
    // void updateLvl();

    sf::Uint32 mShroomState;
    int mHealth; // When hp == 0, destroy
    
};

#endif

// /**
//  * @file mushroom.h
//  * @author Ian Codding II, Balin Becker
//  * @brief Mushroom class - static obstacles on the game board
//  * @version 1.0 - Grid-Based
//  * @date 2025-11-26
//  *
//  * @copyright Copyright (c) 2025
//  *
//  * MUSHROOM MECHANICS:
//  *
//  * Mushrooms are static obstacles that:
//  * - Block centipede movement (centipede bounces around them)
//  * - Block player movement
//  * - Can be destroyed by bullets (takes multiple hits)
//  * - Have health (1-4 hits to destroy)
//  * - Change appearance based on damage
//  *
//  * HEALTH STATES:
//  * - 4 health: Full mushroom
//  * - 3 health: Slightly damaged
//  * - 2 health: More damage visible
//  * - 1 health: Nearly destroyed
//  * - 0 health: Gone (removed from game)
//  *
//  * REGENERATION:
//  * - Optional: mushrooms can slowly regenerate health
//  * - Useful for endless gameplay
//  */

// #ifndef MUSHROOM_H
// #define MUSHROOM_H

// #include <SFML/Graphics.hpp>
// #include "GameGrid.h"

// /**
//  * @enum MushroomState
//  * @brief The type/state of the mushroom
//  */
// enum MushroomState {
//     NORMAL = 0,      // Regular mushroom - blocks centipede
//     SUPER = 1,       // Super mushroom - bonus points when destroyed
//     DESTROYED = 2    // Destroyed - no longer exists
// };

// /**
//  * @class Mushroom
//  * @brief Static obstacle - blocks movement and bullets
//  *
//  * Responsibilities:
//  * - Store position and health
//  * - Change appearance based on health
//  * - Handle bullet collisions
//  * - Remove self when destroyed
//  */
// class Mushroom : public sf::Drawable {
// public:
//     // Maximum health a mushroom can have
//     static const int MAX_HEALTH = 4;

//     /**
//      * @brief Constructor - create a mushroom
//      *
//      * @param grid Pointer to GameGrid
//      * @param texture Reference to mushroom sprite texture
//      * @param gridX Grid X position
//      * @param gridY Grid Y position
//      * @param health Initial health (default 4 = full)
//      * @param state Mushroom type (NORMAL or SUPER)
//      */
//     Mushroom(GameGrid* grid, sf::Texture& texture, int gridX, int gridY, int health = MAX_HEALTH, MushroomState state = NORMAL);

//     /**
//      * @brief Destructor
//      */
//     ~Mushroom();

//     // ===== HEALTH =====

//     /**
//      * @brief Take damage
//      *
//      * Reduces health by 1 and updates appearance.
//      * Automatically marks as destroyed if health reaches 0.
//      *
//      * @return true if mushroom is destroyed (health <= 0)
//      */
//     bool takeDamage();

//     /**
//      * @brief Get current health
//      *
//      * @return Health value (0-4)
//      */
//     int getHealth() const { return health; }

//     /**
//      * @brief Check if mushroom is destroyed
//      *
//      * @return true if health <= 0
//      */
//     bool isDestroyed() const { return health <= 0; }

//     /**
//      * @brief Get mushroom state
//      *
//      * @return Current MushroomState (NORMAL, SUPER, or DESTROYED)
//      */
//     MushroomState getState() const { return state; }

//     /**
//      * @brief Regenerate health
//      *
//      * Increases health by 1 (up to MAX_HEALTH).
//      * Useful for endless mode.
//      *
//      * @return true if regeneration occurred
//      */
//     bool regenerate();

//     // ===== POSITION & COLLISION =====

//     /**
//      * @brief Get grid position
//      *
//      * @return Pair of (gridX, gridY)
//      */
//     std::pair<int, int> getPosition() const;

//     /**
//      * @brief Get collision bounds
//      *
//      * @return FloatRect in pixel coordinates
//      */
//     sf::FloatRect getGlobalBounds() const;

//     // ===== RENDERING =====

//     /**
//      * @brief Draw mushroom
//      *
//      * Inherited from sf::Drawable.
//      * Visual appearance changes based on health.
//      *
//      * @param target Render target
//      * @param states Render states
//      */
//     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

//     // ===== UPDATE =====

//     /**
//      * @brief Update mushroom state
//      *
//      * Handles regeneration and other time-based effects.
//      *
//      * @param dt Delta time since last frame
//      */
//     void update(float dt);

// private:
//     // Grid reference
//     GameGrid* grid;

//     // Texture
//     sf::Texture& texture;

//     // Position
//     int gridX;
//     int gridY;

//     // Health
//     int health;

//     // State (NORMAL, SUPER, or DESTROYED)
//     MushroomState state;

//     // Regeneration timer (optional)
//     float regenTimer;
//     const float REGEN_DELAY = 5.0f;  // Regenerate every 5 seconds

//     /**
//      * @brief Update grid occupancy
//      *
//      * Marks mushroom's cell as occupied on the grid.
//      */
//     void updateGridOccupancy();

//     /**
//      * @brief Clear from grid
//      *
//      * Removes mushroom from grid when destroyed.
//      */
//     void clearFromGrid();
// };

// #endif // MUSHROOM_H