/**
 * @file LeaderboardScreen.cpp
 * @author Ian Codding II
 * @brief Implementation of LeaderboardScreen - leaderboard display
 * @version 1.0
 * @date 2025-10-27
 *
 * @copyright Copyright (c) 2025
 */

#include "../includes/LeaderboardScreen.h"
#include "../includes/errorHandler.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

/**
 * @brief Constructor - initialize the leaderboard screen
 *
 * Sets up:
 * - All pointers to nullptr
 * - Black background
 * - "LEADERBOARD" title text
 * - Empty entries vector
 *
 * @param win Reference to the main window
 * @param fnt Reference to the shared font
 */
LeaderboardScreen::LeaderboardScreen(sf::RenderWindow &win, sf::Font &fnt)
    : Screen(win, fnt)
    , backButton(nullptr) {

    std::cout << "[LeaderboardScreen] Constructor called" << std::endl;

    // Set up the black background
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);

    // Set up the title
    titleText.setFont(font);
    titleText.setString("LEADERBOARD");
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::Green);
    titleText.setPosition(
        (1200 - titleText.getLocalBounds().width) / 2,
        25);

    // Set up header text
    headerText.setFont(font);
    headerText.setString("RANK          PLAYER NAME          SCORE");
    headerText.setCharacterSize(27);
    headerText.setFillColor(sf::Color::Yellow);
    headerText.setPosition(50, 170);
}

/**
 * @brief Destructor - clean up resources
 */
LeaderboardScreen::~LeaderboardScreen() {
    std::cout << "[LeaderboardScreen] Destructor called" << std::endl;
    cleanup();
}

/**
 * @brief Initialize - load scores and create button
 *
 * Called once when screen becomes active.
 * 1. Loads leaderboard from file
 * 2. Formats text display
 * 3. Creates Back button
 */
void LeaderboardScreen::initialize() {
    std::cout << "[LeaderboardScreen] initialize() called" << std::endl;

    // Load leaderboard data from file
    loadFromFile();

    // Format the text for display
    formatRankText();

    // Create the Back button
    float winWidth = 1200;
    float winHeight = 800;

    backButton = new Button(
        "Back",
        sf::Vector2f((winWidth - 800) / 2, winHeight - 100),
        sf::Vector2f(200, 50),
        sf::Color::Green);
    backButton->setColorTextNormal(sf::Color::Black);
    backButton->setColorTextHover(sf::Color::Yellow);

    std::cout << "[LeaderboardScreen] Initialization complete" << std::endl;
}

/**
 * @brief Update - process events and return next state
 *
 * Updates the Back button and checks for clicks.
 *
 * Note: Button::update() takes (sf::Event&, sf::RenderWindow&)
 * Note: Button::getState() returns: normal, hovered, or clicked
 *
 * @param event The SFML event to process
 * @return MENU if Back clicked, otherwise LEADERBOARD
 */
GameState LeaderboardScreen::update(sf::Event &event) {
    // Update Back button
    if (backButton != nullptr) {
        backButton->update(event, window);
        if (backButton->getState() == clicked) {
            std::cout << "[LeaderboardScreen] Back clicked - returning to menu" << std::endl;
            return GameState::MENU;
        }
    }
    // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
    //     std::cout << "[LeaderboardScreen] Escaped clicked - returning to menu" << std::endl;
    //     return GameState::MENU;
    // }

    // Stay on leaderboard
    return GameState::LEADERBOARD;
}

/**
 * @brief Render - draw the leaderboard screen
 *
 * Drawing order:
 * 1. Background
 * 2. Title
 * 3. Column headers
 * 4. Ranked entries (1-10)
 * 5. Back button
 *
 * IMPORTANT: Button inherits from sf::Drawable
 * So we use window.draw(*button) NOT button->draw(window)
 */
void LeaderboardScreen::render() {
    // Draw background
    window.draw(background);

    // Draw title
    window.draw(titleText);

    // Draw header
    window.draw(headerText);

    // Draw all ranked entries
    for (const auto &rankText : rankTexts) {
        window.draw(rankText);
    }

    // Draw Back button
    if (backButton != nullptr) {
        window.draw(*backButton);
    }
}

/**
 * @brief Add a new score to the leaderboard
 *
 * Inserts a new entry, sorts by score (highest first), keeps top 10.
 *
 * Example usage from Game class:
 * ```cpp
 * LeaderboardScreen* leaderboard = (LeaderboardScreen*)screenManager.getScreen(GameState::LEADERBOARD);
 * leaderboard->addScore("PLAYER", finalScore);
 * leaderboard->saveToFile();
 * ```
 *
 * @param name Player name to add
 * @param score Score to add
 */
void LeaderboardScreen::addScore(const std::string &name, int score) {
    std::cout << "[LeaderboardScreen] Adding score: " << name << " - " << score << std::endl;

    // Add the new entry
    entries.push_back(LeaderboardEntry(name, score));

    // Sort by score (highest first)
    sortByScore();

    // Keep only top 10
    keepTop10();

    // Reformat display text
    formatRankText();
}

/**
 * @brief Check if a score qualifies for top 10
 *
 * Used by Game class to show name entry dialog.
 *
 * @param score Score to check
 * @return true if score is top 10 or list has < 10 entries
 */
bool LeaderboardScreen::isTopScore(int score) const {
    // If leaderboard has fewer than 10 entries, any score qualifies
    if (entries.size() < 10) {
        return true;
    }

    // Check if score is higher than the lowest entry (which is last after sorting)
    if (score > entries.back().score) {
        return true;
    }

    return false;
}

/**
 * @brief Load leaderboard from file
 *
 * Reads data/leaderboard.txt format:
 * ```
 * PlayerName 12500
 * Player2 10000
 * ...
 * ```
 *
 * Creates file if it doesn't exist.
 */
void LeaderboardScreen::loadFromFile() {
    std::cout << "[LeaderboardScreen] Loading from file: " << LEADERBOARD_FILE << std::endl;

    // Clear existing entries
    entries.clear();

    // Try to open the file
    std::ifstream file(LEADERBOARD_FILE);

    // If file doesn't exist, that's okay - just start with empty leaderboard
    if (!file.is_open()) {
        std::cout << "[LeaderboardScreen] File doesn't exist yet - starting with empty leaderboard" << std::endl;
        return;
    }

    // Read entries from file
    // Format: PlayerName Score
    std::string name;
    int score;

    while (file >> name >> score) {
        entries.push_back(LeaderboardEntry(name, score));
        std::cout << "[LeaderboardScreen] Loaded: " << name << " - " << score << std::endl;
    }

    // Close the file
    file.close();

    // Sort entries by score (highest first)
    sortByScore();

    // Keep only top 10
    keepTop10();

    std::cout << "[LeaderboardScreen] Loaded " << entries.size() << " entries" << std::endl;
}

/**
 * @brief Save leaderboard to file
 *
 * Writes all entries to data/leaderboard.txt
 */
void LeaderboardScreen::saveToFile() {
    std::cout << "[LeaderboardScreen] Saving to file: " << LEADERBOARD_FILE << std::endl;

    // Open file for writing
    std::ofstream file(LEADERBOARD_FILE);

    // Check if file opened successfully
    if (!file.is_open()) {
        std::cerr << "[ERROR] LeaderboardScreen: Failed to open leaderboard file for writing" << std::endl;
        return;
    }

    // Write all entries
    for (const auto &entry : entries) {
        file << entry.name << " " << entry.score << std::endl;
    }

    // Close file
    file.close();

    std::cout << "[LeaderboardScreen] Saved " << entries.size() << " entries" << std::endl;
}

/**
 * @brief Sort entries by score (highest first)
 *
 * Uses std::sort with a lambda function to sort in descending order.
 */
void LeaderboardScreen::sortByScore() {
    // Sort using std::sort
    // The lambda compares two entries and returns true if first should come before second
    // We want highest scores first, so if a.score > b.score, a comes first
    std::sort(entries.begin(), entries.end(),
              [](const LeaderboardEntry &a, const LeaderboardEntry &b) {
                  return a.score > b.score; // Descending order
              });
}

/**
 * @brief Keep only top 10 entries
 *
 * Removes any entries beyond position 10.
 */
void LeaderboardScreen::keepTop10() {
    // If we have more than 10 entries, erase the extras
    if (entries.size() > 10) {
        entries.erase(entries.begin() + 10, entries.end());
    }
}

/**
 * @brief Format the rank text for display
 *
 * Creates sf::Text objects for each entry to be displayed.
 * Format: "1.  PlayerName         12500"
 */
void LeaderboardScreen::formatRankText() {
    std::cout << "[LeaderboardScreen] Formatting rank text" << std::endl;

    // Clear existing rank texts
    rankTexts.clear();

    // Create text for each entry
    float startY = 240;    // Y position for first entry
    float lineHeight = 35; // Space between entries

    for (long unsigned int i = 0; i < entries.size(); i++) {
        sf::Text rankText;
        rankText.setFont(font);
        rankText.setCharacterSize(25);
        rankText.setFillColor(sf::Color::White);

        // Format: "1.  PlayerName:         Score"
        // Using string operands and space counting for nice formatting
        std::string line = std::to_string(i + 1) + "." +
                           std::string(20 - (entries[i].name.length() + std::to_string(i + 1).length()), ' ') +
                           entries[i].name + ":" +
                           std::string(20 - (std::to_string(entries[i].score).length()), ' ') +
                           std::to_string(entries[i].score);

        rankText.setString(line);
        rankText.setPosition(50, startY + (i * lineHeight));

        rankTexts.push_back(rankText);

        std::cout <<line <<std::endl;
    }

    std::cout << "[LeaderboardScreen] Formatted " << rankTexts.size() << " rank texts" << std::endl;
}

/**
 * @brief Cleanup - delete button
 *
 * Called when transitioning away from this screen.
 */
void LeaderboardScreen::cleanup() {
    std::cout << "[LeaderboardScreen] cleanup() called" << std::endl;

    if (backButton != nullptr) {
        delete backButton;
        backButton = nullptr;
    }

    std::cout << "[LeaderboardScreen] Cleanup complete" << std::endl;
}