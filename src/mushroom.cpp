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

const int MAXHEALTH = 4;

/**
 * @brief Construct a new Mushroom:: Mushroom object w/ float vector2 and health
 * 
 * @param pos   Vector2f position
 * @param hp    0 < hp <= 4 Number of hitpoints/health
 */
Mushroom::Mushroom(sf::Vector2f pos, int hp) {
    //** REMOVE LATER **//
    if (!mAtlas.loadFromFile("assets/temp/Normal_mushroom1.png")) {
        cerr << "Cannot load mushroom texture(s)\n";
        exit(1);
    }

    mBlock.setTexture(mAtlas);
    sf::Vector2u imageSize = mAtlas.getSize();
    mBlock.setOrigin(imageSize.x/2, imageSize.y/2);
    updateTexture();
    
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
    mBlock.setPosition(mPosition);
}

/**
 * @brief Sets mushroom positions w/ coords
 * 
 * @param x X coordinate
 * @param y Y coordinate
 */
void Mushroom::setPos(int x, int y) {
    // if (x > MaxX) {
    //     x = MaxX;
    // } else if (x < MinX) {
    //     x = MinX;
    // }

    // if (y > MaxY) {
    //     y = MaxY;
    // } else if (y < MinY) {
    //     y = MinY;
    // }
    
    sf::Vector2f pos(x, y);
    setPos(pos);
}

/**
 * @brief Damages mushroom for percentage
 * 
 * @param dmg Percentage of hit points
 */
void Mushroom::hit(float dmg) {
    int hp = mHealth*dmg;
    hit(hp);
}

/**
 * @brief Damages muchroom for int points
 * 
 * @param dmg Number of hit points
 */
void Mushroom::hit(int dmg) {
    if (dmg >= mHealth) {
        mHealth -= mHealth;
    } else if (dmg <= 0) {
        mHealth -= 0;
    } else {
        mHealth -= dmg;
    }
}

/**
 * @brief Updates the texture on the mushroom
 * 
 */
void Mushroom::updateTexture() {
    if (mHealth == 0) {
        // Destroy
    } else if (mHealth > MAXHEALTH * 0.75) { // If > 75%
        // Full Mushroom
        sf::IntRect Tex(1, 1, 1, 1);
        mBlock.setTextureRect(Tex);
    } else if (mHealth > MAXHEALTH * 0.5 and mHealth < MAXHEALTH * 0.75) { // If  > 50% and < 75%
        // Hit Mushroom
    } else if (mHealth > MAXHEALTH * 0.25 and mHealth < MAXHEALTH * 0.5) { // If > 25% and < 50%
        // Damaged Mushroom
    } else if (mHealth > 0 and mHealth < MAXHEALTH * 0.25) { // If > 0 and < 25%
        // Broken Mushroom
    }
}


/**
 * @brief 
 * 
 * @param e 
 * @param window 
 */
void Mushroom::update(sf::Event& e, sf::RenderWindow& window) {

}

/**
 * @brief 
 * 
 * @param target 
 * @param states 
 */
void Mushroom::draw(sf::RenderTarget& target,sf::RenderStates states) const {
    target.draw(mBlock, states);
}

