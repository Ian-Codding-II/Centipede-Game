/**
 * @file    centipede.h
 * @author  Ian Codding II, Balin Becker
 * @brief   Create a centipede simulator
 * @date    2025-10-21
 */

// Each segment is its own sprite
// Each segment of the array follows after one another
// Create an (array?) of segments

#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include "animated_object.h"
#include <vector>
#include <cmath>

class Centipede {
public:
    Centipede(sf::Texture& Texture) : Centipede(Texture, 8, sf::Vector2f(0, 0), sf::Vector2i(1, 1)) {};
    Centipede(sf::Texture& Texture, int length, sf::Vector2f position, sf::Vector2i factor);

    // Returns head position
    sf::Vector2f getPosition() {return mPosition;};

    void setPosition(sf::Vector2f position);

    void setScale(sf::Vector2i factor);
    void move(sf::Vector2f position);
    void fall();

private:
    struct segment {
        segment(anim_obj& sprite, std::string name) {
            mName = name;
            mSprite = &sprite;
        }
        anim_obj* mSprite;
        std::string mName;
    };

    std::vector<segment> mCentipedeVect;
    sf::Vector2f mPosition;
    int mSpacing;
    
};

#endif


// /**
//  * @file Centipede.h
//  * @author Ian Codding II
//  * @brief Centipede class - the main enemy in the game
//  * @version 1.0
//  * @date 2025-11-26
//  *
//  * @copyright Copyright (c) 2025
//  *
//  * CENTIPEDE MECHANICS:
//  *
//  * The centipede is a chain of segments that moves across the screen.
//  * - Head leads the movement
//  * - Body segments follow the head
//  * - Moves horizontally until hitting a wall or mushroom, then moves down and reverses direction
//  * - When shot, the segment dies and may split into two smaller centipedes
//  * - Centipede moves one grid cell per update
//  *
//  * GRID-BASED MOVEMENT:
//  * - Centipede occupies one grid cell per segment
//  * - Segments are stored as a queue (head at front, tail at back)
//  * - When moving, new head position is added, tail is removed
//  * - Each segment tracks its (gridX, gridY) position
//  *
//  * COLLISION WITH MUSHROOMS:
//  * - When centipede hits mushroom, it moves down one row
//  * - Then reverses horizontal direction (left <> right)
//  * - This creates the characteristic "bouncing" behavior
//  *
//  * SHOOTING MECHANICS:
//  * - When a segment is shot, it dies
//  * - If head is shot: centipede stops moving, segments turn into new centipede
//  * - If middle is shot: centipede splits into two (front half + back half)
//  * - If tail is shot: just removes that segment
//  *
//  * EXAMPLE PROGRESSION:
//  * ```
//  * Initial centipede (length 8):
//  * [H][1][2][3][4][5][6][T]
//  *
//  * Hit segment 3:
//  * [H][1][2]  and  [4][5][6][T]
//  * Two separate centipedes now!
//  * ```
//  */

// #ifndef CENTIPEDE_H
// #define CENTIPEDE_H

// #include <SFML/Graphics.hpp>
// #include <vector>
// #include <deque>
// #include <iostream>
// #include "GameGrid.h"

// /**
//  * @struct CentipedeSegment
//  * @brief A single segment of the centipede
//  *
//  * Contains position and visual information for one body part.
//  * Each segment has its own texture (head, body, tail are different).
//  */
// struct CentipedeSegment {
//     int gridX;              // Grid X position
//     int gridY;              // Grid Y position
//     sf::Texture* texture;   // Pointer to this segment's texture
//     int segmentType;        // 0=head, 1-n-2=body, n-1=tail

//     CentipedeSegment(int x, int y, sf::Texture* tex = nullptr, int type = 0) 
//         : gridX(x), gridY(y), texture(tex), segmentType(type) {}
// };

// /**
//  * @enum CentipedeDirection
//  * @brief Direction the centipede is moving
//  */
// enum CentipedeDirection {
//     MOVING_LEFT = -1,
//     MOVING_RIGHT = 1
// };

// /**
//  * @class Centipede
//  * @brief Main enemy class - a chain of segments that moves across the screen
//  *
//  * Responsibilities:
//  * - Store all segments in order (head to tail)
//  * - Move segments each frame (following grid system)
//  * - Handle collision with walls/mushrooms
//  * - Handle being shot and splitting
//  * - Draw all segments to screen
//  *
//  * Example usage:
//  * ```cpp
//  * GameGrid grid(1200, 800);
//  * Centipede centipede(&grid, texture, 10);  // 10 segments starting at top
//  *
//  * // Each frame:
//  * centipede.update(dt);  // Move centipede
//  * centipede.render(window);  // Draw it
//  *
//  * // When shot:
//  * if (bulletHitsSegment) {
//  *     Centipede* newCentipede = centipede.shootSegment(segmentIndex);
//  *     if (newCentipede) {
//  *         // A new centipede was created from the split
//  *         addCentipedeToGame(newCentipede);
//  *     }
//  * }
//  * ```
//  */
// class Centipede : public sf::Drawable {
// public:
//     /**
//      * @brief Constructor - create a new centipede
//      *
//      * Initializes a centipede starting at the top of the screen
//      * moving either left or right.
//      *
//      * @param grid Pointer to GameGrid for collision checking
//      * @param headTexture Texture for the head segment
//      * @param bodyTexture Texture for body segments
//      * @param tailTexture Texture for the tail segment
//      * @param length Number of segments in the centipede
//      * @param startDirection Direction to move (MOVING_LEFT or MOVING_RIGHT)
//      */
//     Centipede(GameGrid* grid, sf::Texture& headTexture, sf::Texture& bodyTexture, 
//               sf::Texture& tailTexture, int length, CentipedeDirection startDirection = MOVING_RIGHT);

//     /**
//      * @brief Destructor - cleanup
//      */
//     ~Centipede();

//     // ===== MOVEMENT =====

//     /**
//      * @brief Update - move centipede one step
//      *
//      * Called once per game frame. Moves the centipede according to its
//      * current direction and handles collisions with mushrooms/walls.
//      *
//      * @param dt Delta time (frame-independent, but may not be used for grid)
//      */
//     void update(float dt);

//     /**
//      * @brief Move centipede in current direction
//      *
//      * Checks if movement is valid (no collision), then:
//      * - Adds new head position
//      * - Removes tail position
//      * - Updates grid
//      *
//      * @return true if movement was successful, false if blocked
//      */
//     bool moveForward();

//     /**
//      * @brief Move centipede down one row and reverse direction
//      *
//      * Called when centipede hits a mushroom or wall.
//      * Moves down, then changes direction (left ↔ right).
//      */
//     void moveDownAndReverse();

//     // ===== DAMAGE & DEATH =====

//     /**
//      * @brief Shoot a specific segment of the centipede
//      *
//      * When a bullet hits a segment:
//      * - If head is shot: might stop and create new centipede from body
//      * - If middle is shot: splits into two centipedes
//      * - If tail is shot: just removes that segment
//      *
//      * Returns a new Centipede if the centipede splits (or nullptr if no split).
//      *
//      * @param segmentIndex Index of segment to shoot (0 = head)
//      * @return Pointer to new Centipede if split occurs, nullptr otherwise
//      */
//     Centipede* shootSegment(int segmentIndex);

//     /**
//      * @brief Check if centipede is still alive
//      *
//      * @return true if centipede has at least 1 segment
//      */
//     bool isAlive() const { return !segments.empty(); }

//     /**
//      * @brief Get number of segments
//      *
//      * @return Segment count
//      */
//     int getLength() const { return segments.size(); }

//     // ===== POSITION & COLLISION =====

//     /**
//      * @brief Get position of head segment
//      *
//      * @return Grid coordinates of head as (x, y) pair
//      */
//     std::pair<int, int> getHeadPosition() const;

//     /**
//      * @brief Get position of specific segment
//      *
//      * @param segmentIndex Index (0 = head, length-1 = tail)
//      * @return Grid coordinates as (x, y) pair
//      */
//     std::pair<int, int> getSegmentPosition(int segmentIndex) const;

//     /**
//      * @brief Get bounds of centipede (for collision detection)
//      *
//      * @return FloatRect covering all segments
//      */
//     sf::FloatRect getGlobalBounds() const;

//     /**
//      * @brief Check if centipede segment is at specific grid location
//      *
//      * Useful for collision checking.
//      *
//      * @param gridX Grid X position
//      * @param gridY Grid Y position
//      * @return Index of segment at that position, or -1 if none
//      */
//     int getSegmentAtPosition(int gridX, int gridY) const;

//     // ===== RENDERING =====

//     /**
//      * @brief Render - draw all centipede segments
//      *
//      * Inherited from sf::Drawable.
//      * Called automatically by window.draw(*centipede).
//      *
//      * @param target Render target (window)
//      * @param states Render states (transformations, etc.)
//      */
//     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

//     // ===== DEBUG =====

//     /**
//      * @brief Print centipede state to console
//      */
//     void debugPrint() const;

// private:
//     // Grid reference for collision checking
//     GameGrid* grid;

//     // Separate textures for different segment types
//     sf::Texture& headTexture;
//     sf::Texture& bodyTexture;
//     sf::Texture& tailTexture;

//     // All segments (deque allows efficient add/remove from both ends)
//     // Front (index 0) = head, Back = tail
//     std::deque<CentipedeSegment> segments;

//     // Current direction of movement
//     CentipedeDirection direction;

//     // Movement timer (for frame-by-frame movement)
//     float moveTimer;
//     const float MOVE_DELAY = 0.1f;  // Time between grid movements

//     /**
//      * @brief Initialize segments in a line
//      *
//      * Creates the initial centipede chain starting from the top.
//      *
//      * @param length Number of segments to create
//      */
//     void initializeSegments(int length);

//     /**
//      * @brief Check if a grid cell is passable (no collision)
//      *
//      * @param gridX Grid X position
//      * @param gridY Grid Y position
//      * @return true if centipede can move there
//      */
//     bool isPassable(int gridX, int gridY) const;

//     /**
//      * @brief Update grid to reflect current positions
//      *
//      * Marks all occupied cells in grid so other objects know where centipede is.
//      */
//     void updateGridOccupancy();

//     /**
//      * @brief Clear centipede from grid
//      *
//      * Removes CENTIPEDE flags from all cells the centipede occupies.
//      */
//     void clearFromGrid();
// };

// #endif // CENTIPEDE_H