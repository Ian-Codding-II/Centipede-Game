/**
 * @file mainMenu.cpp
 * @author Ian Codding II
 * @brief 
 * @version 0.1
 * @date 2025-10-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "../includes/mainMenu.h"
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& window) : mWindow(window) {
    // Create background immediately (doesn't need OpenGL context)
    mBackground.setSize({1280.f, 720.f});
    mBackground.setFillColor(sf::Color(0, 0, 0, 100));
    // Buttons created in initialize() instead
}

/**
 * @brief 
 * 
 */
void MainMenu::initialize() {
    if (mInitialized) return;  // Only initialize once
    
    try {
        // NOW safe to create buttons - OpenGL context is active
        mStartButton = new Button("Start Game", {640, 300}, {200, 60}, sf::Color::Blue);
        mStartButton->setColorTextNormal(sf::Color::Green);
        mStartButton->setColorTextHover(sf::Color::Red);

        mQuitButton = new Button("Quit", {640, 400}, {200, 60}, sf::Color::Blue);
        mQuitButton->setColorTextNormal(sf::Color::Black);
        mQuitButton->setColorTextHover(sf::Color::Red);
        
        mInitialized = true;
        std::cout << "[INFO] Menu initialized successfully\n";
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Failed to initialize menu: " << e.what() << "\n";
        throw;
    }
}

/**
 * @brief 
 * 
 * @param e 
 */
void MainMenu::update(sf::Event& e) {
    if (!mInitialized || !mStartButton || !mQuitButton) return;
    
    mStartButton->update(e, mWindow);
    mQuitButton->update(e, mWindow);

    if (mStartButton->getState() == clicked) {
        startPressed = true;
    }
    if (mQuitButton->getState() == clicked) {
        quitPressed = true;
    }

    if (startPressed || quitPressed) {
        mStartButton->setText(mStartButton->getText());
        mQuitButton->setText(mQuitButton->getText());
    }
}

/**
 * @brief 
 * 
 * @param window 
 */
void MainMenu::draw(sf::RenderWindow& window) {
    window.draw(mBackground);
    if (mInitialized && mStartButton && mQuitButton) {
        mStartButton->draw(window, sf::RenderStates::Default);
        mQuitButton->draw(window, sf::RenderStates::Default);
    }
}

/**
 * @brief 
 * 
 */
void MainMenu::reset() {
    startPressed = false;
    quitPressed = false;
}

/**
 * @brief Destroy the Main Menu:: Main Menu object
 * 
 */
MainMenu::~MainMenu() {
    delete mStartButton;
    delete mQuitButton;
}