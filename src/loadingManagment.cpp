
// /**
//  * @file loading.cpp
//  * @author Ian Codding II
//  * @brief This file will handel the resources and regular loading.
//  * @version 0.1
//  * @date 2025-11-05
//  * 
//  * @copyright Copyright (c) 2025
//  * 
//  */
// #include "../includes/screenManager.h"
// #include <iostream>

// /**
//  * @brief Constructor for ScreenManager
//  * 
//  * This initializes the ScreenManager with a reference to the main window.
//  * The window is passed by reference (&) so we're not copying it - we're working
//  * with the SAME window that was created in main.cpp.
//  * 
//  * All button pointers are initialized to nullptr (null) so we can safely check
//  * if they exist before using them. This prevents segfaults from using uninitialized pointers.
//  * 
//  * @param win Reference to the main SFML window
//  */
// ScreenManager::ScreenManager(sf::RenderWindow& win)
//     : window(win),                              // Store reference to the window
//       currentState(GameState::MENU),           // Start in MENU state
//       startButton(nullptr),                     // All buttons start as nullptr
//       leaderboardButton(nullptr),
//       settingsButton(nullptr),
//       quitButton(nullptr),
//       resumeButton(nullptr),
//       mainMenuButton(nullptr),
//       quitFromPauseButton(nullptr),
//       backButton(nullptr),
//       livesUpButton(nullptr),
//       livesDownButton(nullptr),
//       levelUpButton(nullptr),
//       levelDownButton(nullptr),
//       playAgainButton(nullptr),
//       mainMenuFromGameOverButton(nullptr),
//       confirmYesButton(nullptr),
//       confirmNoButton(nullptr),
//       showQuitConfirmation(false),              // Don't show quit dialog yet
//       lives(3),                                 // Default game settings
//       spawnLevel(0),
//       selectedPlayerIcon(0) {
    
//     // Setup the black background that covers the entire window
//     // This is drawn first so everything else appears on top of it
//     background.setSize(sf::Vector2f(800.0f, 600.0f));
//     background.setFillColor(sf::Color::Black);
    
//     // Setup semi-transparent overlay for dialogs
//     // This darkens the screen behind popup dialogs (like quit confirmation)
//     // Alpha value of 180 means it's mostly opaque but you can see through it slightly
//     dialogOverlay.setSize(sf::Vector2f(800.0f, 600.0f));
//     dialogOverlay.setFillColor(sf::Color(0, 0, 0, 180));  // Black with 180/255 opacity
// }

// /**
//  * @brief Destructor for ScreenManager
//  * 
//  * When the ScreenManager is destroyed (program ends), we must delete all
//  * dynamically allocated buttons to prevent memory leaks. If we don't do this,
//  * the memory used by buttons will never be freed.
//  */
// ScreenManager::~ScreenManager() {
//     std::cout << "[DEBUG] ScreenManager destructor called" << std::endl;
//     deleteAllButtons();  // Clean up all button memory
// }

// /**
//  * @brief Initialize the ScreenManager
//  * 
//  * This is called once after construction to set up everything needed:
//  * 1. Load fonts and setup text objects
//  * 2. Load leaderboard data from file
//  * 3. Create the buttons for the main menu (since we start in MENU state)
//  * 
//  * We do this in initialize() instead of the constructor because some operations
//  * require the OpenGL context to be fully ready.
//  */
// void ScreenManager::initialize() {
//     std::cout << "[DEBUG] ScreenManager::initialize() called" << std::endl;
    
//     // Load fonts and textures
//     loadResources();
    
//     // Load saved high scores from disk
//     loadLeaderboard();
    
//     // Create buttons for the initial state (MENU)
//     createMainMenuButtons();
    
//     // CRITICAL FIX: Also create quit confirmation buttons NOW
//     // These are used by multiple states, so we create them once and keep them
//     createQuitConfirmButtons();
    
//     std::cout << "[DEBUG] ScreenManager initialized successfully" << std::endl;
// }

// /**
//  * @brief Load fonts and setup text objects
//  * 
//  * Loads the font file and creates reusable text objects for titles, subtitles,
//  * and info text. If the primary font fails to load, we try a system font as backup.
//  * 
//  * These text objects are reused throughout the program - we just change their
//  * string content and position as needed.
//  */
// void ScreenManager::loadResources() {
//     std::cout << "[DEBUG] Loading resources..." << std::endl;
    
//     // Try to load the game font
//     // This is used for all text in menus
//     if (!font.loadFromFile("assets/fonts/college.ttf")) {
//         std::cerr << "[WARNING] Could not load college.ttf, trying system font" << std::endl;
        
//         // If that fails, try a common system font as fallback
//         // This ensures the game still works even without the custom font
//         if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
//             std::cerr << "[ERROR] Could not load any font!" << std::endl;
//         }
//     } else {
//         std::cout << "[DEBUG] Font loaded successfully" << std::endl;
//     }
    
//     // Setup title text (large text for screen titles)
//     titleText.setFont(font);
//     titleText.setCharacterSize(60);       // Big font for titles
//     titleText.setFillColor(sf::Color::Green);
    
//     // Setup subtitle text (medium text)
//     subtitleText.setFont(font);
//     subtitleText.setCharacterSize(35);
//     subtitleText.setFillColor(sf::Color::Yellow);
    
//     // Setup info text (small text for details)
//     infoText.setFont(font);
//     infoText.setCharacterSize(20);
//     infoText.setFillColor(sf::Color::White);
    
//     std::cout << "[DEBUG] Resources loaded" << std::endl;
// }

// /**
//  * @brief Update function - called every frame for each event
//  * 
//  * This is the heart of the ScreenManager. It processes events (mouse clicks, key presses)
//  * and updates buttons based on the current state.
//  * 
//  * The function checks which state we're in and only updates the buttons that exist
//  * in that state. For example, in MENU state, we update the start/settings/quit buttons,
//  * but in PLAYING state there are no UI buttons to update.
//  * 
//  * IMPORTANT: This must be called INSIDE the event loop in main.cpp, not after it!
//  * 
//  * @param event The SFML event that occurred this frame (mouse move, click, key press, etc.)
//  */
// void ScreenManager::update(sf::Event& event) {
//     // SPECIAL CASE: Quit confirmation dialog takes priority over everything
//     // If the dialog is showing, we only process input for Yes/No buttons
//     // and ignore all other buttons until the dialog is closed
//     if (showQuitConfirmation) {
//         std::cout << "[DEBUG] Quit confirmation showing, only updating Yes/No buttons" << std::endl;
        
//         // Safety check: make sure buttons exist before using them
//         // This prevents segfault if buttons were deleted
//         if (!confirmYesButton || !confirmNoButton) {
//             std::cerr << "[ERROR] Quit confirmation buttons are nullptr!" << std::endl;
//             showQuitConfirmation = false;  // Hide dialog if buttons don't exist
//             return;
//         }
        
//         // Update the two confirmation buttons
//         confirmYesButton->update(event, window);
//         confirmNoButton->update(event, window);
        
//         // Check if Yes was clicked - close the entire program
//         if (confirmYesButton->getState() == clicked) {
//             std::cout << "[DEBUG] YES clicked - closing window" << std::endl;
//             window.close();  // This will end the main loop in main.cpp
//         }
        
//         // Check if No was clicked - hide the dialog and return to previous state
//         if (confirmNoButton->getState() == clicked) {
//             std::cout << "[DEBUG] NO clicked - hiding dialog" << std::endl;
//             showQuitConfirmation = false;
            
//             // Reset button states by setting text to itself
//             // This is a trick that works because setText() recalculates button layout
//             confirmNoButton->setText(confirmNoButton->getText());
//             confirmYesButton->setText(confirmYesButton->getText());
//         }
        
//         // Don't process any other buttons while dialog is showing
//         return;
//     }
    
//     // Process buttons based on current state
//     // Each state has different buttons, so we handle them separately
//     switch (currentState) {
//         case GameState::MENU: {
//             // MAIN MENU STATE
//             // We have 4 buttons: Start, Leaderboard, Settings, Quit
            
//             std::cout << "[DEBUG] Updating MENU state buttons" << std::endl;
            
//             // Safety check: verify all menu buttons exist
//             // If any are nullptr, we can't use them without causing a segfault
//             if (!startButton || !leaderboardButton || !settingsButton || !quitButton) {
//                 std::cerr << "[ERROR] One or more menu buttons are nullptr!" << std::endl;
//                 return;
//             }
            
//             // Update each button with the current event
//             // This allows buttons to detect mouse hovers and clicks
//             startButton->update(event, window);
//             leaderboardButton->update(event, window);
//             settingsButton->update(event, window);
//             quitButton->update(event, window);
            
//             // Check if Start Game was clicked
//             if (startButton->getState() == clicked) {
//                 std::cout << "[DEBUG] Start Game clicked - transitioning to PLAYING" << std::endl;
//                 setState(GameState::PLAYING);
                
//                 // Reset button state so it doesn't stay "clicked" forever
//                 startButton->setText(startButton->getText());
//             }
            
//             // Check if Leaderboard was clicked
//             if (leaderboardButton->getState() == clicked) {
//                 std::cout << "[DEBUG] Leaderboard clicked" << std::endl;
//                 setState(GameState::LEADERBOARD);
//                 leaderboardButton->setText(leaderboardButton->getText());
//             }
            
//             // Check if Settings was clicked
//             if (settingsButton->getState() == clicked) {
//                 std::cout << "[DEBUG] Settings clicked" << std::endl;
//                 setState(GameState::SETTINGS);
//                 settingsButton->setText(settingsButton->getText());
//             }
            
//             // Check if Quit was clicked - show confirmation dialog
//             if (quitButton->getState() == clicked) {
//                 std::cout << "[DEBUG] Quit clicked - showing confirmation" << std::endl;
//                 showQuitConfirmation = true;
//                 quitButton->setText(quitButton->getText());
//             }
//             break;
//         }
            
//         case GameState::PLAYING: {
//             // PLAYING STATE
//             // No UI buttons to update - gameplay is handled by Game class
//             // The pause menu appears when user presses P key (handled in main.cpp)
//             std::cout << "[DEBUG] PLAYING state - no buttons to update" << std::endl;
//             break;
//         }
            
//         case GameState::PAUSED: {
//             // PAUSED STATE
//             // Show pause menu with Resume, Main Menu, and Quit buttons
            
//             std::cout << "[DEBUG] Updating PAUSED state buttons" << std::endl;
            
//             // Safety check for pause menu buttons
//             if (!resumeButton || !mainMenuButton || !quitFromPauseButton) {
//                 std::cerr << "[ERROR] One or more pause buttons are nullptr!" << std::endl;
//                 return;
//             }
            
//             // Update pause menu buttons
//             resumeButton->update(event, window);
//             mainMenuButton->update(event, window);
//             quitFromPauseButton->update(event, window);
            
//             // Check if Resume was clicked - return to gameplay
//             if (resumeButton->getState() == clicked) {
//                 std::cout << "[DEBUG] Resume clicked - returning to PLAYING" << std::endl;
//                 setState(GameState::PLAYING);
//                 resumeButton->setText(resumeButton->getText());
//             }
            
//             // Check if Main Menu was clicked - abandon game and return to menu
//             if (mainMenuButton->getState() == clicked) {
//                 std::cout << "[DEBUG] Main Menu clicked from pause" << std::endl;
//                 setState(GameState::MENU);
//                 mainMenuButton->setText(mainMenuButton->getText());
//             }
            
//             // Check if Quit was clicked - show confirmation
//             if (quitFromPauseButton->getState() == clicked) {
//                 std::cout << "[DEBUG] Quit clicked from pause" << std::endl;
//                 showQuitConfirmation = true;
//                 quitFromPauseButton->setText(quitFromPauseButton->getText());
//             }
//             break;
//         }
            
//         case GameState::SETTINGS: {
//             // SETTINGS STATE
//             // Allow player to adjust lives, spawn level, and select player icon
            
//             std::cout << "[DEBUG] Updating SETTINGS state buttons" << std::endl;
            
//             // Safety checks for settings buttons
//             if (!backButton || !livesUpButton || !livesDownButton || 
//                 !levelUpButton || !levelDownButton) {
//                 std::cerr << "[ERROR] One or more settings buttons are nullptr!" << std::endl;
//                 return;
//             }
            
//             // Update all settings buttons
//             backButton->update(event, window);
//             livesUpButton->update(event, window);
//             livesDownButton->update(event, window);
//             levelUpButton->update(event, window);
//             levelDownButton->update(event, window);
            
//             // Update player icon selection buttons
//             for (size_t i = 0; i < playerIconButtons.size(); i++) {
//                 if (playerIconButtons[i]) {
//                     playerIconButtons[i]->update(event, window);
                    
//                     // If this icon button was clicked, select it
//                     if (playerIconButtons[i]->getState() == clicked) {
//                         std::cout << "[DEBUG] Player icon " << i << " selected" << std::endl;
//                         selectedPlayerIcon = i;
//                         playerIconButtons[i]->setText(playerIconButtons[i]->getText());
//                     }
//                 }
//             }
            
//             // Check if Back button was clicked - return to main menu
//             if (backButton->getState() == clicked) {
//                 std::cout << "[DEBUG] Back clicked from settings" << std::endl;
//                 setState(GameState::MENU);
//                 backButton->setText(backButton->getText());
//             }
            
//             // Check if Lives Up button was clicked - increase lives (max 5)
//             if (livesUpButton->getState() == clicked) {
//                 if (lives < 5) {
//                     lives++;
//                     std::cout << "[DEBUG] Lives increased to " << lives << std::endl;
//                 }
//                 livesUpButton->setText(livesUpButton->getText());
//             }
            
//             // Check if Lives Down button was clicked - decrease lives (min 1)
//             if (livesDownButton->getState() == clicked) {
//                 if (lives > 1) {
//                     lives--;
//                     std::cout << "[DEBUG] Lives decreased to " << lives << std::endl;
//                 }
//                 livesDownButton->setText(livesDownButton->getText());
//             }
            
//             // Check if Level Up button was clicked - increase spawn level
//             if (levelUpButton->getState() == clicked) {
//                 spawnLevel++;
//                 std::cout << "[DEBUG] Spawn level increased to " << spawnLevel << std::endl;
//                 levelUpButton->setText(levelUpButton->getText());
//             }
            
//             // Check if Level Down button was clicked - decrease spawn level (min 0)
//             if (levelDownButton->getState() == clicked) {
//                 if (spawnLevel > 0) {
//                     spawnLevel--;
//                     std::cout << "[DEBUG] Spawn level decreased to " << spawnLevel << std::endl;
//                 }
//                 levelDownButton->setText(levelDownButton->getText());
//             }
//             break;
//         }
            
//         case GameState::LEADERBOARD: {
//             // LEADERBOARD STATE
//             // Display high scores - ESC key returns to menu
//             // No buttons to update, just check for ESC key
            
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
//                 std::cout << "[DEBUG] ESC pressed in leaderboard - returning to menu" << std::endl;
//                 setState(GameState::MENU);
//             }
//             break;
//         }
            
//         case GameState::GAME_OVER: {
//             // GAME OVER STATE
//             // Show final score with Play Again and Main Menu options
            
//             std::cout << "[DEBUG] Updating GAME_OVER state buttons" << std::endl;
            
//             // Safety check for game over buttons
//             if (!playAgainButton || !mainMenuFromGameOverButton) {
//                 std::cerr << "[ERROR] One or more game over buttons are nullptr!" << std::endl;
//                 return;
//             }
            
//             // Update game over buttons
//             playAgainButton->update(event, window);
//             mainMenuFromGameOverButton->update(event, window);
            
//             // Check if Play Again was clicked - start new game
//             if (playAgainButton->getState() == clicked) {
//                 std::cout << "[DEBUG] Play Again clicked" << std::endl;
//                 setState(GameState::PLAYING);
//                 playAgainButton->setText(playAgainButton->getText());
//             }
            
//             // Check if Main Menu was clicked - return to menu
//             if (mainMenuFromGameOverButton->getState() == clicked) {
//                 std::cout << "[DEBUG] Main Menu clicked from game over" << std::endl;
//                 setState(GameState::MENU);
//                 mainMenuFromGameOverButton->setText(mainMenuFromGameOverButton->getText());
//             }
//             break;
//         }
//     }
// }

// /**
//  * @brief Render function - draws everything for the current state
//  * 
//  * This is called every frame to draw the UI. First it draws the black background,
//  * then it calls the appropriate render function based on current state.
//  * Finally, if the quit confirmation dialog is showing, it draws that on top.
//  * 
//  * Rendering order matters! Things drawn first appear behind things drawn later.
//  */
// void ScreenManager::render() {
//     // Draw black background first (behind everything)
//     window.draw(background);
    
//     // Draw the appropriate screen based on current state
//     switch (currentState) {
//         case GameState::MENU:
//             renderMainMenu();
//             break;
            
//         case GameState::PLAYING:
//             // Gameplay rendering is handled by Game class in main.cpp
//             // We don't draw anything here
//             break;
            
//         case GameState::PAUSED:
//             renderPauseMenu();
//             break;
            
//         case GameState::SETTINGS:
//             renderSettings();
//             break;
            
//         case GameState::LEADERBOARD:
//             renderLeaderboard();
//             break;
            
//         case GameState::GAME_OVER:
//             renderGameOver(0);  // TODO: Pass actual score from Game class
//             break;
//     }
    
//     // Draw quit confirmation dialog on top of everything if showing
//     // This must be last so it appears above all other UI elements
//     if (showQuitConfirmation) {
//         renderQuitConfirmation();
//     }
// }

// /**
//  * @brief Change the current state
//  * 
//  * This is the most critical function - it handles transitioning between states.
//  * When changing states, we must:
//  * 1. Delete buttons from the old state (to free memory)
//  * 2. Change the state variable
//  * 3. Create buttons for the new state
//  * 
//  * CRITICAL FIX: We now check if quit confirmation buttons exist before creating them.
//  * They're created once in initialize() and kept for the entire program lifetime.
//  * 
//  * @param newState The state to transition to
//  */
// void ScreenManager::setState(GameState newState) {
//     std::cout << "[DEBUG] setState called: " << static_cast<int>(currentState) 
//               << " -> " << static_cast<int>(newState) << std::endl;
    
//     // If we're already in the requested state, do nothing
//     // This prevents unnecessary deletion and recreation of buttons
//     if (currentState == newState) {
//         std::cout << "[DEBUG] Already in requested state, ignoring" << std::endl;
//         return;
//     }
    
//     // STEP 1: Delete buttons from the OLD state
//     // We only delete buttons specific to that state
//     // Quit confirmation buttons are NEVER deleted here
//     std::cout << "[DEBUG] Cleaning up old state buttons..." << std::endl;
//     switch (currentState) {
//         case GameState::MENU:
//             std::cout << "[DEBUG] Deleting main menu buttons" << std::endl;
//             deleteMainMenuButtons();
//             break;
            
//         case GameState::PAUSED:
//             std::cout << "[DEBUG] Deleting pause menu buttons" << std::endl;
//             deletePauseMenuButtons();
//             break;
            
//         case GameState::SETTINGS:
//             std::cout << "[DEBUG] Deleting settings buttons" << std::endl;
//             deleteSettingsButtons();
//             break;
            
//         case GameState::GAME_OVER:
//             std::cout << "[DEBUG] Deleting game over buttons" << std::endl;
//             deleteGameOverButtons();
//             break;
            
//         case GameState::PLAYING:
//         case GameState::LEADERBOARD:
//             // These states have no buttons to delete
//             std::cout << "[DEBUG] No buttons to delete for this state" << std::endl;
//             break;
//     }
    
//     // STEP 2: Change the state variable
//     std::cout << "[DEBUG] Changing state variable" << std::endl;
//     currentState = newState;
    
//     // STEP 3: Create buttons for the NEW state
//     // We only create buttons needed for that state
//     std::cout << "[DEBUG] Creating new state buttons..." << std::endl;
//     switch (currentState) {
//         case GameState::MENU:
//             std::cout << "[DEBUG] Creating main menu buttons" << std::endl;
//             createMainMenuButtons();
//             break;
            
//         case GameState::PAUSED:
//             std::cout << "[DEBUG] Creating pause menu buttons" << std::endl;
//             createPauseMenuButtons();
//             break;
            
//         case GameState::SETTINGS:
//             std::cout << "[DEBUG] Creating settings buttons" << std::endl;
//             createSettingsButtons();
//             break;
            
//         case GameState::GAME_OVER:
//             std::cout << "[DEBUG] Creating game over buttons" << std::endl;
//             createGameOverButtons();
//             break;
            
//         case GameState::PLAYING:
//         case GameState::LEADERBOARD:
//             // These states have no buttons to create
//             std::cout << "[DEBUG] No buttons to create for this state" << std::endl;
//             break;
//     }
    
//     // CRITICAL FIX: Don't recreate quit confirmation buttons!
//     // They're created once in initialize() and never deleted
//     // This check is here just for safety, but should never trigger
//     if (!confirmYesButton || !confirmNoButton) {
//         std::cout << "[WARNING] Quit confirmation buttons missing, recreating" << std::endl;
//         createQuitConfirmButtons();
//     }
    
//     std::cout << "[DEBUG] setState complete" << std::endl;
// }

// /**
//  * @brief Get the current state
//  * @return The current GameState enum value
//  */
// GameState ScreenManager::getState() const {
//     return currentState;
// }