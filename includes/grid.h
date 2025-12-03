/**
 * @file    grid.h
 * @author  Balin Becker Ian Codding II Roman Salazar
 * @brief   Grid Class
 * @date    2025-12-01
 */

#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

class Grid {
public:
    Grid(sf::FloatRect Region, int cellSize);

    sf::Vector2f GetPosition(sf::Vector2f position);

    sf::FloatRect getRegion() const { return mRegion;}
private:
    sf::FloatRect mRegion;
    int mCellSize;
};

#endif