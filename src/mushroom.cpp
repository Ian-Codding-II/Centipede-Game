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

/**
 * @brief Construct a new Mushroom:: Mushroom object
 * 
 */
Mushroom::Mushroom() : Mushroom(sf::Vector2f(0, 0), MAXHEALTH) {
    
}

/**
 * @brief Construct a new Mushroom:: Mushroom object w/ float vector2
 * 
 * @param pos Vector2f position
 */
Mushroom::Mushroom(sf::Vector2f pos) : Mushroom(pos, MAXHEALTH) {

}

/**
 * @brief Construct a new Mushroom:: Mushroom object w/ coords
 * 
 * @param x X coordinate
 * @param y Y coordinate
 */
Mushroom::Mushroom(float x, float y) : Mushroom(sf::Vector2f(x,y), MAXHEALTH) {

}

/**
 * @brief Construct a new Mushroom:: Mushroom object w/ health
 * 
 * @param hp 0 < hp <= 4 Number of hitpoints/health
 */
Mushroom::Mushroom(int hp) : Mushroom(sf::Vector2f(0,0), hp) {

}

/**
 * @brief Construct a new Mushroom:: Mushroom object w/ coords and health
 * 
 * @param x     X coordinate
 * @param y     Y coordinate
 * @param hp    0 < hp <= 4 Number of hitpoints/health
 */
Mushroom::Mushroom(float x, float y, int hp) : Mushroom(sf::Vector2f(x, y), hp) {
    
}

/**
 * @brief Construct a new Mushroom:: Mushroom object w/ float vector2 and health
 * 
 * @param pos   Vector2f position
 * @param hp    0 < hp <= 4 Number of hitpoints/health
 */
Mushroom::Mushroom(sf::Vector2f pos, int hp) {
    if (!mTexture.loadFromFile("../assets/temp/Normal_mushroom1.png")) {
        cerr << "Cannot load mushroom texture\n";
        exit(1);
    }

    mBlock.setTexture(mTexture);
    sf::Vector2u imageSize = mTexture.getSize();
    mBlock.setOrigin(imageSize.x/2, imageSize.y/2);

    if (hp <= 0)
        mHealth = 1;
    else if (hp > MAXHEALTH)
        mHealth = MAXHEALTH;

    mPosition = pos;
    setPos(mPosition);
    
}

void Mushroom::setPos(sf::Vector2f pos) {
    
}

void Mushroom::setPos(int x, int y) {
    
}

