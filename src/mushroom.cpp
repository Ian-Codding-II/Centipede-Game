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
 * @brief Construct a new Mushroom:: Mushroom object w/ float vector2 and health
 * 
 * @param pos   Vector2f position
 * @param hp    0 < hp <= 4 Number of hitpoints/health
 */
Mushroom::Mushroom(sf::Vector2f pos, int hp) {
    //** REMOVE LATER **//
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

/**
 * @brief Sets mushroom position w/ float Vector2
 * 
 * @param pos Vector2 position
 */
void Mushroom::setPos(sf::Vector2f pos) {
    mPosition = pos;
    // Update position
}

/**
 * @brief Sets mushroom positions w/ coords
 * 
 * @param x X coordinate
 * @param y Y coordinate
 */
void Mushroom::setPos(int x, int y) {
    sf::Vector2f pos(x, y);
    setPos(pos);
}