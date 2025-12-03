/**
 * @file GameGrid.cpp
 * @author Ian Codding II
 * @brief Implementation of grid-based game world system
 * @version 1.0
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 */

#include "../includes/GameGrid.h"
#include <cstdlib>
#include <cmath>

/**
 * @brief Constructor - initialize game grid
 *
 * Creates a 2D grid where each cell can track what content occupies it.
 * Grid dimensions are calculated from window size and CELL_SIZE.
 *
 * Example:
 * - Window: 1200x800 pixels
 * - CELL_SIZE: 32 pixels
 * - Grid: 38x25 cells (rounded up)
 *
 * @param windowWidth Pixel width of game world
 * @param windowHeight Pixel height of game world
 */
GameGrid::GameGrid(int windowWidth, int windowHeight) {
    // Calculate grid dimensions (round up to ensure full coverage)
    gridWidth = (windowWidth + CELL_SIZE - 1) / CELL_SIZE;  // Ceiling division
    gridHeight = (windowHeight + CELL_SIZE - 1) / CELL_SIZE;

    std::cout << "[GameGrid] Created grid: " << gridWidth << "x" << gridHeight << " cells" << std::endl;
    std::cout << "[GameGrid] Cell size: " << CELL_SIZE << "x" << CELL_SIZE << " pixels" << std::endl;
    std::cout << "[GameGrid] Total cells: " << (gridWidth * gridHeight) << std::endl;

    // Initialize grid with all cells empty
    initializeGrid();
}

/**
 * @brief Destructor
 */
GameGrid::~GameGrid() {
    std::cout << "[GameGrid] Destructor called" << std::endl;
}

/**
 * @brief Initialize all grid cells to EMPTY
 */
void GameGrid::initializeGrid() {
    // Create 2D vector of appropriate size
    gridData.clear();
    gridData.resize(gridHeight);

    for (int y = 0; y < gridHeight; y++) {
        gridData[y].resize(gridWidth, EMPTY);
    }

    std::cout << "[GameGrid] Grid initialized" << std::endl;
}

// ===== COORDINATE CONVERSION =====

/**
 * @brief Convert pixel X to grid X
 */
int GameGrid::pixelToGridX(float pixelX) const {
    int gridX = static_cast<int>(pixelX / CELL_SIZE);
    return std::max(0, std::min(gridX, gridWidth - 1));
}

/**
 * @brief Convert pixel Y to grid Y
 */
int GameGrid::pixelToGridY(float pixelY) const {
    int gridY = static_cast<int>(pixelY / CELL_SIZE);
    return std::max(0, std::min(gridY, gridHeight - 1));
}

/**
 * @brief Convert grid X to pixel X
 */
float GameGrid::gridToPixelX(int gridX) const {
    return static_cast<float>(gridX * CELL_SIZE);
}

/**
 * @brief Convert grid Y to pixel Y
 */
float GameGrid::gridToPixelY(int gridY) const {
    return static_cast<float>(gridY * CELL_SIZE);
}

/**
 * @brief Get center of grid cell in pixels
 */
sf::Vector2f GameGrid::gridToCenterPixel(int gridX, int gridY) const {
    float centerX = gridToPixelX(gridX) + CELL_SIZE / 2.0f;
    float centerY = gridToPixelY(gridY) + CELL_SIZE / 2.0f;
    return sf::Vector2f(centerX, centerY);
}

// ===== GRID BOUNDS =====

/**
 * @brief Check if grid coordinates are in bounds
 */
bool GameGrid::isInBounds(int gridX, int gridY) const {
    return gridX >= 0 && gridX < gridWidth &&
           gridY >= 0 && gridY < gridHeight;
}

// ===== CELL OCCUPANCY =====

/**
 * @brief Check if cell is occupied
 */
bool GameGrid::isOccupied(int gridX, int gridY, int contentMask) const {
    if (!isInBounds(gridX, gridY)) {
        return true; // Out of bounds is treated as occupied (blocked)
    }

    // Check if ANY of the content types in the mask are present
    return (gridData[gridY][gridX] & contentMask) != 0;
}

/**
 * @brief Mark cell as occupied
 */
void GameGrid::setOccupied(int gridX, int gridY, int contentType) {
    if (!isInBounds(gridX, gridY)) {
        return;
    }

    // Add the content type to the cell (bitwise OR)
    gridData[gridY][gridX] |= contentType;
}

/**
 * @brief Clear specific content from cell
 */
void GameGrid::clearOccupied(int gridX, int gridY, int contentType) {
    if (!isInBounds(gridX, gridY)) {
        return;
    }

    // Remove the content type from the cell (bitwise AND with complement)
    gridData[gridY][gridX] &= ~contentType;
}

/**
 * @brief Clear all content from cell
 */
void GameGrid::clearCell(int gridX, int gridY) {
    if (!isInBounds(gridX, gridY)) {
        return;
    }

    gridData[gridY][gridX] = EMPTY;
}

// ===== UTILITY FUNCTIONS =====

/**
 * @brief Find random empty cell
 *
 * Picks random cells until finding an empty one.
 * WARNING: If grid is very full, this could be slow!
 */
std::pair<int, int> GameGrid::getRandomEmptyCell() const {
    int attempts = 0;
    const int MAX_ATTEMPTS = 1000;

    while (attempts < MAX_ATTEMPTS) {
        int randomX = rand() % gridWidth;
        int randomY = rand() % gridHeight;

        // Skip boundary rows (top and bottom)
        if (randomY < 2 || randomY >= gridHeight - 2) {
            attempts++;
            continue;
        }

        if (!isOccupied(randomX, randomY, MUSHROOM | CENTIPEDE | PLAYER)) {
            return std::make_pair(randomX, randomY);
        }

        attempts++;
    }

    // Fallback if grid is full (shouldn't happen)
    std::cout << "[GameGrid] WARNING: Could not find empty cell after " << MAX_ATTEMPTS << " attempts" << std::endl;
    return std::make_pair(gridWidth / 2, gridHeight / 2);
}

/**
 * @brief Get adjacent cells (up, down, left, right)
 */
std::vector<std::pair<int, int>> GameGrid::getAdjacentCells(int gridX, int gridY) const {
    std::vector<std::pair<int, int>> adjacent;

    // Define the 4 adjacent cells (up, down, left, right)
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int adjX = gridX + dx[i];
        int adjY = gridY + dy[i];

        if (isInBounds(adjX, adjY)) {
            adjacent.push_back(std::make_pair(adjX, adjY));
        }
    }

    return adjacent;
}

/**
 * @brief Check if path is clear between two points
 *
 * Uses simple line-drawing algorithm (Bresenham-like) to check all cells along path.
 */
bool GameGrid::isPathClear(int startX, int startY, int endX, int endY, int blockingMask) const {
    // Simple line-drawing algorithm
    int dx = std::abs(endX - startX);
    int dy = std::abs(endY - startY);
    int sx = (startX < endX) ? 1 : -1;
    int sy = (startY < endY) ? 1 : -1;
    int err = dx - dy;

    int currentX = startX;
    int currentY = startY;

    while (true) {
        // Check if current cell is blocked
        if (isOccupied(currentX, currentY, blockingMask)) {
            return false;
        }

        // Reached end point
        if (currentX == endX && currentY == endY) {
            break;
        }

        // Step to next cell
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            currentX += sx;
        }
        if (e2 < dx) {
            err += dx;
            currentY += sy;
        }
    }

    return true;
}

/**
 * @brief Debug print - show grid contents
 */
void GameGrid::debugPrint() const {
    std::cout << "\n[GameGrid] Grid state:" << std::endl;

    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            int content = gridData[y][x];

            if (content == EMPTY) {
                std::cout << ".";
            } else if (content & MUSHROOM) {
                std::cout << "M";
            } else if (content & CENTIPEDE) {
                std::cout << "C";
            } else if (content & PLAYER) {
                std::cout << "P";
            } else if (content & BULLET) {
                std::cout << "B";
            } else if (content & WALL) {
                std::cout << "W";
            } else {
                std::cout << "?";
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}