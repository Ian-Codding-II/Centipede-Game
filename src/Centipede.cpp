/**
 * @file    Centipede.cpp
 * @author  Balin Becker
 * @brief   Centipede class definitions
 * @date    2025-10-21
 */

#include "../includes/Centipede.h"

VertDirection vertState = VertDirection::down;
HoriDirection horiState = HoriDirection::right;

Centipede::Centipede(sf::Texture& Texture, int length, sf::Vector2f position, sf::Vector2i factor) {
    mLength = length;
    mSpacing = 15;
    mPosition = position;
    mTexture = Texture;
    
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            // Create a head
            anim_obj* headSeg = new anim_obj(Texture, sf::IntRect(0, 8*1, 8, 8), 4, "CentipedeHead");
            segment* head = new segment(headSeg, "Head");
            head->mSprite->setScale(factor);
            head->mSprite->setPosition(mPosition);
            mCentipedeVect.push_back(head);
        } else {
            // Create a segment
            anim_obj* sSegment = new anim_obj(Texture, sf::IntRect(0, 8*0, 8, 8), 4, "CentipedeSegment");
            segment* seg = new segment(sSegment, "Segment");
            seg->mSprite->setScale(factor);
            seg->mSprite->setPosition(sf::Vector2f(mPosition.x - i * mSpacing, mPosition.y));
            mCentipedeVect.push_back(seg);
        }
    }
    
    vertState = VertDirection::down;
    horiState = HoriDirection::right;
}

/**
 * @brief Destroy the Centipede::Centipede object
 * 
 */
Centipede::~Centipede() {
    for (int i = 0; i < mLength; i++) {
        delete mCentipedeVect[i]->mSprite;
        delete mCentipedeVect[i];
    }
}

/**
 * @brief Places all centipede segments at position
=======
 
 * 
 * @param position Position to place at
 */
void Centipede::setPosition(sf::Vector2f position) {
    for (segment* seg : mCentipedeVect) {
        seg->mSprite->setPosition(position);
    }
}

/**
 * @brief Sets scale of Centipede
 * 
 * @param factor Factor to scale by
 */
void Centipede::setScale(sf::Vector2i factor) {
    for (segment* seg : mCentipedeVect) {
        seg->mSprite->setScale(factor);
    }
}

void Centipede::hit() {
    if (!mCentipedeVect.empty()) {
        delete mCentipedeVect.back()->mSprite;
        delete mCentipedeVect.back();
        mCentipedeVect.pop_back();
        mLength--; // update length!
    }
}

/**
 * @brief Moves the Centipede to the position
 * 
 * @param position Position to move to
 */
void Centipede::move(float dt, Grid grid) {
    elapsedTime += dt;

    if (elapsedTime >= speed) {
        elapsedTime -= speed;

        bool bumped = false;
        sf::FloatRect bounds = mCentipedeVect[0]->mSprite->getSprite().getGlobalBounds();
        sf::Vector2f hPos(bounds.left, bounds.top);
        sf::Vector2f hSize(bounds.width, bounds.height);

        int lookDir = 0;
        if (horiState == HoriDirection::left) {
            lookDir = -16;
        } else if (horiState == HoriDirection::right) {
            lookDir = 16;
        }

        // Checks collisions and grid bounds
        sf::FloatRect frontHitbox = sf::FloatRect(hPos.x + lookDir, hPos.y, hSize.x / 4, hSize.y);
        std::vector<c_obj*> collisions = mCentipedeVect[0]->mSprite->getCollided(frontHitbox);
        if (collisions.size() > 0) {
            for (long unsigned int i = 0; i < collisions.size(); i++) {
                if (collisions[i]->getName() == "Mushroom") {
                    bumped = true;
                    break;
                }
            }
        } else if (!frontHitbox.intersects(grid.GetRegion())) {
            bumped = true;
        }

        // Checks vertical limits
        if (hPos.y < ((grid.GetRegion().top) - (grid.GetRegion().height / 2))) {
            vertState = VertDirection::down;
        } else if (hPos.y > ((grid.GetRegion().top) + (grid.GetRegion().height / 2))) {
            vertState = VertDirection::up;
        }

        if (bumped) {
            
            if (vertState == VertDirection::down) {
                sf::Vector2f prevPos = sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y);
                mCentipedeVect[0]->mSprite->setPosition(sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y + 16));

                for (int i = 1; i < mLength; i++) {
                    sf::Vector2f currentPos = sf::Vector2f(mCentipedeVect[i]->mSprite->getPosition().x, mCentipedeVect[i]->mSprite->getPosition().y);
                    mCentipedeVect[i]->mSprite->setPosition(prevPos);
                    prevPos = currentPos;
                }
            
            } else if (vertState == VertDirection::up) {
                sf::Vector2f prevPos = sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y);
                mCentipedeVect[0]->mSprite->setPosition(sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y - 16));

                for (int i = 1; i < mLength; i++) {
                    sf::Vector2f currentPos = sf::Vector2f(mCentipedeVect[i]->mSprite->getPosition().x, mCentipedeVect[i]->mSprite->getPosition().y);
                    mCentipedeVect[i]->mSprite->setPosition(prevPos);
                    prevPos = currentPos;
                }

            }

            if (horiState == HoriDirection::left) {
                horiState = HoriDirection::right;
            } else {
                horiState = HoriDirection::left;
            }
        } else {
            if (horiState == HoriDirection::right) {
                sf::Vector2f prevPos = sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y);
                mCentipedeVect[0]->mSprite->setPosition(sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x + 16, mCentipedeVect[0]->mSprite->getPosition().y));

                for (int i = 1; i < mLength; i++) {
                    sf::Vector2f currentPos = sf::Vector2f(mCentipedeVect[i]->mSprite->getPosition().x, mCentipedeVect[i]->mSprite->getPosition().y);
                    mCentipedeVect[i]->mSprite->setPosition(prevPos);
                    prevPos = currentPos;
                }
            } else if (horiState == HoriDirection::left) {
                sf::Vector2f prevPos = sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x, mCentipedeVect[0]->mSprite->getPosition().y);
                mCentipedeVect[0]->mSprite->setPosition(sf::Vector2f(mCentipedeVect[0]->mSprite->getPosition().x - 16, mCentipedeVect[0]->mSprite->getPosition().y));

                for (int i = 1; i < mLength; i++) {
                    sf::Vector2f currentPos = sf::Vector2f(mCentipedeVect[i]->mSprite->getPosition().x, mCentipedeVect[i]->mSprite->getPosition().y);
                    mCentipedeVect[i]->mSprite->setPosition(prevPos);
                    prevPos = currentPos;
                }
            }
        }
    }
}

/**
 * @brief Causes Centipede to fall the ground
 */
void Centipede::fall() {

}

/**
 * @brief 
 * 
 */
void Centipede::update(float dt) {
    for (int i = 0; i < mLength; i++) {
        mCentipedeVect[i]->mSprite->update(dt);
    }
}

/**
 * @brief 
 * 
 * @param target 
 * @param states 
 */
void Centipede::draw(sf::RenderTarget& target,sf::RenderStates states) const {
    for (int i = 0; i < mLength; i++) {
        target.draw(mCentipedeVect[i]->mSprite->getSprite(), states);
    }
}
