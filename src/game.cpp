/**
 * @file game.cpp
 * @author Ian Codding II
 * @brief Main game controller - orchestrates all gameplay systems
 * @version 2.3 - Objects handle own collision and grid management
 * @date 2025-12-01
 */

#include "../includes/game.h"
#include "../includes/errorHandler.h"
#include "../includes/grid.h"
#include <cstdlib>
#include <iostream>

/**
 * @brief Constructor - initialize game systems
 * @param win Reference to render window
 * @param screenMngr Reference to ScreenManager
 */
Game::Game(sf::RenderWindow &win, ScreenManager &screenMngr)
    : window(win)
    , screenManager(screenMngr)
    , currentState(GameState::PLAYING)
    , isGameOver(false)
    , isPaused(false)
    , score(0)
    , lives(3)
    , level(1)
    , player(nullptr)
    , centipede(nullptr)
    , grid(nullptr)
    , texture() {

    std::cout << "[Game] Constructor called" << std::endl;

    sf::Font &font = screenManager.getFont();

    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(10, 10);

    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::Green);
    livesText.setPosition(window.getSize().x - 200, 10);

    levelText.setFont(font);
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf::Color::Green);
    levelText.setPosition(window.getSize().x / 2 - 50, 10);

    if (!loadTextures()) {
        logError("Game", "Failed to load textures");
    }

    std::cout << "[Game] Constructor completed" << std::endl;
}

/**
 * @brief Destructor - cleanup resources
 */
Game::~Game() {
    std::cout << "[Game] Destructor called" << std::endl;
    cleanup();
}

/**
 * @brief Initialize new game session
 * Gets settings, creates player, generates mushrooms
 */
void Game::initialize() {
    std::cout << "[Game] initialize() called" << std::endl;

    // Create grid
    if (grid == nullptr) {
        grid = new Grid(sf::FloatRect(125, 80, 950, 720), 16);
        std::cout << "[Game] Grid created (360x360, 16x16 cells)" << std::endl;
    }

    SettingsScreen *settings =
        (SettingsScreen *)screenManager.getScreen(GameState::SETTINGS);

    if (settings != nullptr) {
        lives = settings->getLives();
        level = settings->getSpawnLevel();
        std::cout << "[Game] Settings: Lives=" << lives << ", Level=" << level << std::endl;
    }

    score = 0;
    isGameOver = false;
    isPaused = false;
    currentState = GameState::PLAYING;

    player = new sf::RectangleShape();
    Player::startPlayer(*player, texture);

    sf::RectangleShape bullet = sf::RectangleShape();
    Bullet::startBullet(bullet, texture);

    generateMushrooms();

    std::cout << "[Game] Game ready to play" << std::endl;
}

/**
 * @brief Handle pause/resume input (P or ESC)
 * @param event SFML event to process
 */
void Game::handleInput(const sf::Event &event) {
    if (isGameOver)
        return;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Escape) {
            isPaused = !isPaused;

            if (isPaused) {
                currentState = GameState::PAUSED;
                std::cout << "[Game] PAUSED" << std::endl;
            } else {
                currentState = GameState::PLAYING;
                std::cout << "[Game] RESUMED" << std::endl;
            }
        }
    }
}

/**
 * @brief Update game logic each frame
 * Only called when state == PLAYING
 * @param dt Delta time since last frame (seconds)
 */
void Game::update(float dt) {
    if (isPaused || isGameOver)
        return;

    // Update player
    if (player) {
        Player::movePlayer(*player, dt, grid->getRegion());
    }

    // Handle bullets
    sf::RectangleShape tempBullet;
    tempBullet.setSize(sf::Vector2f(10.f, 10.f));
    bulletObj.isShooting(*player, tempBullet, texture, bulletObj, dt);

    for (int i = static_cast<int>(bulletObj.bullets.size()) - 1; i >= 0; i--) {
        sf::Vector2f bulletPos = bulletObj.bullets[i].getPosition();
        bulletPos.y -= 500 * dt;
        bulletObj.bullets[i].setPosition(bulletPos);

        if (bulletPos.y < 0) {
            bulletObj.bullets.erase(bulletObj.bullets.begin() + i);
        }
    }

    // Update mushrooms
    for (auto mushroom : mushrooms) {
        if (mushroom) {
            mushroom->update();
        }
    }

    updateUI();
    checkGameOver();

    static int frameCount = 0;
    if (++frameCount % 60 == 0) {
        debugPrint();
    }
}

/**
 * @brief Render all game objects to window
 * Order: background, mushrooms, bullets, player, UI text
 */
void Game::render() {
    window.draw(background);

    for (auto mushroom : mushrooms) {
        if (mushroom) {
            window.draw(*mushroom);
        }
    }

    for (auto &bullet : bulletObj.bullets) {
        window.draw(bullet);
    }

    if (player) {
        window.draw(*player);
    }

    window.draw(scoreText);
    window.draw(livesText);
    window.draw(levelText);
}

/**
 * @brief Get current game state
 * @return GameState (PLAYING, PAUSED, GAME_OVER, etc)
 */
GameState Game::getState() const {
    return currentState;
}

/**
 * @brief Set game state with debug logging
 * @param newState New state to transition to
 */
void Game::setState(GameState newState) {
    if (newState != currentState) {
        currentState = newState;
        std::cout << "[Game] State: " << static_cast<int>(newState) << std::endl;
    }
}

/**
 * @brief Clean up all allocated resources
 * Deletes player, mushrooms, bullets
 */
void Game::cleanup() {
    std::cout << "[Game] cleanup() called" << std::endl;

    if (player != nullptr) {
        delete player;
        player = nullptr;
    }

    for (auto mushroom : mushrooms) {
        if (mushroom != nullptr) {
            delete mushroom;
        }
    }
    mushrooms.clear();

    bulletObj.bullets.clear();

    if (grid != nullptr) {
        delete grid;
        grid = nullptr;
    }

    std::cout << "[Game] Cleanup completed" << std::endl;
}

/**
 * @brief Load all game textures from atlas file
 * @return true if successful, false on error
 */
bool Game::loadTextures() {
    if (!texture.loadFromFile("assets/sprites/atlas.png")) {
        logError("Game", "Failed to load atlas texture");
        return false;
    }

    std::cout << "[Game] Atlas loaded" << std::endl;
    return true;
}

/**
 * @brief Generate random mushroom obstacles
 * Count = 10 + (level * 2)
 */
void Game::generateMushrooms() {
    if (grid == nullptr) {
        std::cerr << "[Game] ERROR: Grid not initialized!" << std::endl;
        return;
    }

    int mushroomCount = 10 + (level * 2);

    std::cout << "[Game] Generating " << mushroomCount << " mushrooms" << std::endl;

    for (int i = 0; i < mushroomCount; i++) {
        // Use grid bounds with padding from top for UI
        float randomX = rand() % (int)grid->getRegion().width + grid->getRegion().left;
        float randomY = rand() % (int)(grid->getRegion().height - 250) + grid->getRegion().top + 50;

        Mushroom *mushroom = new Mushroom(
            texture,
            sf::IntRect(64, 64, 32, 32),
            sf::Vector2f(randomX, randomY),
            4,
            false);

        mushroom->setScale(sf::Vector2i(3, 3));
        mushrooms.push_back(mushroom);
    }

    std::cout << "[Game] Created " << mushrooms.size() << " mushrooms" << std::endl;
}

/**
 * @brief Check game over condition and handle top 10 scores
 * If lives <= 0: set game over and mark for name input if top 10
 */
void Game::checkGameOver() {
    if (lives <= 0) {
        isGameOver = true;
        currentState = GameState::GAME_OVER;

        std::cout << "[Game] GAME OVER - Score: " << score << std::endl;

        GameOverScreen *gameOverScreen =
            (GameOverScreen *)screenManager.getScreen(GameState::GAME_OVER);

        if (gameOverScreen != nullptr) {
            gameOverScreen->setScore(score);

            LeaderboardScreen *leaderboard =
                (LeaderboardScreen *)screenManager.getScreen(GameState::LEADERBOARD);

            if (leaderboard != nullptr && leaderboard->isTopScore(score)) {
                std::cout << "[Game] Top 10 score! Ready for name input" << std::endl;
                gameOverScreen->setIsTopScore(true);
            }
        }
    }
}

/**
 * @brief Save name to leaderboard after submission
 * Called by main.cpp after GameOverScreen returns GAME_OVER
 * @param playerName Name to save
 */
void Game::savePlayerScore(const std::string &playerName) {
    LeaderboardScreen *leaderboard =
        (LeaderboardScreen *)screenManager.getScreen(GameState::LEADERBOARD);

    if (leaderboard != nullptr) {
        leaderboard->addScore(playerName, score);
        leaderboard->saveToFile();
        std::cout << "[Game] Score saved: " << playerName << " - " << score << std::endl;
    }
}

void Game::updateUI() {
    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(lives));
    levelText.setString("Level: " + std::to_string(level));
}

void Game::debugPrint() const {
    std::cout << "[Game] Score: " << score << " | Lives: " << lives
              << " | Level: " << level << " | Bullets: " << bulletObj.bullets.size()
              << " | Mushrooms: " << mushrooms.size() << std::endl;
}