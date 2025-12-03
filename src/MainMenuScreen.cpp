/**
 * @file MainMenuScreen.cpp
 * @author Ian Codding II
 * @brief Implementation of MainMenuScreen - main menu interface
 * @version 1.0
 * @date 2025-10-27
 * 
 * @copyright Copyright (c) 2025
 */

#include "../includes/MainMenuScreen.h"
#include "../includes/errorHandler.h"
#include <iostream>

/**
 * @brief Constructor - initialize the main menu screen
 * 
 * This sets up the initial state but doesn't create buttons yet.
 * Button creation happens in initialize() because SFML objects need
 * the OpenGL context to be ready.
 * 
 * We:
 * 1. Call parent constructor which stores window and font references
 * 2. Initialize all button pointers to nullptr (safe default)
 * 3. Set showQuitDialog to false (dialog not visible initially)
 * 4. Set up the background rectangle
 * 5. Set up the title text
 * 
 * @param win Reference to the main window
 * @param fnt Reference to the shared font
 */
MainMenuScreen::MainMenuScreen(sf::RenderWindow& win, sf::Font& fnt)
    : Screen(win, fnt),
      startButton(nullptr),
      leaderboardButton(nullptr),
      settingsButton(nullptr),
      quitButton(nullptr),
      confirmYesButton(nullptr),
      confirmNoButton(nullptr),
      showQuitDialog(false) {
    
    std::cout << "[MainMenuScreen] Constructor called" << std::endl;
    
    // Set up the black background that covers the entire screen
    // The background fills the entire window
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);
    
    // Set up the semi-transparent dialog overlay
    // This appears behind the quit confirmation dialog to dim the background
    dialogOverlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    dialogOverlay.setPosition(0, 0);
    dialogOverlay.setFillColor(sf::Color(0, 0, 0, 200)); // Black with 200/255 opacity
    
    // Set up the title text
    titleText.setFont(font);
    titleText.setString("CENTIPEDE");
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::Green);
    
    // Center the title horizontally and position it near the top
    titleText.setPosition(
        (1200 - titleText.getLocalBounds().width) / 2,
        25
    );
}

/**
 * @brief Destructor - clean up resources
 * 
 * Calls cleanup() to ensure all buttons are deleted.
 * We use the destructor to guarantee cleanup happens even if
 * someone forgets to call cleanup() manually.
 */
MainMenuScreen::~MainMenuScreen() {
    std::cout << "[MainMenuScreen] Destructor called" << std::endl;
    cleanup();
}

/**
 * @brief Initialize - create all buttons for this screen
 * 
 * This is called once when the screen is first created or switched to.
 * Creates the 4 main menu buttons and 2 quit confirmation buttons.
 * 
 * Button constructor signature:
 * Button(std::string label, sf::Vector2f position, sf::Vector2f size, sf::Color color)
 * 
 * Then we can set text colors with:
 * - setColorTextNormal()
 * - setColorTextHover()
 * 
 * Button layout:
 * - Title at top: "CENTIPEDE"
 * - Start Game button (green, top)
 * - Leaderboard button
 * - Settings button
 * - Quit button (red, bottom)
 * - Below: Yes/No buttons for quit confirmation (hidden initially)
 * 
 * Button positioning uses the window size so buttons are centered
 * and scale with different window sizes.
 */
void MainMenuScreen::initialize() {
    std::cout << "[MainMenuScreen] initialize() called" << std::endl;
    
    // Get window dimensions for positioning
    float winWidth = 1200;
    float winHeight = 800;
    
    // Proportional button sizing
    float buttonWidth = winWidth * 0.36f;      // 36% of window width
    float buttonHeight = winHeight * 0.09f;    // 9% of window height
    float spacing = winHeight * 0.07f;         // 7% vertical spacing
    float centerX = (winWidth - buttonWidth) / 2-148;
    
    // Calculate the starting Y position (center buttons vertically)
    float totalHeight = (buttonHeight + spacing) * 4; // 4 buttons
    float startY = (winHeight - totalHeight) / 2+100;
    
    // Create START GAME button
    // Position: centered horizontally, upper portion of buttons
    // Constructor: Button(label, position, size, color)
    startButton = new Button(
        "Start Game",
        sf::Vector2f(centerX, startY),
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Color::Blue
    );
    startButton->setColorTextNormal(sf::Color::Black);
    startButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[MainMenuScreen] Created Start button" << std::endl;
    
    // Create LEADERBOARD button
    // Position: below Start button with spacing
    leaderboardButton = new Button(
        "Leaderboard",
        sf::Vector2f(centerX, startY + (buttonHeight + spacing)),
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Color::Green
    );
    leaderboardButton->setColorTextNormal(sf::Color::Black);
    leaderboardButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[MainMenuScreen] Created Leaderboard button" << std::endl;
    
    // Create SETTINGS button
    // Position: below Leaderboard button
    settingsButton = new Button(
        "Settings",
        sf::Vector2f(centerX, startY + 2 * (buttonHeight + spacing)),
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Color::Green
    );
    settingsButton->setColorTextNormal(sf::Color::Black);
    settingsButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[MainMenuScreen] Created Settings button" << std::endl;
    
    // Create QUIT button
    // Position: at bottom of main buttons (red to indicate danger)
    quitButton = new Button(
        "Quit",
        {sf::Vector2f(centerX, startY + 3 * (buttonHeight + spacing))},
        sf::Vector2f(buttonWidth, buttonHeight),
        sf::Color::Red
    );
    quitButton->setColorTextNormal(sf::Color::Black);
    quitButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[MainMenuScreen] Created Quit button" << std::endl;
    
    // Create quit confirmation dialog buttons
    float confirmStartY = startY + 2*(buttonHeight + spacing) + spacing;
    float confirmButtonWidth = buttonWidth * 0.4f;
    float confirmSpacing = buttonWidth * 0.1f;
    float confirmCenterX = (winWidth - (confirmButtonWidth * 2 + confirmSpacing)) / 2;

    std::cout << "[MainMenuScreen] Dimensions fo quit confirmation: " << confirmStartY << " " << confirmButtonWidth << " " << confirmSpacing << " " 
        << confirmCenterX << " " << buttonHeight <<std::endl;
    
    // YES button - left side of confirmation dialog
    confirmYesButton = new Button(
        "Yes",
        sf::Vector2f(confirmCenterX, confirmStartY),
        sf::Vector2f(confirmButtonWidth, buttonHeight),
        sf::Color::Green
    );
    confirmYesButton->setColorTextNormal(sf::Color::Black);
    confirmYesButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[MainMenuScreen] Created Confirm Yes button" << std::endl;
    
    // NO button - right side of confirmation dialog
    confirmNoButton = new Button(
        "No",
        sf::Vector2f(confirmCenterX + 2*confirmButtonWidth + confirmSpacing, confirmStartY),
        sf::Vector2f(confirmButtonWidth, buttonHeight),
        sf::Color::Red
    );
    confirmNoButton->setColorTextNormal(sf::Color::Black);
    confirmNoButton->setColorTextHover(sf::Color::Yellow);
    std::cout << "[MainMenuScreen] Created Confirm No button" << std::endl;
}

/**
 * @brief Update - process events and return next state
 * 
 * Called every frame with each event that occurred.
 * Updates buttons and checks for clicks.
 * Returns the appropriate state based on which button was clicked.
 * 
 * If quit dialog is showing, only the Yes/No confirmation buttons work.
 * Otherwise, the main 4 buttons are active.
 * 
 * Note: Button::update() takes (sf::Event&, sf::RenderWindow&)
 * Note: Button::getState() returns: normal, hovered, or clicked
 * 
 * @param event The SFML event to process
 * @return The next state to transition to (or current state to stay)
 */
GameState MainMenuScreen::update(sf::Event& event) {
    // Check if quit confirmation dialog is showing
    if (showQuitDialog) {
        // Dialog is active, so only Yes/No buttons should work
        
        // Update the Yes button and check if clicked
        if (confirmYesButton != nullptr) {
            confirmYesButton->update(event, window);
            if (confirmYesButton->getState() == clicked) {
                std::cout << "[MainMenuScreen] Quit confirmed - closing window" << std::endl;
                window.close();
                return GameState::MENU; // Won't matter, window is closed
            }
        }
        
        // Update the No button and check if clicked
        if (confirmNoButton != nullptr) {
            confirmNoButton->update(event, window);
            if (confirmNoButton->getState() == clicked) {
                std::cout << "[MainMenuScreen] Quit cancelled" << std::endl;
                showQuitDialog = false; // Hide dialog, stay in menu
                return GameState::MENU;
            }
        }
        
        // If we got here, no button was clicked while dialog is open
        return GameState::MENU;
    }
    
    // Dialog is NOT showing, so update the main menu buttons
    
    // Update START GAME button
    if (startButton != nullptr) {
        startButton->update(event, window);
        if (startButton->getState() == clicked) {
            std::cout << "[MainMenuScreen] Start Game clicked - transitioning to PLAYING" << std::endl;
            return GameState::PLAYING;
        }
    }
    
    // Update LEADERBOARD button
    if (leaderboardButton != nullptr) {
        leaderboardButton->update(event, window);
        if (leaderboardButton->getState() == clicked) {
            std::cout << "[MainMenuScreen] Leaderboard clicked" << std::endl;
            return GameState::LEADERBOARD;
        }
    }
    
    // Update SETTINGS button
    if (settingsButton != nullptr) {
        settingsButton->update(event, window);
        if (settingsButton->getState() == clicked) {
            std::cout << "[MainMenuScreen] Settings clicked" << std::endl;
            return GameState::SETTINGS;
        }
    }
    
    // Update QUIT button
    if (quitButton != nullptr) {
        quitButton->update(event, window);
        if (quitButton->getState() == clicked) {
            std::cout << "[MainMenuScreen] Quit clicked - showing confirmation dialog" << std::endl;
            showQuitDialog = true; // Show the confirmation dialog
            return GameState::MENU; // Stay in menu
        }
    }
    
    // No button was clicked, stay in MENU
    return GameState::MENU;
}

/**
 * @brief Render - draw the main menu screen
 * 
 * Called every frame to draw all UI elements.
 * Drawing order matters - things drawn first appear behind things drawn later.
 * 
 * Draw order:
 * 1. Background (black rectangle - appears behind everything)
 * 2. Title text
 * 3. Main menu buttons
 * 4. Quit confirmation dialog (if showing)
 */
void MainMenuScreen::render() {
    // Draw the black background
    // This covers the entire screen and makes the UI visible
    window.draw(background);
    
    // Draw the title
    window.draw(titleText);
    
    // Draw the 4 main menu buttons
    // sf::Drawable objects are drawn using window.draw()
    if (startButton != nullptr) {
        window.draw(*startButton);
    }
    if (leaderboardButton != nullptr) {
        window.draw(*leaderboardButton);
    }
    if (settingsButton != nullptr) {
        window.draw(*settingsButton);
    }
    if (quitButton != nullptr) {
        window.draw(*quitButton);
    }
    
    // If quit dialog is showing, draw it on top
    // This will appear above all other UI elements
    if (showQuitDialog) {
        renderQuitDialog();
    }
}

/**
 * @brief Render the quit confirmation dialog
 * 
 * This is a separate function because the dialog is only drawn when active.
 * It draws:
 * 1. Semi-transparent overlay to dim the background
 * 2. Dialog box (darker rectangle)
 * 3. Question text ("Are you sure?")
 * 4. Yes/No buttons
 * 
 * This creates a "modal" effect - the dialog blocks interaction with
 * the menu until the user clicks Yes or No.
 */
void MainMenuScreen::renderQuitDialog() {
    // Draw semi-transparent overlay to dim the background
    // This makes it clear the dialog is the focus
    window.draw(dialogOverlay);
    
    // Create and draw the dialog box (darker rectangle in center)
    float dialogWidth = 480; // winWidth * 0.4f;
    float dialogHeight = 200; // winHeight * 0.25f;
    float dialogX = 360; // (winWidth - dialogWidth) / 2;
    float dialogY = 300; // (winHeight - dialogHeight) / 2;
    
    sf::RectangleShape dialogBox(sf::Vector2f(dialogWidth, dialogHeight));
    dialogBox.setPosition(dialogX, dialogY);
    dialogBox.setFillColor(sf::Color(50, 50, 50)); // Dark gray
    window.draw(dialogBox);
    
    // Draw border around dialog box
    sf::RectangleShape dialogBorder(sf::Vector2f(dialogWidth, dialogHeight));
    dialogBorder.setPosition(dialogX, dialogY);
    dialogBorder.setFillColor(sf::Color::Transparent);
    dialogBorder.setOutlineThickness(3);
    dialogBorder.setOutlineColor(sf::Color::Red);
    window.draw(dialogBorder);
    
    // Create and draw the question text
    sf::Text questionText;
    questionText.setFont(font);
    questionText.setString("\n   Are you sure\nyou want to quit?");
    questionText.setCharacterSize(27);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(
       dialogX + (dialogWidth - questionText.getLocalBounds().width) / 2,
        dialogY + dialogHeight * 0.15f
    );
    window.draw(questionText);
    
    // Draw the Yes/No buttons
    if (confirmYesButton != nullptr) {
        window.draw(*confirmYesButton);
    }
    if (confirmNoButton != nullptr) {
        window.draw(*confirmNoButton);
    }
}

/**
 * @brief Cleanup - delete all buttons
 * 
 * Called when transitioning away from this screen.
 * Deletes all button objects to free their memory.
 * 
 * After this is called, all button pointers are set to nullptr.
 * This is important because:
 * 1. Prevents memory leaks
 * 2. Prevents accessing deleted buttons
 * 3. If we return to this screen, initialize() will create new buttons
 */
void MainMenuScreen::cleanup() {
    std::cout << "[MainMenuScreen] cleanup() called" << std::endl;
    
    // Delete each button if it exists
    if (startButton != nullptr) {
        delete startButton;
        startButton = nullptr;
    }
    
    if (leaderboardButton != nullptr) {
        delete leaderboardButton;
        leaderboardButton = nullptr;
    }
    
    if (settingsButton != nullptr) {
        delete settingsButton;
        settingsButton = nullptr;
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
    
    std::cout << "[MainMenuScreen] All buttons deleted" << std::endl;
}