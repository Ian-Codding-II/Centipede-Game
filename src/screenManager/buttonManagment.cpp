#include "../../includes/screenManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>

// ============================================================================
// BUTTON CREATION METHODS
// These create dynamically allocated buttons using 'new'
// Each button must be deleted later to prevent memory leaks
// ============================================================================

/**
 * @brief Create main menu buttons
 * 
 * Creates 4 buttons for the main menu:
 * - Start Game: Begins gameplay
 * - Leaderboard: Shows high scores
 * - Settings: Configure game options
 * - Quit: Exit program (with confirmation)
 * 
 * Buttons are positioned down the left side of the screen.
 */
void ScreenManager::createMainMenuButtons() {
    std::cout << "[DEBUG] Creating main menu buttons..." << std::endl;
    
    // Create Start Game button
    // Position {200, 250} means X=200, Y=250 (center of button)
    // Size {200, 60} means width=200, height=60
    startButton = new Button("Start Game", {200, 250}, {200, 60}, sf::Color::White);
    startButton->setColorTextNormal(sf::Color::Green);   // Text color when not hovered
    startButton->setColorTextHover(sf::Color::Yellow);   // Text color when hovering
    
    // Create Leaderboard button
    leaderboardButton = new Button("Leaderboard", {200, 330}, {200, 60}, sf::Color::White);
    leaderboardButton->setColorTextNormal(sf::Color::Green);
    leaderboardButton->setColorTextHover(sf::Color::Yellow);
    
    // Create Settings button
    settingsButton = new Button("Settings", {200, 410}, {200, 60}, sf::Color::White);
    settingsButton->setColorTextNormal(sf::Color::Green);
    settingsButton->setColorTextHover(sf::Color::Yellow);
    
    // Create Quit button (red on hover to indicate danger)
    quitButton = new Button("Quit", {200, 490}, {200, 60}, sf::Color::White);
    quitButton->setColorTextNormal(sf::Color::Green);
    quitButton->setColorTextHover(sf::Color::Red);  // Red to show it's destructive
    
    std::cout << "[DEBUG] Main menu buttons created" << std::endl;
}

/**
 * @brief Create pause menu buttons
 * 
 * Creates 3 buttons shown on the right side during pause:
 * - Resume: Return to gameplay
 * - Main Menu: Abandon game and return to menu
 * - Quit: Exit program
 * 
 * These are positioned on the right side (X=700) to not obscure the frozen game.
 */
void ScreenManager::createPauseMenuButtons() {
    std::cout << "[DEBUG] Creating pause menu buttons..." << std::endl;
    
    resumeButton = new Button("Resume", {700, 150}, {150, 50}, sf::Color::White);
    resumeButton->setColorTextNormal(sf::Color::Green);
    resumeButton->setColorTextHover(sf::Color::Yellow);
    
    mainMenuButton = new Button("Main Menu", {700, 220}, {150, 50}, sf::Color::White);
    mainMenuButton->setColorTextNormal(sf::Color::Green);
    mainMenuButton->setColorTextHover(sf::Color::Yellow);
    
    quitFromPauseButton = new Button("Quit", {700, 290}, {150, 50}, sf::Color::White);
    quitFromPauseButton->setColorTextNormal(sf::Color::Green);
    quitFromPauseButton->setColorTextHover(sf::Color::Red);
    
    std::cout << "[DEBUG] Pause menu buttons created" << std::endl;
}

/**
 * @brief Create settings screen buttons
 * 
 * Creates buttons for adjusting game settings:
 * - +/- buttons for lives (1-5)
 * - +/- buttons for spawn level (0+)
 * - Icon selection buttons (4 player icons)
 * - Back button to return to menu
 */
void ScreenManager::createSettingsButtons() {
    std::cout << "[DEBUG] Creating settings buttons..." << std::endl;
    
    // Back button (bottom of screen)
    backButton = new Button("Back", {400, 500}, {150, 50}, sf::Color::White);
    backButton->setColorTextNormal(sf::Color::Green);
    backButton->setColorTextHover(sf::Color::Yellow);
    
    // Lives adjustment buttons (small +/- buttons)
    livesUpButton = new Button("+", {500, 200}, {40, 40}, sf::Color::White);
    livesUpButton->setColorTextNormal(sf::Color::Green);
    livesUpButton->setColorTextHover(sf::Color::Yellow);
    
    livesDownButton = new Button("-", {300, 200}, {40, 40}, sf::Color::White);
    livesDownButton->setColorTextNormal(sf::Color::Green);
    livesDownButton->setColorTextHover(sf::Color::Yellow);
    
    // Level adjustment buttons
    levelUpButton = new Button("+", {500, 260}, {40, 40}, sf::Color::White);
    levelUpButton->setColorTextNormal(sf::Color::Green);
    levelUpButton->setColorTextHover(sf::Color::Yellow);
    
    levelDownButton = new Button("-", {300, 260}, {40, 40}, sf::Color::White);
    levelDownButton->setColorTextNormal(sf::Color::Green);
    levelDownButton->setColorTextHover(sf::Color::Yellow);
    
    // Create 4 player icon selection buttons
    // They're spaced 80 pixels apart horizontally
    for (int i = 0; i < 4; i++) {
        Button* iconButton = new Button(
            std::to_string(i + 1),                    // Label: "1", "2", "3", "4"
            {250.0f + i * 80.0f, 350},                // Position: spread across screen
            {60, 60},                                  // Size: 60x60 square
            sf::Color::White
        );
        iconButton->setColorTextNormal(sf::Color::Green);
        iconButton->setColorTextHover(sf::Color::Yellow);
        playerIconButtons.push_back(iconButton);       // Add to vector
    }
    
    std::cout << "[DEBUG] Settings buttons created" << std::endl;
}

/**
 * @brief Create game over screen buttons
 * 
 * Creates 2 buttons shown after game ends:
 * - Play Again: Start a new game
 * - Main Menu: Return to main menu
 */
void ScreenManager::createGameOverButtons() {
    std::cout << "[DEBUG] Creating game over buttons..." << std::endl;
    
    playAgainButton = new Button("Play Again", {400, 350}, {200, 60}, sf::Color::White);
    playAgainButton->setColorTextNormal(sf::Color::Green);
    playAgainButton->setColorTextHover(sf::Color::Yellow);
    
    mainMenuFromGameOverButton = new Button("Main Menu", {400, 430}, {200, 60}, sf::Color::White);
    mainMenuFromGameOverButton->setColorTextNormal(sf::Color::Green);
    mainMenuFromGameOverButton->setColorTextHover(sf::Color::Yellow);
    
    std::cout << "[DEBUG] Game over buttons created" << std::endl;
}

/**
 * @brief Create quit confirmation dialog buttons
 * 
 * Creates the Yes/No buttons for the quit confirmation dialog.
 * CRITICAL: These are created ONCE in initialize() and NEVER deleted.
 * They're reused whenever the quit confirmation dialog appears.
 * 
 * This prevents the segfault that was happening when transitioning states.
 */
void ScreenManager::createQuitConfirmButtons() {
    std::cout << "[DEBUG] Creating quit confirmation buttons..." << std::endl;
    
    // Only create if they don't already exist
    // This prevents memory leaks from creating them multiple times
    if (confirmYesButton != nullptr || confirmNoButton != nullptr) {
        std::cout << "[WARNING] Quit confirmation buttons already exist, skipping creation" << std::endl;
        return;
    }
    
    // Yes button (left side of dialog)
    confirmYesButton = new Button("Yes", {340, 350}, {100, 50}, sf::Color::White);
    confirmYesButton->setColorTextNormal(sf::Color::Green);
    confirmYesButton->setColorTextHover(sf::Color::Red);  // Red to show danger
    
    // No button (right side of dialog)
    confirmNoButton = new Button("No", {460, 350}, {100, 50}, sf::Color::White);
    confirmNoButton->setColorTextNormal(sf::Color::Green);
    confirmNoButton->setColorTextHover(sf::Color::Yellow);
    
    std::cout << "[DEBUG] Quit confirmation buttons created" << std::endl;
}

// ============================================================================
// BUTTON DELETION METHODS
// These free memory used by buttons
// CRITICAL: Always set pointers to nullptr after deleting to prevent
// "double delete" errors (deleting the same memory twice)
// ============================================================================

/**
 * @brief Delete main menu buttons
 * 
 * Frees memory used by the 4 main menu buttons.
 * After deleting, we set pointers to nullptr so we can safely check
 * if buttons exist before using them.
 */
void ScreenManager::deleteMainMenuButtons() {
    std::cout << "[DEBUG] Deleting main menu buttons..." << std::endl;
    
    // For each button: delete it, then set pointer to nullptr
    // The nullptr check prevents "use after delete" bugs
    if (startButton) {
        delete startButton;
        startButton = nullptr;
    }
    if (leaderboardButton) {
        delete leaderboardButton;
        leaderboardButton = nullptr;
    }
    if (settingsButton) {
        delete settingsButton;
        settingsButton = nullptr;
    }
    if (quitButton) {
        delete quitButton;
        quitButton = nullptr;
    }
    
    std::cout << "[DEBUG] Main menu buttons deleted" << std::endl;
}

/**
 * @brief Delete pause menu buttons
 */
void ScreenManager::deletePauseMenuButtons() {
    std::cout << "[DEBUG] Deleting pause menu buttons..." << std::endl;
    
    if (resumeButton) {
        delete resumeButton;
        resumeButton = nullptr;
    }
    if (mainMenuButton) {
        delete mainMenuButton;
        mainMenuButton = nullptr;
    }
    if (quitFromPauseButton) {
        delete quitFromPauseButton;
        quitFromPauseButton = nullptr;
    }
    
    std::cout << "[DEBUG] Pause menu buttons deleted" << std::endl;
}

/**
 * @brief Delete settings buttons
 * 
 * Also deletes all player icon buttons from the vector.
 * We iterate through the vector and delete each button individually.
 */
void ScreenManager::deleteSettingsButtons() {
    std::cout << "[DEBUG] Deleting settings buttons..." << std::endl;
    
    if (backButton) {
        delete backButton;
        backButton = nullptr;
    }
    if (livesUpButton) {
        delete livesUpButton;
        livesUpButton = nullptr;
    }
    if (livesDownButton) {
        delete livesDownButton;
        livesDownButton = nullptr;
    }
    if (levelUpButton) {
        delete levelUpButton;
        levelUpButton = nullptr;
    }
    if (levelDownButton) {
        delete levelDownButton;
        levelDownButton = nullptr;
    }
    
    // Delete all player icon buttons
    // We must delete each button in the vector individually
    for (size_t i = 0; i < playerIconButtons.size(); i++) {
        if (playerIconButtons[i]) {
            delete playerIconButtons[i];
            // Don't need to set to nullptr since we're clearing the vector
        }
    }
    // Clear the vector (removes all elements)
    playerIconButtons.clear();
    
    std::cout << "[DEBUG] Settings buttons deleted" << std::endl;
}

/**
 * @brief Delete game over buttons
 */
void ScreenManager::deleteGameOverButtons() {
    std::cout << "[DEBUG] Deleting game over buttons..." << std::endl;
    
    if (playAgainButton) {
        delete playAgainButton;
        playAgainButton = nullptr;
    }
    if (mainMenuFromGameOverButton) {
        delete mainMenuFromGameOverButton;
        mainMenuFromGameOverButton = nullptr;
    }
    
    std::cout << "[DEBUG] Game over buttons deleted" << std::endl;
}

/**
 * @brief Delete quit confirmation buttons
 * 
 * IMPORTANT: This should ONLY be called in the destructor.
 * During normal state transitions, these buttons are kept alive.
 */
void ScreenManager::deleteQuitConfirmButtons() {
    std::cout << "[DEBUG] Deleting quit confirmation buttons..." << std::endl;
    
    if (confirmYesButton) {
        delete confirmYesButton;
        confirmYesButton = nullptr;
    }
    if (confirmNoButton) {
        delete confirmNoButton;
        confirmNoButton = nullptr;
    }
    
    std::cout << "[DEBUG] Quit confirmation buttons deleted" << std::endl;
}

/**
 * @brief Delete ALL buttons
 * 
 * Called by the destructor to clean up all memory before program ends.
 * Calls all the individual delete functions to ensure nothing is leaked.
 */
void ScreenManager::deleteAllButtons() {
    std::cout << "[DEBUG] Deleting all buttons..." << std::endl;
    
    // Delete buttons from all states
    deleteMainMenuButtons();
    deletePauseMenuButtons();
    deleteSettingsButtons();
    deleteGameOverButtons();
    deleteQuitConfirmButtons();  // Only here, not in setState()!
    
    std::cout << "[DEBUG] All buttons deleted" << std::endl;
}