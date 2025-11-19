/**
 * @file LeaderboardScreen.h
 * @author Ian Codding II
 * @brief Leaderboard screen - displays high scores
 * @version 1.0
 * @date 2025-10-27
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef LEADERBOARD_SCREEN_H
#define LEADERBOARD_SCREEN_H

#include "Screen.h"
#include "button.h"
#include <vector>
#include <string>

/**
 * @struct LeaderboardEntry
 * @brief Represents a single leaderboard entry (name and score)
 */
struct LeaderboardEntry {
    std::string name;   // Player name
    int score;          // Score achieved
    
    LeaderboardEntry() : name(""), score(0) {}
    LeaderboardEntry(const std::string& n, int s) : name(n), score(s) {}
};

/**
 * @class LeaderboardScreen
 * @brief Handles the leaderboard display showing top 10 scores
 * 
 * This screen displays the top 10 highest scores achieved by players.
 * It:
 * - Loads scores from a leaderboard file (leaderboard.txt)
 * - Displays them in a ranked list
 * - Allows navigation (Back button)
 * - Can save/load leaderboard data
 * 
 * Layout:
 * - "LEADERBOARD" title (large, green)
 * - Ranked list of top 10 scores (1-10)
 * - Each entry shows: Rank. PlayerName .... Score
 * - Back button to return to menu
 * 
 * File format (leaderboard.txt):
 * ```
 * PlayerName Score
 * PlayerName Score
 * ...
 * ```
 * 
 * This class is responsible for:
 * - Creating the leaderboard display
 * - Loading scores from file
 * - Saving scores to file
 * - Rendering the leaderboard
 * - Handling the Back button
 * - Cleaning up when transitioning away
 */
class LeaderboardScreen : public Screen {
private:
    // Navigation button
    Button* backButton;             // "Back" - return to main menu
    
    // Leaderboard data
    std::vector<LeaderboardEntry> entries;  // List of top scores
    
    // UI text elements
    sf::Text titleText;             // "LEADERBOARD" title
    sf::Text headerText;            // "RANK  PLAYER  SCORE" header
    std::vector<sf::Text> rankTexts; // One text object per leaderboard entry
    
    // Background
    sf::RectangleShape background;  // Black background
    
    // File path for leaderboard data
    const std::string LEADERBOARD_FILE = "data/leaderboard.txt";
    
public:
    /**
     * @brief Constructor - sets up initial state
     * 
     * Initializes all pointers and prepares text objects.
     * Button creation happens in initialize().
     * 
     * @param win Reference to main window
     * @param fnt Reference to loaded font
     */
    LeaderboardScreen(sf::RenderWindow& win, sf::Font& fnt);
    
    /**
     * @brief Destructor - ensures cleanup is called
     */
    ~LeaderboardScreen();
    
    /**
     * @brief Initialize - load scores and create button
     * 
     * Called once when screen becomes active.
     * Loads leaderboard data from file and creates the Back button.
     */
    void initialize() override;
    
    /**
     * @brief Update - process events and return next state
     * 
     * Updates the Back button and checks for clicks.
     * Returns MENU if Back is clicked, otherwise LEADERBOARD.
     * 
     * @param event The SFML event to process
     * @return Next state to transition to
     */
    GameState update(sf::Event& event) override;
    
    /**
     * @brief Render - draw the leaderboard screen
     * 
     * Draws background, title, leaderboard entries, and Back button.
     */
    void render() override;
    
    /**
     * @brief Cleanup - delete button
     * 
     * Frees memory used by the Back button.
     */
    void cleanup() override;
    
    /**
     * @brief Add a new score to the leaderboard
     * 
     * Adds an entry, sorts by score (highest first), keeps only top 10.
     * Does NOT automatically save to file - call save() after.
     * 
     * @param name Player name
     * @param score Score achieved
     */
    void addScore(const std::string& name, int score);
    
    /**
     * @brief Check if a score qualifies for top 10
     * 
     * Used by Game class to determine if player should enter name.
     * 
     * @param score Score to check
     * @return true if score is in top 10 (or list has < 10 entries)
     */
    bool isTopScore(int score) const;
    
    /**
     * @brief Load leaderboard from file
     * 
     * Reads leaderboard.txt and populates the entries vector.
     * Creates file if it doesn't exist.
     */
    void loadFromFile();
    
    /**
     * @brief Save leaderboard to file
     * 
     * Writes all entries to leaderboard.txt.
     */
    void saveToFile();
    
private:
    /**
     * @brief Sort entries by score (highest first)
     * 
     * Called after adding a new score or loading from file.
     * Ensures entries are in correct rank order.
     */
    void sortByScore();
    
    /**
     * @brief Keep only top 10 entries
     * 
     * Called after adding a new score.
     * Removes any entries beyond the top 10.
     */
    void keepTop10();
    
    /**
     * @brief Format the rank text for display
     * 
     * Creates text objects for all entries to be displayed.
     * Called after loading leaderboard.
     */
    void formatRankText();
};

#endif // LEADERBOARD_SCREEN_H