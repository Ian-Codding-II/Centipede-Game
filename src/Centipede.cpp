/**
 * @file    Centipede.cpp
 * @author  Balin Becker
 * @brief   Centipede class definitions
 * @date    2025-10-21
 */

#include "../includes/Centipede.h"

Centipede::Centipede(sf::Texture& Texture, int length, sf::Vector2i factor) {
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
void Centipede::setScale(sf::Vector2i factor) {
    for (segment seg : mCentipedeVect) {
        seg.mSprite->setScale(factor);
    }
}

/**
 * @brief Moves the centipede to the position
 * 
 * @param position Position to move to
 */
void Centipede::move(sf::Vector2i position) {
    // Move head toward position once
    // If segment behind is able to move, move
    // repeat until head is on position and all segments are in line
}

/**
 * @brief Causes centipede to fall the ground
 */
void Centipede::fall() {

}



// /**
//  * @file Centipede.cpp
//  * @author Ian Codding II
//  * @brief Implementation of Centipede class
//  * @version 1.0
//  * @date 2025-11-26
//  *
//  * @copyright Copyright (c) 2025
//  */

// #include "../includes/Centipede.h"
// #include <cmath>

// /**
//  * @brief Constructor - create a new centipede
//  *
//  * Sets up the centipede with initial segments at the top of the screen.
//  * Each segment type (head, body, tail) can have a different texture.
//  *
//  * @param grid Pointer to GameGrid
//  * @param headTexture Reference to head texture
//  * @param bodyTexture Reference to body texture
//  * @param tailTexture Reference to tail texture
//  * @param length Number of segments
//  * @param startDirection Initial direction (left or right)
//  */
// Centipede::Centipede(GameGrid* grid, sf::Texture& headTexture, sf::Texture& bodyTexture,
//                      sf::Texture& tailTexture, int length, CentipedeDirection startDirection)
//     : grid(grid),
//       headTexture(headTexture),
//       bodyTexture(bodyTexture),
//       tailTexture(tailTexture),
//       direction(startDirection),
//       moveTimer(0.0f) {

//     std::cout << "[Centipede] Constructor called - length: " << length << std::endl;

//     // Create all segments
//     initializeSegments(length);

//     // Mark centipede on grid
//     updateGridOccupancy();

//     std::cout << "[Centipede] Centipede created successfully" << std::endl;
// }

// /**
//  * @brief Destructor
//  */
// Centipede::~Centipede() {
//     std::cout << "[Centipede] Destructor called" << std::endl;
//     clearFromGrid();
// }

// // ===== MOVEMENT =====

// /**
//  * @brief Update - move centipede each frame
//  *
//  * Uses a timer to move the centipede at intervals, creating smooth grid-based movement.
//  *
//  * @param dt Delta time since last frame
//  */
// void Centipede::update(float dt) {
//     if (segments.empty()) {
//         return;  // Dead centipede, don't move
//     }

//     // Accumulate time
//     moveTimer += dt;

//     // Move when enough time has passed
//     if (moveTimer >= MOVE_DELAY) {
//         moveTimer = 0.0f;

//         // Try to move forward
//         if (!moveForward()) {
//             // Hit obstacle - move down and reverse direction
//             moveDownAndReverse();
//         }
//     }
// }

// /**
//  * @brief Move centipede forward one grid cell
//  *
//  * Adds new head position and removes tail.
//  * Updates grid accordingly.
//  *
//  * @return true if successful, false if blocked
//  */
// bool Centipede::moveForward() {
//     if (segments.empty()) {
//         return false;
//     }

//     // Get current head position
//     int headX = segments.front().gridX;
//     int headY = segments.front().gridY;

//     // Calculate new head position based on direction
//     int newHeadX = headX + static_cast<int>(direction);
//     int newHeadY = headY;

//     // Check if new position is passable
//     if (!isPassable(newHeadX, newHeadY)) {
//         return false;  // Blocked
//     }

//     // Clear centipede from grid before moving
//     clearFromGrid();

//     // Add new head
//     segments.push_front(CentipedeSegment(newHeadX, newHeadY));

//     // Remove tail (keeps length constant)
//     segments.pop_back();

//     // Update grid with new positions
//     updateGridOccupancy();

//     return true;
// }

// /**
//  * @brief Move down and reverse direction
//  *
//  * Called when centipede hits a wall or mushroom.
//  * Moves entire centipede down one row, then reverses left/right direction.
//  */
// void Centipede::moveDownAndReverse() {
//     std::cout << "[Centipede] Moving down and reversing direction" << std::endl;

//     clearFromGrid();

//     // Move all segments down one row
//     for (auto& segment : segments) {
//         segment.gridY += 1;

//         // Check bounds - if went off bottom, keep at bottom
//         if (segment.gridY >= grid->getGridHeight()) {
//             segment.gridY = grid->getGridHeight() - 1;
//         }
//     }

//     // Reverse direction
//     direction = (direction == MOVING_RIGHT) ? MOVING_LEFT : MOVING_RIGHT;

//     updateGridOccupancy();
// }

// // ===== DAMAGE & DEATH =====

// /**
//  * @brief Shoot a segment
//  *
//  * Removes the segment and potentially creates a new centipede if it splits.
//  * When head/tail are removed, reassigns segment types to maintain proper textures.
//  *
//  * @param segmentIndex Index of segment to shoot
//  * @return New centipede if split occurs, nullptr otherwise
//  */
// Centipede* Centipede::shootSegment(int segmentIndex) {
//     if (segmentIndex < 0 || segmentIndex >= static_cast<int>(segments.size())) {
//         return nullptr;  // Invalid index
//     }

//     std::cout << "[Centipede] Segment " << segmentIndex << " shot! Length: " << segments.size() << std::endl;

//     clearFromGrid();

//     Centipede* newCentipede = nullptr;

//     // If middle segment is shot, create a new centipede from the tail part
//     if (segmentIndex > 0 && segmentIndex < static_cast<int>(segments.size()) - 1) {
//         // Create new centipede from remaining tail segments
//         int tailLength = segments.size() - segmentIndex - 1;

//         // Extract tail segments
//         std::deque<CentipedeSegment> tailSegments(
//             segments.begin() + segmentIndex + 1,
//             segments.end()
//         );

//         // Create new centipede with tail segments
//         newCentipede = new Centipede(grid, headTexture, bodyTexture, tailTexture, tailLength, direction);

//         // Remove tail segments from this centipede
//         while (segments.size() > segmentIndex) {
//             segments.pop_back();
//         }

//         std::cout << "[Centipede] Split! Original: " << segments.size()
//                   << " segments, New: " << tailLength << " segments" << std::endl;
//     } else {
//         // Head or tail shot - just remove that segment
//         segments.erase(segments.begin() + segmentIndex);

//         std::cout << "[Centipede] Segment removed. Remaining: " << segments.size() << std::endl;
//     }

//     // FIX: Reassign segment types to maintain correct textures
//     // After removing head or tail, we need to update all segment type indices
//     for (int i = 0; i < static_cast<int>(segments.size()); i++) {
//         segments[i].segmentType = i;
//     }

//     updateGridOccupancy();

//     return newCentipede;
// }

// // ===== POSITION & COLLISION =====

// /**
//  * @brief Get head position
//  */
// std::pair<int, int> Centipede::getHeadPosition() const {
//     if (segments.empty()) {
//         return std::make_pair(0, 0);
//     }
//     return std::make_pair(segments.front().gridX, segments.front().gridY);
// }

// /**
//  * @brief Get specific segment position
//  */
// std::pair<int, int> Centipede::getSegmentPosition(int segmentIndex) const {
//     if (segmentIndex < 0 || segmentIndex >= static_cast<int>(segments.size())) {
//         return std::make_pair(0, 0);
//     }
//     return std::make_pair(segments[segmentIndex].gridX, segments[segmentIndex].gridY);
// }

// /**
//  * @brief Get global bounds
//  */
// sf::FloatRect Centipede::getGlobalBounds() const {
//     if (segments.empty()) {
//         return sf::FloatRect(0, 0, 0, 0);
//     }

//     // Find bounding box containing all segments
//     float minX = grid->gridToPixelX(segments.front().gridX);
//     float minY = grid->gridToPixelY(segments.front().gridY);
//     float maxX = minX + GameGrid::CELL_SIZE;
//     float maxY = minY + GameGrid::CELL_SIZE;

//     for (const auto& segment : segments) {
//         float x = grid->gridToPixelX(segment.gridX);
//         float y = grid->gridToPixelY(segment.gridY);

//         if (x < minX) minX = x;
//         if (y < minY) minY = y;
//         if (x + GameGrid::CELL_SIZE > maxX) maxX = x + GameGrid::CELL_SIZE;
//         if (y + GameGrid::CELL_SIZE > maxY) maxY = y + GameGrid::CELL_SIZE;
//     }

//     return sf::FloatRect(minX, minY, maxX - minX, maxY - minY);
// }

// /**
//  * @brief Find segment at position
//  */
// int Centipede::getSegmentAtPosition(int gridX, int gridY) const {
//     for (int i = 0; i < static_cast<int>(segments.size()); i++) {
//         if (segments[i].gridX == gridX && segments[i].gridY == gridY) {
//             return i;
//         }
//     }
//     return -1;
// }

// // ===== RENDERING =====

// /**
//  * @brief Draw all segments
//  *
//  * Each segment uses its appropriate texture rect from the atlas (head, body, or tail).
//  */
// void Centipede::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//     for (int i = 0; i < static_cast<int>(segments.size()); i++) {
//         const auto& segment = segments[i];

//         // Create sprite for this segment
//         sf::Sprite sprite;

//         // All sprites use the same texture
//         sprite.setTexture(headTexture);  // All use same texture (atlas)

//         // Determine which texture rect to use based on segment type
//         sf::IntRect textureRect;

//         if (i == 0) {
//             // Head segment - TODO: Adjust these coordinates to match your atlas
//             textureRect = sf::IntRect(0, 0, 32, 32);  // Head position in atlas
//         } else if (i == static_cast<int>(segments.size()) - 1) {
//             // Tail segment
//             textureRect = sf::IntRect(64, 0, 32, 32);  // Tail position in atlas
//         } else {
//             // Body segment
//             textureRect = sf::IntRect(32, 0, 32, 32);  // Body position in atlas
//         }

//         sprite.setTextureRect(textureRect);

//         // Position sprite at grid cell center
//         sf::Vector2f pixelPos = grid->gridToCenterPixel(segment.gridX, segment.gridY);
//         sprite.setPosition(pixelPos);

//         // Center the sprite on the cell
//         sprite.setOrigin(16, 16);  // 32x32 / 2 = 16

//         target.draw(sprite, states);
//     }
// }

// // ===== PRIVATE HELPER FUNCTIONS =====

// /**
//  * @brief Initialize segments in a line
//  *
//  * Creates segments starting at the top center, moving right.
//  * Assigns proper segment types (head, body, tail).
//  *
//  * @param length Number of segments
//  */
// void Centipede::initializeSegments(int length) {
//     segments.clear();

//     // Start at top center of grid
//     int startX = grid->getGridWidth() / 2;
//     int startY = 2;  // A few cells down from top

//     // Create segments in a horizontal line
//     for (int i = 0; i < length; i++) {
//         int segX = startX - i;  // Line extends to the left from start

//         // Make sure segment is in bounds
//         if (segX >= 0 && segX < grid->getGridWidth()) {
//             // Determine segment type (0=head, 1..n-2=body, n-1=tail)
//             int segmentType = i;
//             segments.push_back(CentipedeSegment(segX, startY, nullptr, segmentType));
//         }
//     }

//     std::cout << "[Centipede] Initialized " << segments.size() << " segments" << std::endl;
// }

// /**
//  * @brief Check if position is passable
//  */
// bool Centipede::isPassable(int gridX, int gridY) const {
//     // Out of bounds?
//     if (!grid->isInBounds(gridX, gridY)) {
//         return false;
//     }

//     // Blocked by mushroom or another centipede?
//     if (grid->isOccupied(gridX, gridY, MUSHROOM | CENTIPEDE)) {
//         return false;
//     }

//     return true;
// }

// /**
//  * @brief Update grid occupancy
//  */
// void Centipede::updateGridOccupancy() {
//     for (const auto& segment : segments) {
//         grid->setOccupied(segment.gridX, segment.gridY, CENTIPEDE);
//     }
// }

// /**
//  * @brief Clear from grid
//  */
// void Centipede::clearFromGrid() {
//     for (const auto& segment : segments) {
//         grid->clearOccupied(segment.gridX, segment.gridY, CENTIPEDE);
//     }
// }

// /**
//  * @brief Debug print
//  */
// void Centipede::debugPrint() const {
//     std::cout << "\n[Centipede] Debug Info:" << std::endl;
//     std::cout << "  Length: " << segments.size() << std::endl;
//     std::cout << "  Direction: " << (direction == MOVING_RIGHT ? "RIGHT" : "LEFT") << std::endl;
//     std::cout << "  Head: (" << segments.front().gridX << ", " << segments.front().gridY << ")" << std::endl;
//     std::cout << "  Tail: (" << segments.back().gridX << ", " << segments.back().gridY << ")" << std::endl;
//     std::cout << std::endl;
// }