/**
 * @file PauseScreen.cpp
 * @author Ian Codding II
 * @brief Implementation of PauseScreen - pause menu during gameplay
 * @version 1.1 - Fixed state management
 * @date 2025-10-27
 * 
 * @copyright Copyright (c) 2025
 */

#include "../includes/PauseScreen.h"
#include "../includes/errorHandler.h"
#include <iostream>

/**
 * @brief Constructor - initialize the pause screen
 * 
 * Sets up the initial state with:
 * - All button pointers to nullptr
 * - showQuitDialog to false
 * - Semi-transparent overlay (to dim the game behind it)
 * - "PAUSED" title text
 * 
 * The overlay covers the entire screen with semi-transparency so you can
 * still see the game behind it, but it's dimmed and non-interactive.
 * 
 * @param win Reference to the main window
 * @param fnt Reference to the shared font
 */
PauseScreen::PauseScreen(sf::RenderWindow& win, sf::Font& fnt)
    : Screen(win, fnt),
      resumeButton(nullptr),
      mainMenuButton(nullptr),
      quitButton(nullptr),
      confirmYesButton(nullptr),
      confirmNoButton(nullptr),
      showQuitDialog(false) {
    
    std::cout << "[PauseScreen] Constructor called" << std::endl;
    
    // Set up the semi-transparent overlay
    // This creates a darkened effect over the game
    overlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setPosition(0, 0);
    overlay.setFillColor(sf::Color(0, 0, 0, 150)); // Black with 150/255 opacity
    
    // Set up the "PAUSED" title text
    pausedText.setFont(font);
    pausedText.setString("PAUSED");
    pausedText.setCharacterSize(80);
    pausedText.setFillColor(sf::Color::Yellow);
    pausedText.setPosition(
        (window.getSize().x - pausedText.getLocalBounds().width) / 2,
        50
    );
}

/**
 * @brief Destructor - clean up resources
 */
PauseScreen::~PauseScreen() {
    std::cout << "[PauseScreen] Destructor called" << std::endl;
    cleanup();
}

/**
 * @brief Initialize - create all buttons for this screen
 * 
 * Creates 3 pause menu buttons and 2 quit confirmation buttons.
 * The buttons are positioned in the center of the screen.
 * 
 * Button constructor signature:
 * Button(std::string label, sf::Vector2f position, sf::Vector2f size, sf::Color color)
 * 
 * Then we can set text colors with:
 * - setColorTextNormal()
 * - setColorTextHover()
 * 
 * Button layout:
 * - Resume Game (green) - top
 * - Main Menu (yellow) - middle
 * - Quit (red) - bottom
 * - Yes/No confirmation buttons (below main buttons)
 */
void PauseScreen::initialize() {
    std::cout << "[PauseScreen] initialize() called" << std::endl;
    
    float winWidth = window.getSize().x;
    float winHeight = window.getSize().y;
    
    // Button dimensions and spacing
    float buttonWidth =  winWidth * 0.36f;;
    float buttonHeight =  winHeight * 0.09f;
    float spacing = winHeight * 0.07f;
    
    // Center buttons horizontally
    float centerX = (winWidth * 0.5f);
    
    // Calculate vertical position to center all buttons
    float totalHeight = (buttonHeight + spacing) * 3; // 3 buttons
    float startY = (winHeight - totalHeight) / 2+100;
    
    // Create RESUME button
    // Constructor: Button(label, position, size, color)
    resumeButton = new Button(
        "Resume Game",
        sf::Vector2f(centerX, startY),
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Color::Green
    );
    // Set text color for normal and hover states
    resumeButton->setColorTextNormal(sf::Color::Black);
    resumeButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[PauseScreen] Created Resume button" << std::endl;
    
    // Create MAIN MENU button
    // Middle button - abandons current game
    mainMenuButton = new Button(
        "Main Menu",
        sf::Vector2f(centerX, startY + (buttonHeight + spacing)),
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Color::Yellow
    );
    mainMenuButton->setColorTextNormal(sf::Color::Black);
    mainMenuButton->setColorTextHover(sf::Color::Green);
    std::cout << "[PauseScreen] Created Main Menu button" << std::endl;
    
    // Create QUIT button
    // Bottom button - exit game (red for danger)
    quitButton = new Button(
        "Quit",
        sf::Vector2f(centerX, startY + 2 * (buttonHeight + spacing)),
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Color::Red
    );
    quitButton->setColorTextNormal(sf::Color::Black);
    quitButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[PauseScreen] Created Quit button" << std::endl;
    
    // Create quit confirmation dialog buttons (YES and NO)
    float confirmStartY = startY + 3 * (buttonHeight + spacing) + spacing - 190;
    float confirmButtonWidth = 120;
    float confirmSpacing = 130;
    float confirmCenterX = (winWidth - (confirmButtonWidth + confirmSpacing)) / 2;
    
    // YES button - left side
    confirmYesButton = new Button(
        "Yes",
        sf::Vector2f(confirmCenterX, confirmStartY),
        sf::Vector2f(confirmButtonWidth, buttonHeight),
        sf::Color::Green
    );
    confirmYesButton->setColorTextNormal(sf::Color::Black);
    confirmYesButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[PauseScreen] Created Confirm Yes button" << std::endl;
    
    // NO button - right side
    confirmNoButton = new Button(
        "No",
        sf::Vector2f(confirmCenterX + confirmButtonWidth + confirmSpacing, confirmStartY),
        sf::Vector2f(confirmButtonWidth, buttonHeight),
        sf::Color::Red
    );
    confirmNoButton->setColorTextNormal(sf::Color::Black);
    confirmNoButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[PauseScreen] Created Confirm No button" << std::endl;
}

/**
 * @brief Update - process events and return next state
 * 
 * If quit dialog is showing, only Yes/No buttons respond.
 * Otherwise, the three pause menu buttons are active.
 * 
 * Note: Button::update() takes (sf::Event&, sf::RenderWindow&)
 * 
 * Return states:
 * - PLAYING: Continue game (Resume clicked)
 * - MENU: Return to main menu (Main Menu clicked)
 * - PAUSED: Stay paused (No clicked, or no button clicked)
 * - Window closes if Yes clicked
 * 
 * @param event The SFML event to process
 * @return Next state to transition to
 */
GameState PauseScreen::update(sf::Event& event) {
    // Check if quit confirmation dialog is showing
    if (showQuitDialog) {
        // Dialog is active, only Yes/No buttons work
        
        if (confirmYesButton != nullptr) {
            confirmYesButton->update(event, window);
            if (confirmYesButton->getState() == clicked) {
                std::cout << "[PauseScreen] Quit confirmed" << std::endl;
                window.close();
                return GameState::PAUSED; // Won't matter, window closed
            }
        }
        
        if (confirmNoButton != nullptr) {
            confirmNoButton->update(event, window);
            if (confirmNoButton->getState() == clicked) {
                std::cout << "[PauseScreen] Quit cancelled" << std::endl;
                showQuitDialog = false;
                return GameState::PAUSED;
            }
        }
        
        return GameState::PAUSED;
    }
    
    // Dialog is NOT showing, update main pause menu buttons
    
    // Update RESUME button
    if (resumeButton != nullptr) {
        resumeButton->update(event, window);
        if (resumeButton->getState() == clicked) {
            std::cout << "[PauseScreen] Resume clicked - returning to gameplay" << std::endl;
            return GameState::PLAYING;
        }
    }
    
    // Update MAIN MENU button
    if (mainMenuButton != nullptr) {
        mainMenuButton->update(event, window);
        if (mainMenuButton->getState() == clicked) {
            std::cout << "[PauseScreen] Main Menu clicked - transitioning to menu" << std::endl;
            return GameState::MENU;
        }
    }
    
    // Update QUIT button
    if (quitButton != nullptr) {
        quitButton->update(event, window);
        if (quitButton->getState() == clicked) {
            std::cout << "[PauseScreen] Quit clicked - showing confirmation" << std::endl;
            showQuitDialog = true;
            return GameState::PAUSED;
        }
    }
    
    // No button clicked, stay paused
    return GameState::PAUSED;
}

/**
 * @brief Render - draw the pause screen
 * 
 * Drawing order:
 * 1. Semi-transparent overlay (dims the game)
 * 2. "PAUSED" title
 * 3. Pause menu buttons
 * 4. Quit confirmation dialog (if showing)
 */
void PauseScreen::render() {
    // Draw semi-transparent overlay to dim the game
    window.draw(overlay);
    
    // Draw the "PAUSED" title
    window.draw(pausedText);
    
    // Draw the three pause menu buttons
    if (resumeButton != nullptr) {
        window.draw(*resumeButton);
    }
    if (mainMenuButton != nullptr) {
        window.draw(*mainMenuButton);
    }
    if (quitButton != nullptr) {
        window.draw(*quitButton);
    }
    
    // If quit dialog is showing, draw it on top
    if (showQuitDialog) {
        renderQuitDialog();
    }
}

/**
 * @brief Render the quit confirmation dialog
 * 
 * Draws a dialog box with Yes/No buttons asking for quit confirmation.
 * Appears on top of everything else.
 */
void PauseScreen::renderQuitDialog() {
    float winWidth = 1200;
    float winHeight = 800;
    
    // Create and draw darker overlay for the dialog
    sf::RectangleShape dialogOverlay(sf::Vector2f(winWidth, winHeight));
    dialogOverlay.setPosition(0, 0);
    dialogOverlay.setFillColor(sf::Color(0, 0, 0, 100));
    window.draw(dialogOverlay);
    
    // Create and draw dialog box
    float dialogWidth = 400;
    float dialogHeight = 200;
    float dialogX = (winWidth - dialogWidth) / 2;
    float dialogY = (winHeight - dialogHeight) / 2;
    
    dialogBox.setSize(sf::Vector2f(dialogWidth, dialogHeight));
    dialogBox.setPosition(dialogX, dialogY);
    dialogBox.setFillColor(sf::Color(50, 50, 50));
    window.draw(dialogBox);
    
    // Draw border around dialog
    sf::RectangleShape border(sf::Vector2f(dialogWidth, dialogHeight));
    border.setPosition(dialogX, dialogY);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(3);
    border.setOutlineColor(sf::Color::Red);
    window.draw(border);
    
    // Draw question text
    sf::Text questionText;
    questionText.setFont(font);
    questionText.setString("Really quit?");
    questionText.setCharacterSize(30);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(
        dialogX + (dialogWidth - questionText.getLocalBounds().width) / 2,
        dialogY + 70
    );
    window.draw(questionText);
    
    // Draw Yes/No buttons
    if (confirmYesButton != nullptr) {
        window.draw(*confirmYesButton);
    }
    if (confirmNoButton != nullptr) {
        window.draw(*confirmNoButton);
    }
}

/**
 * @brief Cleanup - delete all buttons and reset state
 * 
 * Called when transitioning away from this screen.
 * Properly deletes all allocated buttons and resets dialog state.
 */
void PauseScreen::cleanup() {
    std::cout << "[PauseScreen] cleanup() called" << std::endl;
    
    if (resumeButton != nullptr) {
        delete resumeButton;
        resumeButton = nullptr;
    }
    
    if (mainMenuButton != nullptr) {
        delete mainMenuButton;
        mainMenuButton = nullptr;
    }
    
    if (quitButton != nullptr) {
        delete quitButton;
        quitButton = nullptr;
    }
    
    if (confirmYesButton != nullptr) {
        delete confirmYesButton;
        confirmYesButton = nullptr;
    }
    
    if (confirmNoButton != nullptr) {
        delete confirmNoButton;
        confirmNoButton = nullptr;
    }
    
    // Reset dialog state
    showQuitDialog = false;
    
    std::cout << "[PauseScreen] All buttons deleted" << std::endl;
}