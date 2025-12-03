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
        25
    );
    
    // Set up info text for displaying current values
    infoText.setFont(font);
    infoText.setCharacterSize(24);
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
 * @brief Initialize - create all buttons and load player sprites
 * 
 * NEW: Loads player sprite textures for display
 * Layout:
 * - Title: CENTER TOP
 * - LEFT SIDE:
 *   - Lives: [label] [-] [value] [+]
 *   - Level: [label] [-] [value] [+]
 * - RIGHT SIDE:
 *   - Player Icons: [sprite1] [sprite2] [sprite3] [sprite4]
 *   - With yellow outline on selected
 * - Back button: BOTTOM CENTER
 */
void SettingsScreen::initialize() {
    std::cout << "[SettingsScreen] initialize() called" << std::endl;

    float winWidth = 1200;
    float winHeight = 800;
    
    float centerX = winWidth / 2;
    float leftSideX = winWidth * 0.15f;    // Far left side
    float rightSideX = winWidth * 0.65f;   // Right side
    
    // ========== LEFT SIDE: LIVES AND LEVEL ==========
    
    float livesY = winHeight * 0.25f;
    float levelY = winHeight * 0.45f;
    float buttonSize = 50;
    float spacing = 20;
    
    // ===== LIVES =====
    // Lives Down button (-)
    livesDownButton = new Button(
        "-",
        sf::Vector2f(leftSideX, livesY),
        sf::Vector2f(buttonSize, buttonSize),
        sf::Color::Red
    );
    livesDownButton->setColorTextNormal(sf::Color::White);
    livesDownButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[SettingsScreen] Created Lives Down button" << std::endl;

    // Lives Up button (+)
    livesUpButton = new Button(
        "+",
        sf::Vector2f(leftSideX + buttonSize + spacing * 3, livesY),
        sf::Vector2f(buttonSize, buttonSize),
        sf::Color::Green
    );
    livesUpButton->setColorTextNormal(sf::Color::White);
    livesUpButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[SettingsScreen] Created Lives Up button" << std::endl;
    
    // ===== SPAWN LEVEL =====
    // Spawn Level Down button (-)
    levelDownButton = new Button(
        "-",
        sf::Vector2f(leftSideX, levelY),
        sf::Vector2f(buttonSize, buttonSize),
        sf::Color::Red
    );
    levelDownButton->setColorTextNormal(sf::Color::White);
    levelDownButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[SettingsScreen] Created Level Down button" << std::endl;
    
    // Spawn Level Up button (+)
    levelUpButton = new Button(
        "+",
        sf::Vector2f(leftSideX + buttonSize + spacing * 3, levelY),
        sf::Vector2f(buttonSize, buttonSize),
        sf::Color::Green
    );
    levelUpButton->setColorTextNormal(sf::Color::White);
    levelUpButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[SettingsScreen] Created Level Up button" << std::endl;

    // ========== RIGHT SIDE: PLAYER ICON SPRITES ==========
    
    float iconY = winHeight * 0.30f;
    float iconSize = 80;  // Size of each player sprite
    float iconSpacing = 30;
    
    // Load player sprite texture
    // This assumes you have 4 player sprites in a file or separate files
    // TODO: Load your actual player sprite texture here
    // For now, we'll just note where this should be loaded
    
    // Try to load player texture
    if (!playerTexture.loadFromFile("assets/sprites/atlas.png")) {
        logError("SettingsScreen", "Failed to load player sprite texture");
        std::cout << "[SettingsScreen] Player sprites will not display" << std::endl;
    } else {
        std::cout << "[SettingsScreen] Player sprite texture loaded successfully" << std::endl;
    }
    
    // Create 4 player icon displays
    for (int i = 0; i < 4; i++) {
        // Create a sprite for this player icon
        sf::Sprite playerSprite;
        playerSprite.setTexture(playerTexture);
        
        // Position the sprite
        float iconX = rightSideX + i * (iconSize + iconSpacing);
        playerSprite.setPosition(iconX, iconY);
        
        // Scale the sprite to fit the icon size
        playerSprite.setScale(
            iconSize / playerTexture.getSize().x,
            iconSize / playerTexture.getSize().y
        );
        
        // Store the sprite for rendering
        playerIconSprites.push_back(playerSprite);
        
        std::cout << "[SettingsScreen] Created Player Icon sprite " << (i + 1) << std::endl;
    }

    // ========== BACK BUTTON ==========
    // Back button to return to main menu - stays at bottom center
    float backY = winHeight - 100;
    float backButtonWidth = 200;
    float backButtonHeight = 50;
    
    backButton = new Button(
        "Back",
        sf::Vector2f(centerX - backButtonWidth / 2, backY),
        sf::Vector2f(backButtonWidth, backButtonHeight),
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
            spawnLevel++;
            std::cout << "[SettingsScreen] Spawn level increased to " << spawnLevel << std::endl;
        }
    }
    
    // Handle player icon selection (click on sprites on right side)
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Check if any player icon sprite was clicked
            for (int i = 0; i < static_cast<int>(playerIconSprites.size()); i++) {
                if (playerIconSprites[i].getGlobalBounds().contains(
                    window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    selectedPlayerIcon = i;
                    std::cout << "[SettingsScreen] Player icon " << (i + 1) << " selected" << std::endl;
                }
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
    
    // ========== LEFT SIDE: LIVES AND LEVEL LABELS ==========
    
    float leftSideX = 1200 * 0.15f;
    float livesY = 800 * 0.25f;
    float levelY = 800 * 0.45f;
    
    // Lives label
    infoText.setString("Lives: " + std::to_string(lives));
    infoText.setPosition(leftSideX + 80, livesY + 10);
    window.draw(infoText);
    
    // Spawn Level label
    infoText.setString("Level: " + std::to_string(spawnLevel));
    infoText.setPosition(leftSideX + 80, levelY + 10);
    window.draw(infoText);
    
    // ========== DRAW BUTTONS (LIVES AND LEVEL) ==========
    
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
    
    // ========== RIGHT SIDE: PLAYER ICON SPRITES ==========
    
    float rightSideX = 1200 * 0.65f;
    float iconY = 800 * 0.30f;
    float iconSize = 80;
    float iconSpacing = 30;
    
    // Draw player icon label
    infoText.setString("Player Icon:");
    infoText.setCharacterSize(24);
    infoText.setPosition(rightSideX, iconY - 40);
    window.draw(infoText);
    
    // Draw all player sprites
    for (int i = 0; i < static_cast<int>(playerIconSprites.size()); i++) {
        // Draw the sprite
        window.draw(playerIconSprites[i]);
        
        // If this is the selected icon, draw a yellow outline around it
        if (i == selectedPlayerIcon) {
            float iconX = rightSideX + i * (iconSize + iconSpacing);
            
            // Create a rectangle outline that matches the sprite bounds
            sf::RectangleShape outline(sf::Vector2f(iconSize, iconSize));
            
            // ✅ FIX: Position the outline correctly
            // The outline should be centered on the sprite position
            outline.setPosition(iconX, iconY);
            
            // Make it transparent with just an outline
            outline.setFillColor(sf::Color::Transparent);
            outline.setOutlineThickness(4);  // 4 pixels thick border
            outline.setOutlineColor(sf::Color::Yellow);
            
            window.draw(outline);
            
            std::cout << "[SettingsScreen] Drawing yellow outline at (" << iconX << ", " << iconY << ")" << std::endl;
        }
    }
    
    // ========== DRAW BACK BUTTON ==========
    
    // Draw Back button
    if (backButton != nullptr) {
        window.draw(*backButton);
    }
}

/**
 * @brief Cleanup - delete all buttons and sprites
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
    
    // Clear player icon sprites
    playerIconSprites.clear();
    
    // Delete back button
    if (backButton != nullptr) {
        delete backButton;
        backButton = nullptr;
    }
    
    std::cout << "[SettingsScreen] All buttons deleted" << std::endl;
}