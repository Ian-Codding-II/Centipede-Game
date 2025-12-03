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
Mushroom::Mushroom(sf::Texture &texture, sf::IntRect spriteTexture, sf::Vector2f pos, int hp, bool isSuper)
    : c_obj(texture, spriteTexture, pos, "Mushroom") {

    if (isSuper) {
        mShroomState = super;
    } else {
        mShroomState = normal;
    }

    if (hp <= 0)
        mHealth = 1;
    else if (hp >= MAXHEALTH)
        mHealth = MAXHEALTH;

    updateTexture();
    mSprite.setScale(2, 2);
}

/**
 * @brief Damages mushroom for percentage
 *
 * @param dmg Percentage of hit points
 */
void Mushroom::hit(float dmg) {
    int hp = mHealth * dmg;
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

    updateTexture();
}

/**
 * @brief Updates the texture on the mushroom
 *
 */
void Mushroom::updateTexture() {
    // if (mHealth == 0 or mShroomState == destroy) {
    //     // Destroy
    // }

    switch (mShroomState) {
    case normal:
        if (mHealth > (MAXHEALTH * 0.75)) { // If > 75%
            // Full Mushroom
            setSpriteRect(sf::IntRect(8 * 8, 8 * 2, 8, 8));
        } else if (mHealth > (MAXHEALTH * 0.5) and mHealth <= (MAXHEALTH * 0.75)) { // If  > 50% and < 75%
            // Hit Mushroom
            setSpriteRect(sf::IntRect(8 * 9, 8 * 2, 8, 8));
        } else if (mHealth > (MAXHEALTH * 0.25) and mHealth <= (MAXHEALTH * 0.5)) { // If > 25% and < 50%
            // Damaged Mushroom
            setSpriteRect(sf::IntRect(8 * 10, 8 * 2, 8, 8));
        } else if (mHealth > 0 and mHealth <= (MAXHEALTH * 0.25)) { // If > 0 and < 25%
            // Broken Mushroom
            setSpriteRect(sf::IntRect(8 * 11, 8 * 2, 8, 8));
        }

        break;

    case super:
        if (mHealth > (MAXHEALTH * 0.75)) { // If > 75%
            // Full Mushroom
            setSpriteRect(sf::IntRect(8 * 8, 8 * 3, 8, 8));
        } else if (mHealth > (MAXHEALTH * 0.5) and mHealth < (MAXHEALTH * 0.75)) { // If > 50% and < 75%
            // Hit Mushroom
            setSpriteRect(sf::IntRect(8 * 9, 8 * 3, 8, 8));
        } else if (mHealth > (MAXHEALTH * 0.25) and mHealth < (MAXHEALTH * 0.5)) { // If > 25% and < 50%
            // Damaged Mushroom
            setSpriteRect(sf::IntRect(8 * 10, 8 * 3, 8, 8));
        } else if (mHealth > 0 and mHealth < (MAXHEALTH * 0.25)) { // If > 0 and < 25%
            // Broken Mushroom
            setSpriteRect(sf::IntRect(8 * 11, 8 * 3, 8, 8));
        }

        break;
    }
}

/**
 * @brief
 *
 * @param e
 * @param window
 */
void Mushroom::update() {
    updateTexture();
}

/**
 * @brief tells me if you died
 * 
 * @return true 
 * @return false 
 */
bool Mushroom::isDestroyed() const
{
    return mHealth <= 0;
}