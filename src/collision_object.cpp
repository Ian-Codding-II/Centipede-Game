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
c_obj::c_obj(sf::Texture& texture, sf::IntRect spriteTexture, sf::Vector2f pos, std::string name) {
    mSprite.setTexture(texture);
    mTexture = &texture;
    mName = name;

    sf::Vector2u imageSize(spriteTexture.height, spriteTexture.width);
    mSprite.setOrigin(imageSize.x/2, imageSize.y/2);
    mSprite.setTextureRect(spriteTexture);

    mSprite.setPosition(pos.x, pos.y);
    mPosition = pos;

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
void c_obj::setPosition(sf::Vector2f pos) {
    mSprite.setPosition(pos.x, pos.y);
    mPosition = pos;
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
