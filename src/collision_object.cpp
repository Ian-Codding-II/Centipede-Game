/**
 * @file    collision_object.cpp
 * @author  Balin Becker
 * @brief   collision object class definitions
 * @date    2025-11-24
 */

#include "../includes/collision_object.h"

std::vector<c_obj*> c_obj::objects;

/**
 * @brief Construct a new c_obj object
 */
c_obj::c_obj(sf::Texture& texture, sf::IntRect spriteTexture, sf::Vector2i pos) {
    mSprite.setTexture(texture);
    mTexture = &texture;

    sf::Vector2u imageSize(spriteTexture.height, spriteTexture.width);
    mSprite.setOrigin(imageSize.x/2, imageSize.y/2);
    mSprite.setTextureRect(spriteTexture);

    mSprite.setPosition(pos.x, pos.y);

    objects.push_back(this);
}

/**
 * @brief Gets an array of colliding sprites
 * 
 * @return sf::Sprite* Array of sprites inside bounds
 */
std::vector<c_obj*> c_obj::getCollided() {
    std::vector<c_obj*> collisions;
    sf::FloatRect targetRegion = mSprite.getGlobalBounds();
    for (c_obj* obj: objects) {
        sf::FloatRect compareRegion = obj->mSprite.getGlobalBounds();
        if (targetRegion.intersects(compareRegion)) {
            collisions.push_back(obj);
        }
    }

    return collisions;
}

/**
 * @brief Sets sprite position
 * 
 * @param pos Vector2i (x,y)
 */
void c_obj::setPosition(sf::Vector2i pos) {
    mSprite.setPosition(pos.x, pos.y);
}

/**
 * @brief Sets sprite's TextureRect
 * 
 * @param spriteTexture IntRect (Horizontal, Vertical, Height, Width)
 */
void c_obj::setSpriteRect(sf::IntRect spriteTexture) {
    mSprite.setTextureRect(spriteTexture);
}

/**
 * @brief Sets sprite scale
 */
void c_obj::setScale(sf::Vector2i factor) {
    mSprite.setScale(sf::Vector2f(factor.x, factor.y));
}

/**
 * @brief 
 * 
 * @param target 
 * @param states 
 */
void c_obj::draw(sf::RenderTarget& target,sf::RenderStates states) const {
    target.draw(mSprite, states);
}



// /**
//  * @file collision_object.cpp
//  * @author Balin Becker, Ian Codding II
//  * @brief Implementation of collision object class
//  * @version 2.0
//  * @date 2025-11-26
//  *
//  * @copyright Copyright (c) 2025
//  */

// #include "../includes/collision_object.h"
// #include <iostream>

// /**
//  * @brief Constructor with full parameters
//  */
// c_obj::c_obj(sf::Texture& texture, sf::IntRect spriteTexture, sf::Vector2i pos)
//     : mTexture(texture), mPosition(pos) {

//     mSprite.setTexture(texture);
//     mSprite.setTextureRect(spriteTexture);

//     // Set origin to center for rotation/scaling if needed
//     float originX = spriteTexture.width / 2.0f;
//     float originY = spriteTexture.height / 2.0f;
//     mSprite.setOrigin(originX, originY);

//     std::cout << "[c_obj] Created at (" << pos.x << ", " << pos.y << ")" << std::endl;
// }

// /**
//  * @brief Simple constructor
//  */
// c_obj::c_obj(sf::Texture& texture)
//     : mTexture(texture), mPosition(0, 0) {

//     mSprite.setTexture(texture);

//     std::cout << "[c_obj] Created (simple constructor)" << std::endl;
// }

// // ===== POSITION =====

// /**
//  * @brief Set position
//  */
// void c_obj::setPosition(sf::Vector2i pos) {
//     mPosition = pos;
// }

// // ===== SPRITE/TEXTURE =====

// /**
//  * @brief Set texture rect
//  */
// void c_obj::setSpriteRect(sf::IntRect spriteTexture) {
//     mSprite.setTextureRect(spriteTexture);

//     // Recalculate origin based on new rect
//     float originX = spriteTexture.width / 2.0f;
//     float originY = spriteTexture.height / 2.0f;
//     mSprite.setOrigin(originX, originY);
// }

// // ===== COLLISION =====

// /**
//  * @brief Get global bounds
//  */
// sf::FloatRect c_obj::getGlobalBounds() const {
//     return mSprite.getGlobalBounds();
// }

// /**
//  * @brief Check collision with another object
//  */
// bool c_obj::collidesWith(const c_obj& other) const {
//     return getGlobalBounds().intersects(other.getGlobalBounds());
// }

// // ===== RENDERING =====

// /**
//  * @brief Draw the sprite
//  */
// void c_obj::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//     target.draw(mSprite, states);
// }