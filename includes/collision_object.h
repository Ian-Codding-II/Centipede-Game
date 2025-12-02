/**
 * @file    collision_object.h
 * @author  Balin Becker
 * @brief   Basic collision object class
 * @date    2025-11-24
 */

#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

/**
 * @class c_obj
 * @brief Base collision object
 *
 * General purpose collision object that can be used for custom entities.
 * Most game objects (Player, Centipede, etc.) have their own implementations.
 *
 * This class provides:
 * - Position management
 * - Sprite handling
 * - Bounds for collision detection
 */
class c_obj : public sf::Drawable {
    public:
        c_obj(sf::Texture& texture):c_obj(texture, sf::IntRect(0, 0, 0, 0), sf::Vector2i(0, 0)) {}
        c_obj(sf::Texture& texture, sf::IntRect spriteTexture, sf::Vector2i pos);

        std::vector<c_obj*> getCollided();

        void setPosition(sf::Vector2i pos);
        void setSpriteRect(sf::IntRect spriteTexture);
        void setScale(sf::Vector2i factor);

        sf::Sprite getSprite() const {return mSprite;};
        sf::Vector2i getPosition() const {return mPosition;};

        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

    protected:
        sf::Sprite mSprite;
        sf::Texture* mTexture;
        sf::Vector2i mPosition;

    private:
        static std::vector<c_obj*> objects;
};

#endif

// /**
//  * @file collision_object.h
//  * @author Balin Becker, Ian Codding II
//  * @brief Basic collision object class - Grid-based version
//  * @version 2.0
//  * @date 2025-11-26
//  *
//  * @copyright Copyright (c) 2025
//  *
//  * NOTE: This is a general collision base class.
//  * For actual game objects, use the specialized classes:
//  * - Player (player.h)
//  * - Centipede (Centipede.h)
//  * - Mushroom (mushroom.h)
//  * - Bullet (bullet.h)
//  *
//  * Those classes integrate directly with the grid system
//  * and CollisionManager for better performance.
//  */

// #ifndef COLLISION_OBJECT_H
// #define COLLISION_OBJECT_H

// #include <SFML/Graphics.hpp>
// #include "GameGrid.h"
// #include <vector>

// /**
//  * @class c_obj
//  * @brief Base collision object
//  *
//  * General purpose collision object that can be used for custom entities.
//  * Most game objects (Player, Centipede, etc.) have their own implementations.
//  *
//  * This class provides:
//  * - Position management
//  * - Sprite handling
//  * - Bounds for collision detection
//  */
// class c_obj : public sf::Drawable {
// public:
//     /**
//      * @brief Constructor with position and texture
//      *
//      * @param texture Reference to sprite texture
//      * @param spriteTexture Which part of texture to use (IntRect)
//      * @param pos Grid position (x, y)
//      */
//     c_obj(sf::Texture& texture, sf::IntRect spriteTexture, sf::Vector2i pos);

//     /**
//      * @brief Simple constructor
//      *
//      * @param texture Reference to sprite texture
//      */
//     c_obj(sf::Texture& texture);

//     /**
//      * @brief Virtual destructor for polymorphism
//      */
//     virtual ~c_obj() = default;

//     // ===== POSITION =====

//     /**
//      * @brief Set object position
//      *
//      * @param pos Grid position (x, y)
//      */
//     void setPosition(sf::Vector2i pos);

//     /**
//      * @brief Get object position
//      *
//      * @return Grid position as sf::Vector2i
//      */
//     sf::Vector2i getPosition() const { return mPosition; }

//     // ===== SPRITE/TEXTURE =====

//     /**
//      * @brief Set which part of texture to display
//      *
//      * Useful for spritesheets with multiple frames.
//      *
//      * @param spriteTexture IntRect defining texture region
//      */
//     void setSpriteRect(sf::IntRect spriteTexture);

//     /**
//      * @brief Get the sprite
//      *
//      * @return Reference to sprite
//      */
//     sf::Sprite getSprite() const { return mSprite; }

//     // ===== COLLISION =====

//     /**
//      * @brief Get collision bounds
//      *
//      * @return Global bounds of sprite (pixel coordinates)
//      */
//     sf::FloatRect getGlobalBounds() const;

//     /**
//      * @brief Check if this object collides with another
//      *
//      * Simple AABB collision check.
//      *
//      * @param other Other object to check against
//      * @return true if bounding boxes overlap
//      */
//     bool collidesWith(const c_obj& other) const;

//     // ===== RENDERING =====

//     /**
//      * @brief Draw the object
//      *
//      * Inherited from sf::Drawable.
//      *
//      * @param target Render target
//      * @param states Render states
//      */
//     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

// protected:
//     sf::Sprite mSprite;           // Visual representation
//     sf::Texture& mTexture;        // Reference to texture
//     sf::Vector2i mPosition;       // Position (grid coordinates)
// };

// #endif // COLLISION_OBJECT_H