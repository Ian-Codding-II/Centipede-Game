/**
 * @file SettingsScreen.cpp
 * @author Ian Codding II
 * @brief Implementation of SettingsScreen - settings/configuration interface
 * @version 1.0
 * @date 2025-10-27
 * 
 * @copyright Copyright (c) 2025
 */

#include "../includes/SettingsScreen.h"
#include "../includes/errorHandler.h"
#include <iostream>

/**
 * @brief Constructor - initialize the settings screen
 * 
 * Default settings:
 * - 3 starting lives
 * - Spawn level 1
 *
 * All button pointers are initialized to nullptr.
 */
SettingsScreen::SettingsScreen(sf::RenderWindow& win, sf::Font& fnt)
    : Screen(win, fnt),
      backButton(nullptr),
      livesUpButton(nullptr),
      livesDownButton(nullptr),
      levelUpButton(nullptr),
      levelDownButton(nullptr),
      lives(3),
      spawnLevel(1)
{
    std::cout << "[SettingsScreen] Constructor called" << std::endl;

    // Background
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);

    // Title
    titleText.setFont(font);
    titleText.setString("SETTINGS");
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::Green);

    titleText.setPosition(
        (1200 - titleText.getLocalBounds().width) / 2,
        25
    );

    // Info text
    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::Yellow);
}

/**
 * @brief Destructor
 */
SettingsScreen::~SettingsScreen() {
    std::cout << "[SettingsScreen] Destructor called" << std::endl;
    cleanup();
}

/**
 * @brief Initialize - create lives and level buttons and the back button
 */
void SettingsScreen::initialize() {
    std::cout << "[SettingsScreen] initialize() called" << std::endl;

    float winWidth = 1200;
    float winHeight = 800;

    float leftSideX = winWidth * 0.25f;

    float livesY = winHeight * 0.30f;
    float levelY = winHeight * 0.60f;
    float buttonSize = 50;

    // ===== LIVES =====
    livesDownButton = new Button(
        "_",
        sf::Vector2f(leftSideX, livesY),
        sf::Vector2f(buttonSize, buttonSize),
        sf::Color::Red
    );
    livesDownButton->setColorTextNormal(sf::Color::White);
    livesDownButton->setColorTextHover(sf::Color::Yellow);

    livesUpButton = new Button(
        "+",
        sf::Vector2f(winWidth - leftSideX, livesY),
        sf::Vector2f(buttonSize, buttonSize),
        sf::Color::Green
    );
    livesUpButton->setColorTextNormal(sf::Color::White);
    livesUpButton->setColorTextHover(sf::Color::Yellow);

    // ===== SPAWN LEVEL =====
    levelDownButton = new Button(
        "_",
        sf::Vector2f(leftSideX, levelY),
        sf::Vector2f(buttonSize, buttonSize),
        sf::Color::Red
    );
    levelDownButton->setColorTextNormal(sf::Color::White);
    levelDownButton->setColorTextHover(sf::Color::Yellow);

    levelUpButton = new Button(
        "+",
        sf::Vector2f(winWidth - leftSideX , levelY),
        sf::Vector2f(buttonSize, buttonSize),
        sf::Color::Green
    );
    levelUpButton->setColorTextNormal(sf::Color::White);
    levelUpButton->setColorTextHover(sf::Color::Yellow);

    // ===== BACK BUTTON =====
    float backButtonWidth = 200;
    float backButtonHeight = 50;
    float backY = winHeight - 100;

    backButton = new Button(
        "Back",
        sf::Vector2f( backButtonWidth, backY),
        sf::Vector2f(backButtonWidth, backButtonHeight),
        sf::Color::Green
    );
    backButton->setColorTextNormal(sf::Color::Black);
    backButton->setColorTextHover(sf::Color::Yellow);
}

/**
 * @brief Update the settings
 */
GameState SettingsScreen::update(sf::Event& event) {
    // Lives Down
    if (livesDownButton) {
        livesDownButton->update(event, window);
        if (livesDownButton->getState() == clicked && lives > 1) {
            lives--;
            std::cout << "[SettingsScreen] Lives decreased to " << lives << std::endl;
        }
    }

    // Lives Up
    if (livesUpButton) {
        livesUpButton->update(event, window);
        if (livesUpButton->getState() == clicked && lives < 50) {
            lives++;
            std::cout << "[SettingsScreen] Lives increased to " << lives << std::endl;
        }
    }

    // Spawn Level Down
    if (levelDownButton) {
        levelDownButton->update(event, window);
        if (levelDownButton->getState() == clicked && spawnLevel > 0) {
            spawnLevel--;
            std::cout << "[SettingsScreen] Spawn level decreased to " << spawnLevel << std::endl;
        }
    }

    // Spawn Level Up
    if (levelUpButton) {
        levelUpButton->update(event, window);
        if (levelUpButton->getState() == clicked) {
            spawnLevel++;
            std::cout << "[SettingsScreen] Spawn level increased to " << spawnLevel << std::endl;
        }
    }

    // Back button
    if (backButton) {
        backButton->update(event, window);
        if (backButton->getState() == clicked) {
            std::cout << "[SettingsScreen] Back clicked" << std::endl;
            return GameState::MENU;
        }
    }

    return GameState::SETTINGS;
}

/**
 * @brief Render the menu
 */
void SettingsScreen::render() {
    window.draw(background);
    window.draw(titleText);

    float leftSideX = 1200 * 0.35f;
    float livesY = 800 * 0.27f;
    float levelY = 800 * 0.57f;

    // Lives label
    infoText.setString("Lives: " + std::to_string(lives));
    infoText.setPosition(leftSideX + 80, livesY);
    window.draw(infoText);

    // Spawn Level label
    infoText.setString("Level: " + std::to_string(spawnLevel));
    infoText.setPosition(leftSideX + 80, levelY);
    window.draw(infoText);

    // Draw Buttons
    if (livesDownButton) window.draw(*livesDownButton);
    if (livesUpButton) window.draw(*livesUpButton);
    if (levelDownButton) window.draw(*levelDownButton);
    if (levelUpButton) window.draw(*levelUpButton);
    if (backButton) window.draw(*backButton);
}

/**
 * @brief Cleanup
 */
void SettingsScreen::cleanup() {
    std::cout << "[SettingsScreen] cleanup() called" << std::endl;

    delete livesDownButton; livesDownButton = nullptr;
    delete livesUpButton; livesUpButton = nullptr;
    delete levelDownButton; levelDownButton = nullptr;
    delete levelUpButton; levelUpButton = nullptr;
    delete backButton; backButton = nullptr;

    std::cout << "[SettingsScreen] All buttons deleted" << std::endl;
}
