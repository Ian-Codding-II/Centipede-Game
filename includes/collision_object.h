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