/**
 * @file    animated_object.h
 * @author  Balin Becker
 * @brief   Collision Object but with animated sprites
 * @date    2025-11-24
 */

#ifndef ANIMATED_OBJECT_H
#define ANIMATED_OBJECT_H

#include "collision_object.h"

class anim_obj : public c_obj {
public:
    anim_obj(sf::Texture& texture, sf::IntRect StartFrame, int frames);
    void update(float deltaTime);
private:
    sf::Vector2i mPos;
    sf::Vector2i mSize;
    int mFrames, frameCount = 0;

    const float fps = 0.15;
    float totalElapsed = 0.0;
};

#endif