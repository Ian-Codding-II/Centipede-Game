/**
 * @file game.cpp
 * @author Ian Codding II
 * @brief
 * @version 0.1
 * @date 2025-10-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../includes/game.h"
#include "../includes/errorHandler.h"
#include "../includes/ScreenManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @brief Construct a new Game:: Game object
 * 
 */
Game::Game(sf::RenderWindow& win, ScreenManager & screenMGR) 
    :window(win),
    screenManager(screenMGR),
    currentState(GameState::MENU),
    score(0),
    lives(){
    
}
Game::Game(sf::RenderWindow &win, ScreenManager &sm) {
    
}
Game::~Game(){
    
}
void Game::handleInput() {
    
}
void Game::update(float time) {
    
}
void Game::render() {
    
}
bool Game::isDone() const {
    
}