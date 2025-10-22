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

int MAXHEALTH = 4;

class Mushroom : public sf::Drawable{
    //Texture
    //Sprite
    //Position
    //Health
    //Draw
public:
    Mushroom();
    Mushroom(sf::Vector2f pos);
    Mushroom(float x, float y);
    Mushroom(int hp);
    Mushroom(sf::Vector2f pos, int hp);
    Mushroom(float x, float y, int hp);


    ~Mushroom();

    bool setPos(sf::Vector2f pos);
    bool setPos(int x, int y);

    sf::Vector2f getPos() const {return mPosition;}
    sf::Texture getTexture() const {return mTexture;}
    sf::Sprite getSprite() const {return mBlock;}

    void update(sf::Event& e, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

private:
    sf::Sprite mBlock;
    sf::Texture mTexture; // Not setable, dependent on level and super status
    sf::Vector2f mPosition;
    int mHealth; // When hp == 0, destroy
    bool mSuper; // If super, change texture
};

#endif