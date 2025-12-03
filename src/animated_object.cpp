/**
 * @file    animated_object.cpp
 * @author  Balin Becker
 * @brief   Animated Object class definition
 * @date    2025-11-24
 */

#include "../includes/animated_object.h"

anim_obj::anim_obj(sf::Texture& texture, sf::IntRect StartFrame, int frames, std::string name) : c_obj(texture, StartFrame, sf::Vector2f(0, 0), name) {
    mSize = sf::Vector2f(static_cast<float>(StartFrame.width), static_cast<float>(StartFrame.height));
    mPos  = sf::Vector2f(static_cast<float>(StartFrame.left),  static_cast<float>(StartFrame.top));
    mFrames = frames;

}

/**
 * @brief update sprite
 *          On function call, change to next frame
 */
void anim_obj::update(float deltaTime) {
    totalElapsed += deltaTime;

    if (totalElapsed >= fps) {
        totalElapsed -= fps;
        frameCount++;
        if (frameCount >= mFrames) {
            frameCount = 0;
        }

        setSpriteRect(sf::IntRect(mSize.x * frameCount, mPos.y, mSize.x, mSize.y));
    }
}

