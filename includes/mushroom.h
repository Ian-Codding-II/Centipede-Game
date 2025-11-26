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
#include "collision_object.h"

//int MaxX = 100, MaxY = 100, MinX = 100, MinY = 100;
extern const int MAXHEALTH;

enum state {normal, super, destroy};

class Mushroom : public c_obj{
    //Texture
    //Sprite
    //Position
    //Health
    //Draw
public:

    Mushroom(sf::Texture& texture, sf::IntRect spriteTexture = sf::IntRect(0, 0, 8, 8), sf::Vector2i pos = sf::Vector2i(0, 0), int hp = MAXHEALTH, bool isSuper = false);

    // Default destructor;
    ~Mushroom() {};

    void hit(float dmg);
    void hit(int dmg);

    void update();

private:
    void updateTexture();
    // void updateLvl();

    sf::Uint32 mShroomState;
    int mHealth; // When hp == 0, destroy
    
};

#endif