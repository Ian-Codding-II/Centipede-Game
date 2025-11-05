/**
 * @file mainMenu.h
 * @author Ian Codding II
 * @brief
 * @version 0.1
 * @date 2025-10-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../includes/button.h"
#include <SFML/Graphics.hpp>

class MainMenu {
public:
    MainMenu(sf::RenderWindow &window);
    void initialize(); // NEW: Call this after window is ready
    void update(sf::Event &e);
    void draw(sf::RenderWindow &window);
    bool shouldStartGame() const { return startPressed; }
    bool shouldQuit() const { return quitPressed; }
    void reset();
    ~MainMenu();

private:
    sf::RenderWindow &mWindow;
    Button *mStartButton = nullptr; // Pointers, initialized to null
    Button *mQuitButton = nullptr;
    bool startPressed = false;
    bool quitPressed = false;
    sf::RectangleShape mBackground;
    bool mInitialized = false; // Track initialization
};