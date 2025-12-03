/**
 * @file main.cpp
 * @author Ian Codding II
 * @brief Entry point for Centipede game - sets up window and main loop
 * @version 2.1 - Fixed pause/resume state management
 * @date 2025-10-27
 *
 * @copyright Copyright (c) 2025
 */

#include "../includes/errorHandler.h"
#include "../includes/game.h"
#include "../includes/Game_State.h"
#include "../includes/ScreenManager.h"
#include <cstddef>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

/**
 * @brief Main entry point for the Centipede game
 *
 * This function:
 * 1. Creates the SFML window
 * 2. Creates the ScreenManager for UI management
 * 3. Creates the Game object for gameplay
 * 4. Runs the main game loop with delta time for frame-independent movement
 *
 * The main loop:
 * - Processes all events (mouse clicks, key presses, window close)
 * - Calculates delta time (dt) for frame-independent updates
 * - Updates the appropriate system (UI or Gameplay) with dt
 * - Renders the appropriate system (UI or Gameplay)
 * - Maintains consistent frame rate at 60 FPS
 *
 * The game uses a state machine with two main branches:
 * - Menu states (MENU, SETTINGS, LEADERBOARD): Handled by ScreenManager
 * - Gameplay states (PLAYING, PAUSED, GAME_OVER): Handled by Game class
 *
 * State flow diagram:
 * ```
 * MENU
 *  ├→ SETTINGS (ScreenManager)
 *  ├→ LEADERBOARD (ScreenManager)
 *  └→ PLAYING (Game class)
 *      ├→ PAUSED (ScreenManager)
 *      │   ├→ PLAYING (resume)
 *      │   ├→ MENU (quit to menu)
 *      │   └→ quit (close window)
 *      ├→ GAME_OVER (ScreenManager)
 *      │   ├→ PLAYING (play again)
 *      │   └→ MENU (main menu)
 *      └→ MENU (quit to menu)
 * ```
 *
 * @return 0 on successful exit, 1 on error
 */
int main() {
    try {
        srand(time(NULL));
        std::cout << "========================================" << std::endl;
        std::cout << "     CENTIPEDE GAME - Starting" << std::endl;
        std::cout << "========================================" << std::endl;

        // ========== WINDOW SETUP ==========

        /**
         * Create the main SFML window
         * - Resolution: 1200x800 pixels
         * - Title: "Centipede"
         * - This window is shared by all game systems (UI, Gameplay, etc.)
         *
         * Parameters:
         * 1. sf::VideoMode(width, height) - window resolution
         * 2. "title" - window title bar text
         * 3. sf::Style::Default - window style (resizable, close button, etc.)
         */
        sf::RenderWindow window(
            sf::VideoMode(1200, 800),
            "Centipede",
            sf::Style::Default);

        /**
         * Set frame rate limit to 60 FPS
         * This prevents the game from running as fast as possible
         * and consuming 100% CPU. Instead, it limits to 60 frames/second.
         *
         * Benefits:
         * - Consistent game speed across different computers
         * - Reduced CPU usage
         * - Smoother gameplay
         *
         * Combined with delta time (dt), this ensures:
         * - Smooth, consistent gameplay at 60 FPS
         * - Frame-independent movement (dt adapts to actual frame time)
         * - Predictable gameplay experience
         */
        window.setFramerateLimit(60);

        std::cout << "[main] Window created: 1200x800" << std::endl;
        std::cout << "[main] Frame rate limited to 60 FPS" << std::endl;

        // ========== CLOCK SETUP ==========

        /**
         * Create the clock for delta time calculation
         * This clock is used to measure the time between frames.
         *
         * Delta time (dt) is used for frame-independent movement:
         * - Movement = speed * dt
         * - This ensures consistent speed regardless of FPS
         *
         * The clock is created ONCE before the main loop.
         * Inside the loop, we call restart() every frame to get the time
         * since the last frame.
         */
        sf::Clock clock;

        // ========== UI SYSTEM SETUP ==========

        /**
         * Create the ScreenManager
         * This manages all UI screens (menu, settings, leaderboard, pause, game over)
         *
         * The ScreenManager uses a state machine pattern:
         * - Each GameState (MENU, SETTINGS, PLAYING, etc.) has a corresponding Screen
         * - Only one Screen is active at a time
         * - Screens handle their own buttons, events, and rendering
         */
        ScreenManager screenManager(window);

        std::cout << "[main] ScreenManager created" << std::endl;

        /**
         * Initialize the ScreenManager
         * This must happen after the window is created (OpenGL context needs to exist)
         *
         * What initialize() does:
         * 1. Loads the shared font from assets/fonts/Balins_Font.ttf
         * 2. Creates the initial screen (MainMenuScreen for MENU state)
         * 3. Sets up all UI elements
         */
        screenManager.initialize();

        std::cout << "[main] ScreenManager initialized" << std::endl;

        // ========== GAMEPLAY SYSTEM SETUP ==========

        /**
         * Create the Game object
         * This manages all gameplay elements (centipede, player, bullets, etc.)
         *
         * The Game object is created once but only "active" when state == PLAYING
         *
         * Why not create it on demand?
         * - Creating/destroying complex game objects is expensive
         * - We want to be able to pause and resume without losing state
         * - Reusing the same Game object preserves continuity
         */
        Game *game = nullptr;

        // When Start button is pressed:

        std::cout << "[main] Game object created" << std::endl;

        // ========== MAIN GAME LOOP ==========

        /**
         * Main loop runs until window is closed
         * isOpen() returns false when user clicks close button or we call window.close()
         */
        while (window.isOpen()) {

            /**
             * Calculate delta time (time since last frame in seconds)
             *
             * clock.restart() does two things:
             * 1. Returns the elapsed time since the last call (or creation)
             * 2. Resets the clock to 0
             *
             * .asSeconds() converts the time to seconds as a float
             *
             * Example on 60 FPS system:
             * - Each frame takes ~16.67ms
             * - dt ≈ 0.01667 seconds
             *
             * This dt value is used for ALL frame-independent updates:
             * - player.x += speed * dt
             * - centipede.move(dt)
             * - etc.
             */
            float dt = clock.restart().asSeconds();

            // ===== EVENT PROCESSING =====

            /**
             * Process all events that happened since last frame
             * Events include: mouse movement, clicks, key presses, window resize, etc.
             *
             * sf::Event::pollEvent() returns true if an event occurred, false if no more events
             * We loop until all events are processed
             */
            sf::Event event;
            while (window.pollEvent(event)) {

                // Check if window close button was clicked
                // This sets window.isOpen() to false, ending the main loop
                if (event.type == sf::Event::Closed) {
                    std::cout << "[main] Window close requested" << std::endl;
                    window.close();
                    break; // Exit event loop, next iteration of main loop will see isOpen() = false
                }

                // Get the current game state
                // Used to determine which system handles this event
                GameState currentState = screenManager.getState();

                // Check if the escape key was pressed.
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    std::cout << "[ScreenManager] Escaped clicked - returning to previous screen if not in menu" << std::endl;
                    if (currentState != GameState::MENU) {
                        screenManager.setState(GameState::MENU);
                    }
                }

                // ===== STATE-BASED EVENT HANDLING =====

                /**
                 * Determine which system handles the current event based on game state
                 *
                 * Menu states (MENU, SETTINGS, LEADERBOARD, PAUSED, GAME_OVER):
                 *   → ScreenManager handles the event (buttons, UI)
                 *
                 * Gameplay states (PLAYING):
                 *   → Game class handles the event (player movement, shooting, pause)
                 */

                switch (currentState) {
                    // ===== UI STATES =====

                case GameState::MENU:
                    /**
                     * Main menu state
                     * - User can click Start Game, Settings, Leaderboard, or Quit
                     * - ScreenManager (MainMenuScreen) handles these buttons
                     */
                    screenManager.update(event);
                    break;

                case GameState::SETTINGS:
                    /**
                     * Settings menu state
                     * - User can adjust lives, spawn level, player icon
                     * - ScreenManager (SettingsScreen) handles these buttons
                     */
                    screenManager.update(event);
                    break;

                case GameState::LEADERBOARD:
                    /**
                     * Leaderboard display state
                     * - User can only click Back button
                     * - ScreenManager (LeaderboardScreen) handles this
                     */
                    screenManager.update(event);
                    break;

                case GameState::PAUSED:
                    /**
                     * Pause menu state (during gameplay)
                     * - User can Resume, go to Main Menu, or Quit
                     * - ScreenManager (PauseScreen) handles these buttons
                     * - Game object is NOT updated while paused
                     * - PauseScreen returns next state which we check after this loop
                     */
                    screenManager.update(event);
                    {
                        // Check what state the ScreenManager transitioned to after pause screen input
                        GameState newScreenState = screenManager.getState();
                        
                        // If pause screen changed state to PLAYING (resume clicked)
                        if (newScreenState == GameState::PLAYING && game != nullptr) {
                            std::cout << "[main] Resume clicked - resuming game" << std::endl;
                            game->setPaused(false);
                        }
                        // If pause screen changed state to MENU (main menu clicked)
                        else if (newScreenState == GameState::MENU && game != nullptr) {
                            std::cout << "[main] Main Menu clicked from pause - cleaning up game" << std::endl;
                            game->cleanup();
                            delete game;
                            game = nullptr;
                        }
                    }
                    break;

                case GameState::GAME_OVER:
                    /**
                     * Game over state
                     * - User can enter name if top 10 score
                     * - User can Play Again or return to Main Menu
                     * - ScreenManager (GameOverScreen) handles these buttons
                     */
                    screenManager.update(event);
                    {
                        // Check what state the ScreenManager transitioned to after game over screen input
                        GameState newScreenState = screenManager.getState();
                        
                        // If game over screen changed state to PLAYING (play again clicked)
                        if (newScreenState == GameState::PLAYING && game != nullptr) {
                            std::cout << "[main] Play Again clicked - resetting game" << std::endl;
                            game->cleanup();
                            delete game;
                            game = nullptr;
                            
                            // Reset game over screen for next time
                            GameOverScreen *gameOverScreen =
                                (GameOverScreen *)screenManager.getScreen(GameState::GAME_OVER);
                            if (gameOverScreen != nullptr) {
                                gameOverScreen->reset();
                            }
                        }
                        // If game over screen changed state to MENU (main menu clicked)
                        else if (newScreenState == GameState::MENU && game != nullptr) {
                            std::cout << "[main] Main Menu clicked from game over - cleaning up game" << std::endl;
                            game->cleanup();
                            delete game;
                            game = nullptr;
                            
                            // Reset game over screen for next time
                            GameOverScreen *gameOverScreen =
                                (GameOverScreen *)screenManager.getScreen(GameState::GAME_OVER);
                            if (gameOverScreen != nullptr) {
                                gameOverScreen->reset();
                            }
                        }
                    }
                    break;

                    // ===== GAMEPLAY STATE =====

                case GameState::PLAYING:
                    /**
                     * Active gameplay state
                     * - Player can move and shoot
                     * - Press P or ESC to pause
                     * - Game class (not ScreenManager) handles all events
                     */
                    if (game == nullptr) {
                        std::cout << "[main] Creating Game object for PLAYING state\n";
                        game = new Game(window, screenManager);
                        game->initialize(); // Initialize the game (get settings, create objects)
                        std::cout << "[main] Game initialized and ready to play\n";
                    }

                    // Now game is guaranteed to be non-null
                    if (game != nullptr) {
                        game->handleInput(event);
                    }
                    break;

                default:
                    /**
                     * Unknown state (shouldn't happen)
                     * Log error and continue
                     */
                    logError("main", "Unknown game state");
                    break;
                }
            }

            // ===== UPDATING =====

            /**
             * Update game logic based on current state
             * Different systems update depending on which state we're in
             *
             * Delta time (dt) is passed to gameplay updates for frame-independent movement
             */
            GameState currentState = screenManager.getState();

            if (currentState == GameState::PLAYING) {
                /**
                 * Gameplay update
                 * Called every frame with delta time to:
                 * - Move centipede (centipede position += speed * dt)
                 * - Update bullets (bullet position += speed * dt)
                 * - Check collisions
                 * - Update player position (player position += speed * dt)
                 * - Check game over conditions
                 *
                 * IMPORTANT: Pass dt to ensure frame-independent movement!
                 * Without dt, movement would be frame-dependent and vary with FPS.
                 */
                
                if (game != nullptr) {
                    game->update(dt);

                    // Check if Game class changed state (e.g., PLAYING -> PAUSED or GAME_OVER)
                    GameState newState = game->getState();
                    if (newState != currentState) {
                        std::cout << "[main] Game changed state from PLAYING to "
                                  << static_cast<int>(newState) << std::endl;
                        screenManager.setState(newState);
                    }
                }

            } else {
                /**
                 * Other UI states update
                 * ScreenManager doesn't need per-frame updates for most screens
                 * (It handles everything in event processing)
                 *
                 * Note: We could add animations here if needed
                 */
            }

            // ===== RENDERING =====

            /**
             * Clear the window (paint it black)
             * This removes everything from last frame so we can draw fresh
             */
            window.clear(sf::Color::Black);

            /**
             * Render based on current state
             * Each system draws its own content
             */
            if (currentState == GameState::PLAYING) {
                /**
                 * Render gameplay
                 * Draws: background, mushrooms, centipede, bullets, player, HUD
                 */
                if (game != nullptr) {
                    game->render();
                }
            } else {
                /**
                 * Render UI screen
                 * Draws: buttons, menus, leaderboard, pause screen, etc.
                 * ScreenManager forwards to the appropriate Screen object
                 */
                screenManager.render();
            }

            /**
             * Display the rendered frame
             * Swaps buffers so the user sees what we just drew
             * This is called once per frame, at the end
             */
            window.display();

        } // End main loop

        /**
         * Clean up and delete the Game object before exiting
         * This ensures all game resources are properly cleaned up
         */
        if (game != nullptr) {
            std::cout << "[main] Cleaning up Game object" << std::endl;
            game->cleanup(); // Call cleanup() to free game resources
            delete game;     // Delete the Game object itself
            game = nullptr;
        }

        std::cout << "========================================" << std::endl;
        std::cout << "     CENTIPEDE GAME - Exiting" << std::endl;
        std::cout << "========================================" << std::endl;

        // Window and all objects are automatically destroyed here as they go out of scope
        return 0;

    } catch (const ResourceError &e) {
        /**
         * Catch resource loading errors (font, texture, etc.)
         * Print error message and exit with code 1
         */
        logError("main", std::string("Resource error: ") + e.what());
        return 1;

    } catch (const std::exception &e) {
        /**
         * Catch any other standard exceptions
         * Print error and exit with code 1
         */
        logError("main", std::string("Exception: ") + e.what());
        return 1;
    }
}