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

//int MaxX = 100, MaxY = 100, MinX = 100, MinY = 100;
extern const int MAXHEALTH;

class Mushroom : public sf::Drawable{
    //Texture
    //Sprite
    //Position
    //Health
    //Draw
public:

    Mushroom(sf::Vector2f pos, int hp);

    // Default constructor
    Mushroom() : Mushroom(sf::Vector2f(0, 0), MAXHEALTH) {}
    // Constructor w/ float vect2
    Mushroom(sf::Vector2f pos) : Mushroom(pos, MAXHEALTH) {}
    // Constructor w/ coords
    Mushroom(float x, float y) : Mushroom(sf::Vector2f(x,y), MAXHEALTH) {}
    // Constructor w/ hp
    Mushroom(int hp) : Mushroom(sf::Vector2f(0,0), hp) {}
    // Constructor w/ coords & hp
    Mushroom(float x, float y, int hp) : Mushroom(sf::Vector2f(x, y), hp) {}

    // Default destructor;
    ~Mushroom() {};

    void setPos(sf::Vector2f pos);
    void setPos(int x, int y);

    void hit(float dmg);
    void hit(int dmg);

    sf::Vector2f getPos() const {return mPosition;}
    sf::Texture getTexture() const {return mAtlas;}
    sf::Sprite getSprite() const {return mBlock;}

    void update(sf::Event& e, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

private:
    void updateTexture();
    // void updateLvl();

    sf::Sprite mBlock;
    sf::Texture mAtlas; // PROBABLY TEMPORARY
    sf::Vector2f mPosition;
    int mHealth; // When hp == 0, destroy
    bool mSuper; // If super, change texture
    int lvl;
    
};

#endif