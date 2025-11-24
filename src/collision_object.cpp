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
// std::vector<c_obj*> c_obj::getCollided() {
//     std::vector<c_obj*> collisions;
//     sf::FloatRect targetRegion = mSprite.getGlobalBounds();
//     for (c_obj* obj: objects) {
//         sf::FloatRect compareRegion = obj->mSprite.getGlobalBounds();
//         if (targetRegion.intersects(compareRegion)) {
//             collisions.push_back(obj);
//         }
//     }

//     return collisions;
// }

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


