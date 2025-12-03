/**
 * @file GameGrid.h
 * @author Ian Codding II
 * @brief Grid-based system for managing game world - centipedes, mushrooms, player
 * @version 1.0
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 *
 * GRID SYSTEM EXPLANATION:
 *
 * The game world is divided into a grid of cells.
 * Each cell can contain: mushrooms, centipede segments, player, bullets, etc.
 *
 * DESIGN RESOLUTION: 1200x800
 * GRID CELL SIZE: 32x32 pixels (configurable)
 *
 * GRID LAYOUT:
 * - Horizontal cells: 1200 / 32 = 37.5 → 37 cells wide
 * - Vertical cells: 800 / 32 = 25 cells tall
 * - Total cells: 37 × 25 = 925 cells
 *
 * COORDINATE SYSTEM:
 * - Grid coordinates: (gridX, gridY) - 0 to 36 horizontal, 0 to 24 vertical
 * - Pixel coordinates: (pixelX, pixelY) - 0 to 1200, 0 to 800
 * - Conversion:
 *   gridX = pixelX / CELL_SIZE
 *   gridY = pixelY / CELL_SIZE
 *   pixelX = gridX * CELL_SIZE
 *   pixelY = gridY * CELL_SIZE
 *
 * MOVEMENT:
 * - Centipede moves 1 grid cell per time step
 * - Player moves 1 grid cell per key press
 * - Bullets move multiple cells per frame
 * - All collision detection uses grid cells
 *
 * OCCUPIED CELLS:
 * - Each cell tracks what's in it
 * - Prevents overlapping of solid objects
 * - Allows fast collision detection
 */

#ifndef GAME_GRID_H
#define GAME_GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

/**
 * @brief Cell content flags - what can occupy a grid cell
 * Multiple flags can be set (e.g., MUSHROOM | BULLET)
 */
enum CellContent {
    EMPTY       = 0,      // No content
    MUSHROOM    = 1 << 0, // Mushroom obstacle (blocks movement)
    CENTIPEDE   = 1 << 1, // Centipede segment (blocks movement, collision)
    PLAYER      = 1 << 2, // Player (blocks centipede)
    BULLET      = 1 << 3, // Bullet (no blocking, destroys on collision)
    WALL        = 1 << 4  // Boundary walls
};

/**
 * @class GameGrid
 * @brief Manages the grid-based game world
 *
 * Responsibilities:
 * - Convert between pixel and grid coordinates
 * - Track what's in each cell
 * - Provide fast collision/occupancy queries
 * - Generate valid mushroom positions
 * - Validate movement paths for centipede and player
 *
 * Example usage:
 * ```cpp
 * GameGrid grid(1200, 800, 32);  // 32x32 pixel cells
 *
 * // Convert pixel to grid
 * int gridX = grid.pixelToGridX(100);
 * int gridY = grid.pixelToGridY(200);
 *
 * // Check if cell is occupied
 * if (grid.isOccupied(gridX, gridY, MUSHROOM | CENTIPEDE)) {
 *     // Can't move here - blocked by mushroom or centipede
 * }
 *
 * // Mark cell as occupied
 * grid.setOccupied(gridX, gridY, MUSHROOM);
 *
 * // Generate random empty cell for mushroom
 * auto [mushroomX, mushroomY] = grid.getRandomEmptyCell();
 * ```
 */
class GameGrid {
public:
    // Cell size in pixels (32x32 is standard for retro games like Centipede)
    static const int CELL_SIZE = 32;

    /**
     * @brief Constructor - initialize grid with given dimensions
     *
     * @param windowWidth Pixel width of game world (e.g., 1200)
     * @param windowHeight Pixel height of game world (e.g., 800)
     */
    GameGrid(int windowWidth, int windowHeight);

    /**
     * @brief Destructor - clean up grid
     */
    ~GameGrid();

    // ===== COORDINATE CONVERSION =====

    /**
     * @brief Convert pixel X to grid X
     * @param pixelX X coordinate in pixels
     * @return Grid X coordinate (0 to gridWidth-1)
     */
    int pixelToGridX(float pixelX) const;

    /**
     * @brief Convert pixel Y to grid Y
     * @param pixelY Y coordinate in pixels
     * @return Grid Y coordinate (0 to gridHeight-1)
     */
    int pixelToGridY(float pixelY) const;

    /**
     * @brief Convert grid X to pixel X (top-left of cell)
     * @param gridX Grid X coordinate
     * @return Pixel X coordinate
     */
    float gridToPixelX(int gridX) const;

    /**
     * @brief Convert grid Y to pixel Y (top-left of cell)
     * @param gridY Grid Y coordinate
     * @return Pixel Y coordinate
     */
    float gridToPixelY(int gridY) const;

    /**
     * @brief Get center of grid cell in pixels
     * @param gridX Grid X coordinate
     * @param gridY Grid Y coordinate
     * @return Center position as sf::Vector2f
     */
    sf::Vector2f gridToCenterPixel(int gridX, int gridY) const;

    // ===== GRID DIMENSIONS =====

    /**
     * @brief Get grid width in cells
     * @return Number of columns
     */
    int getGridWidth() const { return gridWidth; }

    /**
     * @brief Get grid height in cells
     * @return Number of rows
     */
    int getGridHeight() const { return gridHeight; }

    /**
     * @brief Check if grid coordinates are valid (in bounds)
     * @param gridX Grid X coordinate
     * @param gridY Grid Y coordinate
     * @return true if within grid bounds
     */
    bool isInBounds(int gridX, int gridY) const;

    // ===== CELL OCCUPANCY =====

    /**
     * @brief Check if cell is occupied by specific content type(s)
     *
     * Can check for multiple types at once:
     * `isOccupied(x, y, MUSHROOM | CENTIPEDE)` - check if either exists
     *
     * @param gridX Grid X coordinate
     * @param gridY Grid Y coordinate
     * @param contentMask Content type(s) to check (CellContent enum flags)
     * @return true if cell contains any of the specified content
     */
    bool isOccupied(int gridX, int gridY, int contentMask) const;

    /**
     * @brief Mark cell as occupied by content type
     *
     * Can set multiple content types in same cell:
     * `setOccupied(x, y, MUSHROOM)` - mark as having mushroom
     *
     * @param gridX Grid X coordinate
     * @param gridY Grid Y coordinate
     * @param contentType Content type to add (CellContent enum)
     */
    void setOccupied(int gridX, int gridY, int contentType);

    /**
     * @brief Clear specific content from cell
     *
     * @param gridX Grid X coordinate
     * @param gridY Grid Y coordinate
     * @param contentType Content type to remove (CellContent enum)
     */
    void clearOccupied(int gridX, int gridY, int contentType);

    /**
     * @brief Clear all content from cell
     *
     * @param gridX Grid X coordinate
     * @param gridY Grid Y coordinate
     */
    void clearCell(int gridX, int gridY);

    // ===== UTILITY FUNCTIONS =====

    /**
     * @brief Find random empty cell in grid
     *
     * Useful for spawning mushrooms in random locations.
     * Keeps trying until it finds an empty cell.
     * WARNING: If grid is too full, this could loop forever!
     *
     * @return Pair of (gridX, gridY) for an empty cell
     */
    std::pair<int, int> getRandomEmptyCell() const;

    /**
     * @brief Get all adjacent cells to given position
     *
     * Useful for checking what's around the player or centipede.
     * Returns cells that are in bounds.
     *
     * @param gridX Grid X coordinate
     * @param gridY Grid Y coordinate
     * @return Vector of (gridX, gridY) pairs for valid adjacent cells
     */
    std::vector<std::pair<int, int>> getAdjacentCells(int gridX, int gridY) const;

    /**
     * @brief Check if path is clear between two points
     *
     * Useful for validating centipede movement paths.
     * Checks if all cells along path are free of blocking content.
     *
     * @param startX Grid X start
     * @param startY Grid Y start
     * @param endX Grid X end
     * @param endY Grid Y end
     * @param blockingMask Content types that block the path
     * @return true if path is clear
     */
    bool isPathClear(int startX, int startY, int endX, int endY, int blockingMask) const;

    /**
     * @brief Debug - print grid to console
     *
     * Shows text representation of grid (useful for debugging).
     * Uses characters to represent content types.
     */
    void debugPrint() const;

private:
    // Grid dimensions
    int gridWidth;   // Number of columns
    int gridHeight;  // Number of rows

    // Grid data - stores content flags for each cell
    // gridData[y][x] contains CellContent flags for cell at (x, y)
    std::vector<std::vector<int>> gridData;

    /**
     * @brief Initialize all cells to EMPTY
     */
    void initializeGrid();
};

#endif // GAME_GRID_H