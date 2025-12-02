/**
 * @file    grid.cpp
 * @author  Balin Becker
 * @brief   Grid Class Definitions
 * @date    2025-12-01
 */

#include "../includes/grid.h"

/**
 * @brief Construct a new Grid:: Grid object
 * 
 * @param Region Region grid exists
 */
Grid::Grid(sf::FloatRect Region, int cellSize) {
    mRegion = Region;
    mCellSize = cellSize;
}

/**
 * @brief Returns an adjusted position relative to the grid
 * 
 * @param position      Position to find
 * @return sf::Vector2i Adjusted Position
 */
sf::Vector2f Grid::GetPosition(sf::Vector2f position) {
    float snapX = std::floor(position.x / mCellSize) * mCellSize;
    float snapY = std::floor(position.y / mCellSize) * mCellSize;
    snapX = std::clamp(snapX, mRegion.left + mCellSize, mRegion.left + mRegion.width - mCellSize);
    snapY = std::clamp(snapY, mRegion.top + mCellSize, mRegion.top + mRegion.height - mCellSize);
    return sf::Vector2f(snapX, snapY);
}

