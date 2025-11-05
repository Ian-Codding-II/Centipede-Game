/**
 * @file main.cpp
 * @author Ian Codding II
 * @brief Entry point with integrated ScreenManager
 * @version 0.1
 * @date 2025-10-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../includes/screenManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    try {
        // Create window
        sf::RenderWindow window(sf::VideoMode(800, 600), "Centipede");
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);

        // Create screen manager
        ScreenManager screenManager(window);
        screenManager.initialize();

        std::cout << "Game started - Initial state: MENU" << std::endl;

        // Main game loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                // Let screen manager handle all events
                screenManager.update(event);

                // Debug: Print state changes
                static GameState lastState = GameState::MENU;
                GameState currentState = screenManager.getState();
                if (currentState != lastState) {
                    std::cout << "State changed to: ";
                    switch (currentState) {
                    case GameState::MENU:
                        std::cout << "MENU";
                        break;
                    case GameState::PLAYING:
                        std::cout << "PLAYING";
                        break;
                    case GameState::PAUSED:
                        std::cout << "PAUSED";
                        break;
                    case GameState::GAME_OVER:
                        std::cout << "GAME_OVER";
                        break;
                    case GameState::SETTINGS:
                        std::cout << "SETTINGS";
                        break;
                    case GameState::LEADERBOARD:
                        std::cout << "LEADERBOARD";
                        break;
                    }
                    std::cout << std::endl;
                    lastState = currentState;
                }
            }

            // Render
            window.clear(sf::Color::Black);

            GameState currentState = screenManager.getState();

            if (currentState == GameState::PLAYING) {
                // TODO: Render actual game here
                // For now, just show placeholder
                sf::Text playingText;
                sf::Font font;
                if (font.loadFromFile("assets/fonts/college.ttf")) {
                    playingText.setFont(font);
                    playingText.setString("PLAYING - Press P to Pause");
                    playingText.setCharacterSize(30);
                    playingText.setFillColor(sf::Color::White);
                    playingText.setPosition(150, 250);
                    window.draw(playingText);
                }

                // Check for pause
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    screenManager.setState(GameState::PAUSED);
                }
            } else {
                // Render UI screens
                screenManager.render();
            }

            window.display();
        }

    } catch (const std::exception &e) {
        std::cerr << "[FATAL ERROR] " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Game closed successfully!" << std::endl;
    return 0;
}


// int main() {
//     try {
//         // -------------------------------
//         // 1. CREATE THE WINDOW
//         // -------------------------------
//         // We make the main RenderWindow here and keep ownership local to main.
//         // ScreenManager receives a reference, so it never allocates or deletes the window.
//         sf::RenderWindow window(sf::VideoMode(800, 600), "Centipede");
//         window.setVerticalSyncEnabled(true);
//         window.setFramerateLimit(60);
//
//         // -------------------------------
//         // 2. INITIALIZE SCREEN MANAGER
//         // -------------------------------
//         // ScreenManager controls which state (menu, settings, playing, etc.) is currently visible.
//         // It will also create buttons and handle all transitions between screens.
//         ScreenManager screenManager(window);
//         screenManager.initialize(); // Build menus, load fonts, etc.
//
//         std::cout << "[INFO] Game started - Initial state: MENU" << std::endl;
//
//         // -------------------------------
//         // 3. MAIN GAME LOOP
//         // -------------------------------
//         // This loop runs until the user closes the window or exits via a menu option.
//         while (window.isOpen()) {
//             sf::Event event;
//             while (window.pollEvent(event)) {
//                 // Handle hard window close (red X)
//                 if (event.type == sf::Event::Closed)
//                     window.close();
//
//                 // Delegate all input handling to the ScreenManager.
//                 // It knows which screen is active and forwards events to the correct buttons or game objects.
//                 screenManager.update(event);
//             }
//
//             // -------------------------------
//             // 4. RENDERING
//             // -------------------------------
//             // Clear the window at the start of every frame.
//             window.clear(sf::Color::Black);
//
//             // Ask the screen manager which state is currently active.
//             GameState currentState = screenManager.getState();
//
//             // If we are in the gameplay state, let the Game class handle rendering.
//             if (currentState == GameState::PLAYING) {
//                 // Placeholder display until game logic is integrated
//                 sf::Font font;
//                 if (font.loadFromFile("assets/fonts/college.ttf")) {
//                     sf::Text playingText("PLAYING - Press P to Pause", font, 30);
//                     playingText.setFillColor(sf::Color::White);
//                     playingText.setPosition(150.f, 250.f);
//                     window.draw(playingText);
//                 }
//
//                 // Quick debug control: pause the game with 'P'
//                 if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
//                     screenManager.setState(GameState::PAUSED);
//                 }
//
//             } else {
//                 // Otherwise, render UI screens (menus, settings, leaderboard, etc.)
//                 screenManager.render();
//             }
//
//             // Present everything drawn this frame.
//             window.display();
//
//             // OPTIONAL DEBUG OUTPUT: track state changes for verification.
//             static GameState lastState = GameState::MENU;
//             if (screenManager.getState() != lastState) {
//                 std::cout << "[STATE CHANGE] "
//                           << static_cast<int>(lastState)
//                           << " → "
//                           << static_cast<int>(screenManager.getState())
//                           << std::endl;
//                 lastState = screenManager.getState();
//             }
//         }
//
//     } catch (const std::exception &e) {
//         // Catch-all for runtime errors (e.g., missing assets, SFML exceptions)
//         std::cerr << "[FATAL ERROR] " << e.what() << std::endl;
//         return EXIT_FAILURE;
//     }
//
//     std::cout << "[INFO] Game closed successfully!" << std::endl;
//     return EXIT_SUCCESS;
// }