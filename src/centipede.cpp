/**
 * @file    centipede.cpp
 * @author  Balin Becker
 * @brief   Centipede class definitions
 * @date    2025-10-21
 */

#include "../includes/centipede.h"

centipede::centipede(sf::Texture& Texture, int length, sf::Vector2f position, sf::Vector2i factor) {
    mPosition = position;
    for (int i = 0; i < length; i++) {
        if (i == length - 1) {
            // Create a head
            anim_obj headSeg(Texture, sf::IntRect(0, 8*1, 8, 8), 4);
            segment head(headSeg, "Head");
            head.mSprite->setScale(factor);
            head.mSprite->setPosition(mPosition);
            mCentipedeVect.push_back(head);
        } else {
            // Create a segment
            anim_obj sSegment(Texture, sf::IntRect(0, 0, 8, 8), 4);
            segment seg(sSegment, "Segment");
            seg.mSprite->setScale(factor);
            seg.mSprite->setPosition(mPosition);
            mCentipedeVect.push_back(seg);
        }
    }

}

/**
 * @brief Places all centipede segments at position
 * 
 * @param position Position to place at
 */
void centipede::setPosition(sf::Vector2f position) {
    for (segment seg : mCentipedeVect) {
        seg.mSprite->setPosition(position);
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
void centipede::move(sf::Vector2f position) {
    segment* Head = &mCentipedeVect.back();
    float distance = sqrt(pow(abs(position.x - mPosition.x), 2) - pow(abs(position.y - mPosition.y), 2));
    for (int i = 0; i < distance; i++) {

        if (Head->mSprite->getPosition() == position) {
            // Catch up rest of centipede
        }
    }
}

/**
 * @brief Causes centipede to fall the ground
 */
void centipede::fall() {

}
