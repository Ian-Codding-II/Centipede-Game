/**
 * @file    centipede.cpp
 * @author  Balin Becker
 * @brief   Centipede class definitions
 * @date    2025-10-21
 */

#include "centipede.h"

centipede::centipede(sf::Texture& Texture, int length, sf::Vector2i factor) {
    for (int i = 0; i < length; i++) {
        if (i == length - 1) {
            // Create a head
            anim_obj headSeg(Texture, sf::IntRect(0, 8*1, 8, 8), 4);
            segment head(headSeg, "Head");
            head.mSprite->setScale(factor);
            mCentipedeVect.push_back(head);
        } else {
            // Create a segment
            anim_obj sSegment(Texture, sf::IntRect(0, 0, 8, 8), 4);
            segment seg(sSegment, "Segment");
            seg.mSprite->setScale(factor);
            mCentipedeVect.push_back(seg);
        }
    }
}

/**
 * @brief Sets scale of centipede
 * 
 * @param factor Factor to scale by
 */
void centipede::setScale(sf::Vector2i factor) {
    for (segment seg : mCentipedeVect) {
        seg.mSprite->setScale(factor);
    }
}

/**
 * @brief Moves the centipede to the position
 * 
 * @param position Position to move to
 */
void centipede::move(sf::Vector2i position) {
    // Move head toward position once
    // If segment behind is able to move, move
    // repeat until head is on position and all segments are in line
}

/**
 * @brief Causes centipede to fall the ground
 */
void centipede::fall() {

}
