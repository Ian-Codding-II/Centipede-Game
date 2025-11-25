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
 * Sets up the initial state with default settings values:
 * - 3 starting lives
 * - Spawn level 1
 * - Player icon 0 (first icon selected)
 * 
 * All button pointers are initialized to nullptr for safety.
 * Button creation happens in initialize().
 * 
 * @param win Reference to the main window
 * @param fnt Reference to the shared font
 */
SettingsScreen::SettingsScreen(sf::RenderWindow& win, sf::Font& fnt)
    : Screen(win, fnt),
      backButton(nullptr),
      livesUpButton(nullptr),
      livesDownButton(nullptr),
      levelUpButton(nullptr),
      levelDownButton(nullptr),
      lives(3),
      spawnLevel(1),
      selectedPlayerIcon(0) {
    
    std::cout << "[SettingsScreen] Constructor called" << std::endl;
    
    // Set up the black background
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);
    
    // Set up the title text
    titleText.setFont(font);
    titleText.setString("SETTINGS");
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::Green);

    titleText.setPosition(
        (1200 - titleText.getLocalBounds().width) / 2,
        60
    );
    
    // Set up info text for displaying current values
    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color::Yellow);
}

/**
 * @brief Destructor - clean up resources
 */
SettingsScreen::~SettingsScreen() {
    std::cout << "[SettingsScreen] Destructor called" << std::endl;
    cleanup();
}

/**
 * @brief Initialize - create all buttons for this screen
 * 
 * Creates 9 buttons total:
 * - 2 buttons for lives adjustment (+/-)
 * - 2 buttons for spawn level adjustment (+/-)
 * - 4 buttons for player icon selection (1, 2, 3, 4)
 * - 1 back button to return to main menu
 * 
 * Button constructor signature:
 * Button(std::string label, sf::Vector2f position, sf::Vector2f size, sf::Color color)
 * 
 * Layout (vertical):
 * - Title
 * - Lives: X  [-] [+]
 * - Spawn Level: X  [-] [+]
 * - Player Icon: [1] [2] [3] [4]
 * - Back button
 */
void SettingsScreen::initialize() {
    std::cout << "[SettingsScreen] initialize() called" << std::endl;

    float winWidth = 1200;
    float winHeight = 800;
    
    // Button sizing proportional to CURRENT window
    float smallButtonSize = 50;
    float largeButtonWidth = 200;
    float largeButtonHeight = 50;
    float centerX = winWidth / 2;
    
    // Positions as percentage of CURRENT window height
    float livesY = winHeight * 0.30f;
    float levelY = winHeight * 0.45f;
    float iconY = winHeight * 0.60f;
    float backY = winHeight -100;

    // ========== LIVES ADJUSTMENT ==========
    // Lives Down button (-)
    // Positioned on the left side
    livesDownButton = new Button(
        "-",
        sf::Vector2f(centerX - winWidth * 0.15f, livesY),
        sf::Vector2f(smallButtonSize, smallButtonSize),
        sf::Color::Red
    );
    livesDownButton->setColorTextNormal(sf::Color::White);
    livesDownButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[SettingsScreen] Created Lives Down button" << std::endl;

    // Lives Up button (+)
    // Positioned to the right of the Down button
    livesUpButton = new Button(
        "+",
        sf::Vector2f(centerX + winWidth * 0.15f, livesY),
        sf::Vector2f(smallButtonSize, smallButtonSize),
        sf::Color::Green
    );
    livesUpButton->setColorTextNormal(sf::Color::White);
    livesUpButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[SettingsScreen] Created Lives Up button" << std::endl;
    
    // ========== SPAWN LEVEL ADJUSTMENT ==========
    // Spawn Level Down button (-)
    levelDownButton = new Button(
        "-",
        sf::Vector2f(centerX - winWidth * 0.15f, levelY),
        sf::Vector2f(smallButtonSize, smallButtonSize),
        sf::Color::Red
    );
    levelDownButton->setColorTextNormal(sf::Color::White);
    levelDownButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[SettingsScreen] Created Level Down button" << std::endl;
    
    // Spawn Level Up button (+)
    levelUpButton = new Button(
        "+",
        sf::Vector2f(centerX + winWidth * 0.15f, levelY),
        sf::Vector2f(smallButtonSize, smallButtonSize),
        sf::Color::Green
    );
    levelUpButton->setColorTextNormal(sf::Color::White);
    levelUpButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[SettingsScreen] Created Level Up button" << std::endl;
    

    // ========== PLAYER ICON SELECTION ==========
    // Create 4 buttons numbered 1, 2, 3, 4 for player icon selection
    // Space them evenly across the middle of the screen
    // float iconStartX = (winWidth / 2) - (4 * (buttonWidth + spacing)) / 2;
    
    // Player icon buttons
    float iconButtonSize = winHeight * 0.08f;
    float iconStartX = centerX - (iconButtonSize * 2 + winWidth * 0.05f);
    float iconSpacing = winWidth * 0.05f;

    for (int i = 0; i < 4; i++) {
        // Convert number to string (1, 2, 3, 4)
        std::string iconLabel = std::to_string(i + 1);
        
        // Create button at appropriate position
        Button* iconButton = new Button(
            iconLabel,
            sf::Vector2f(iconStartX + i * (iconButtonSize + iconSpacing), iconY),
            sf::Vector2f(iconButtonSize, iconButtonSize),
            sf::Color::Blue
        );
        iconButton->setColorTextNormal(sf::Color::White);
        iconButton->setColorTextHover(sf::Color::Yellow);
        
        // Add to vector
        playerIconButtons.push_back(iconButton);
        std::cout << "[SettingsScreen] Created Player Icon button " << (i + 1) << std::endl;
    }

    // ========== BACK BUTTON ==========
    // Back button to return to main menu
    // Centered at the bottom
    backButton = new Button(
        "Back",
        sf::Vector2f(centerX - largeButtonWidth*2, backY),
        sf::Vector2f(largeButtonWidth, largeButtonHeight),
        sf::Color::Green
    );
    backButton->setColorTextNormal(sf::Color::Black);
    backButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[SettingsScreen] Created Back button" << std::endl;
}

/**
 * @brief Update - process events and handle setting changes
 * 
 * Updates all buttons and handles:
 * - Lives +/- adjustments (1-5 range)
 * - Spawn level +/- adjustments (0+ range)
 * - Player icon selection (0-3)
 * - Back button to return to menu
 * 
 * Note: Button::update() takes (sf::Event&, sf::RenderWindow&)
 * Note: Button::getState() returns: normal, hovered, or clicked
 * 
 * @param event The SFML event to process
 * @return Next state (SETTINGS if staying, MENU if Back clicked)
 */
GameState SettingsScreen::update(sf::Event& event) {
    // Update Lives Down button
    if (livesDownButton != nullptr) {
        livesDownButton->update(event, window);
        if (livesDownButton->getState() == clicked) {
            // Decrease lives, but keep minimum of 1
            if (lives > 1) {
                lives--;
                std::cout << "[SettingsScreen] Lives decreased to " << lives << std::endl;
            }
        }
    }
    
    // Update Lives Up button
    if (livesUpButton != nullptr) {
        livesUpButton->update(event, window);
        if (livesUpButton->getState() == clicked) {
            // Increase lives, but keep maximum of 5
            if (lives < 50) {
                lives++;
                std::cout << "[SettingsScreen] Lives increased to " << lives << std::endl;
            }
        }
    }
    
    // Update Spawn Level Down button
    if (levelDownButton != nullptr) {
        levelDownButton->update(event, window);
        if (levelDownButton->getState() == clicked) {
            // Decrease level, but keep minimum of 0
            if (spawnLevel > 0) {
                spawnLevel--;
                std::cout << "[SettingsScreen] Spawn level decreased to " << spawnLevel << std::endl;
            }
        }
    }
    
    // Update Spawn Level Up button
    if (levelUpButton != nullptr) {
        levelUpButton->update(event, window);
        if (levelUpButton->getState() == clicked) {
            // Increase level (no upper limit)
            spawnLevel++;
            std::cout << "[SettingsScreen] Spawn level increased to " << spawnLevel << std::endl;
        }
    }
    
    // Update all player icon selection buttons
    for (long unsigned int i = 0; i < playerIconButtons.size(); i++) {
        if (playerIconButtons[i] != nullptr) {
            playerIconButtons[i]->update(event, window);
            if (playerIconButtons[i]->getState() == clicked) {
                // User clicked icon button i, so select it
                selectedPlayerIcon = i;
                std::cout << "[SettingsScreen] Player icon " << (i + 1) << " selected" << std::endl;
            }
        }
    }
    
    // Update Back button
    if (backButton != nullptr) {
        backButton->update(event, window);
        if (backButton->getState() == clicked) {
            std::cout << "[SettingsScreen] Back clicked - returning to menu" << std::endl;
            return GameState::MENU;
        }
    }
    
    // Stay in settings
    return GameState::SETTINGS;
}

/**
 * @brief Render - draw the settings screen
 * 
 * Draws in order:
 * 1. Background
 * 2. Title
 * 3. Setting labels and current values
 * 4. All buttons
 * 5. Highlight around selected player icon
 */
void SettingsScreen::render() {
    // Draw background
    window.draw(background);
    
    // Draw title
    window.draw(titleText);
        
    // ========== DRAW SETTINGS LABELS AND VALUES ==========
    
    // Lives label and value
    infoText.setString("Lives: " + std::to_string(lives));
    infoText.setPosition(1200 / 2 - 150, 155);
    window.draw(infoText);
    
    // Spawn Level label and value
    infoText.setString("Spawn Level: " + std::to_string(spawnLevel));
    infoText.setPosition(1200 / 2 - 150, 255);
    window.draw(infoText);
    
    // Player Icon label
    infoText.setString("Player Icon:");
    infoText.setPosition(1200 / 2 - 150, 355);
    window.draw(infoText);
    
    // ========== DRAW BUTTONS ==========
    
    // Draw Lives adjustment buttons
    if (livesDownButton != nullptr) {
        window.draw(*livesDownButton);
    }
    if (livesUpButton != nullptr) {
        window.draw(*livesUpButton);
    }
    
    // Draw Spawn Level adjustment buttons
    if (levelDownButton != nullptr) {
        window.draw(*levelDownButton);
    }
    if (levelUpButton != nullptr) {
        window.draw(*levelUpButton);
    }
    
    // Draw Player Icon buttons and highlight selected one
    for (long unsigned int i = 0; i < playerIconButtons.size(); i++) {
        if (playerIconButtons[i] != nullptr) {
            window.draw(*playerIconButtons[i]);
            
            // If this is the selected icon, draw a yellow border around it
            if (static_cast<int> (i) == selectedPlayerIcon) {
                sf::RectangleShape highlight = 
                    sf::RectangleShape(sf::Vector2f(50, 50));
                
                // Position highlight over the button
                highlight.setPosition(
                    playerIconButtons[i]->getPosition().x -2,
                    playerIconButtons[i]->getPosition().y - 2
                );
                
                // Make it look like a border
                highlight.setFillColor(sf::Color::Transparent);
                highlight.setOutlineThickness(3);
                highlight.setOutlineColor(sf::Color::Yellow);
                window.draw(highlight);
            }
        }
    }
    
    // Draw Back button
    if (backButton != nullptr) {
        window.draw(*backButton);
    }
}

/**
 * @brief Cleanup - delete all buttons
 * 
 * Called when transitioning away from this screen.
 * Deletes all button objects to free memory.
 */
void SettingsScreen::cleanup() {
    std::cout << "[SettingsScreen] cleanup() called" << std::endl;
    
    // Delete adjustment buttons
    if (livesDownButton != nullptr) {
        delete livesDownButton;
        livesDownButton = nullptr;
    }
    if (livesUpButton != nullptr) {
        delete livesUpButton;
        livesUpButton = nullptr;
    }
    if (levelDownButton != nullptr) {
        delete levelDownButton;
        levelDownButton = nullptr;
    }
    if (levelUpButton != nullptr) {
        delete levelUpButton;
        levelUpButton = nullptr;
    }
    
    // Delete all player icon buttons
    for (long unsigned int i = 0; i < playerIconButtons.size(); i++) {
        if (playerIconButtons[i] != nullptr) {
            delete playerIconButtons[i];
            playerIconButtons[i] = nullptr;
        }
    }
    playerIconButtons.clear();
    
    // Delete back button
    if (backButton != nullptr) {
        delete backButton;
        backButton = nullptr;
    }
    
    std::cout << "[SettingsScreen] All buttons deleted" << std::endl;
}