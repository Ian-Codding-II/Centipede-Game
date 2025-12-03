/**
 * @file game.cpp
 * @author Ian Codding II
 * @brief Implementation of Game class - WITHOUT centipede for now
 * @version 2.1 - Testing player, bullets, and mushrooms only
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 */

#include "../includes/game.h"
#include "../includes/errorHandler.h"
#include "../includes/GameGrid.h"
#include <iostream>
#include <cstdlib>

/**
 * @brief Constructor - initialize the game
 */
Game::Game(sf::RenderWindow& win, ScreenManager& screenMngr)
    : window(win),
      screenManager(screenMngr),
      currentState(GameState::PLAYING),
      isGameOver(false),
      isPaused(false),
      score(0),
      lives(3),
      level(1),
      player(nullptr),
      centipede(nullptr),
      grid(nullptr),
      playerTexture(),
      mushroomTexture(),
      bulletTexture() {

    std::cout << "[Game] Constructor called" << std::endl;

    // Get font from ScreenManager
    sf::Font& font = screenManager.getFont();

    // Set up background
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);

    // Set up text displays
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

    // Load textures
    if (!loadTextures()) {
        logError("Game", "Failed to load some textures");
    }

    std::cout << "[Game] Constructor completed" << std::endl;
}

/**
 * @brief Destructor
 */
Game::~Game() {
    std::cout << "[Game] Destructor called" << std::endl;
    cleanup();
}

// ===== INITIALIZATION =====
/**
 * @brief Initialize a new game
 */
void Game::initialize() {
    std::cout << "[Game] initialize() called" << std::endl;

    if (grid == nullptr) {
        grid = new GameGrid(1200, 800);
        std::cout << "[Game] Game grid created (1200x800, 32x32 cells)" << std::endl;
    } else {
        delete grid;
        grid = new GameGrid(1200, 800);
    }

    SettingsScreen* settings = (SettingsScreen*)screenManager.getScreen(GameState::SETTINGS);
    if (settings != nullptr) {
        lives = settings->getLives();
        level = settings->getSpawnLevel();
        std::cout << "[Game] Loaded settings: Lives=" << lives << ", Level=" << level << std::endl;
    }

    // Reset score
    score = 0;
    isGameOver = false;
    isPaused = false;

    player = new sf::RectangleShape();
    Player::startPlayer(*player, playerTexture);

    generateMushrooms();

    std::cout << "[Game] Game initialized - ready to play!" << std::endl;
    std::cout << "[Game] Testing: Player, Bullets, and Mushrooms only (no centipede yet)" << std::endl;
}

// ===== GAME LOOP =====
/**
 * @brief Handle input events
 */
void Game::handleInput(const sf::Event& event) {
    if (isGameOver) return;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P) {
            isPaused = !isPaused;
            currentState = isPaused ? GameState::PAUSED : GameState::PLAYING;
            std::cout << "[Game] " << (isPaused ? "Paused" : "Resumed") << std::endl;
        }
    }
}

/**
 * @brief Update game logic
 */
void Game::update(float dt) {
    if (isPaused || isGameOver) return;

    // Update player movement
    if (player) {
        Player::movePlayer(*player, dt);
    }

    
    //sf::Vector2i playerPos = player->getPosition();
    sf::Vector2f fPos = player->getPosition();
    sf::Vector2i playerPos(static_cast<int>(fPos.x), static_cast<int>(fPos.y));

    Bullet::shoot(playerPos, dt, bulletTexture);  

    for (size_t i = 0; i < Bullet::bullets.size(); ++i)
    {
        Bullet* b = Bullet::bullets[i];
        b->update(dt);

        if (!b->isAlive())
        {
            delete b;
            Bullet::bullets.erase(Bullet::bullets.begin() + i);
            i--;  // Important: don't skip next bullet
            std::cout << "[Game] Bullet removed (off-screen)\n";
        }
    }
    for (int i = (int)bulletObj.bullets.size() - 1; i >= 0; i--) {
        Bullet* bullet = bulletObj.bullets[i];
        bullet->update(dt);
        if (!bullet->isAlive()) {
            sf::Vector2i intPos = bullet->getPosition();
        sf::Vector2f floatPos(static_cast<float>(intPos.x), static_cast<float>(intPos.y));  // safe access
            std::cout << "The x value for the bullet = " << floatPos.x
                << " and the y value for the bullet = " << floatPos.y << '\n';
    delete bullet;
    bulletObj.bullets.erase(bulletObj.bullets.begin() + i);
    std::cout << "[Game] Bullet removed (off-screen)" << std::endl;
                    }
    }
    

    
    // Update mushrooms
    for (auto mushroom : mushrooms) {
        if (mushroom) {
            mushroom->update();
        }
    }
    
    // handleCollisions();

    // Update UI
    updateUI();

    // Check game over
    checkGameOver();

    // Debug print
    static int frameCount = 0;
    if (++frameCount % 60 == 0) {
        debugPrint();
    }
}

/**
 * @brief Render all game objects
 */
void Game::render() {
    window.draw(background);

    // Draw mushrooms
    for (auto mushroom : mushrooms) {
        if (mushroom) window.draw(*mushroom);
    }

    for (Bullet* bullet : Bullet::bullets)
    {
        if (bullet )
        {
            window.draw(bullet->mSprite);
        }
    }
    if (player) window.draw(*player);

    // Draw UI text
    window.draw(scoreText);
    window.draw(livesText);
    window.draw(levelText);
}

// ===== STATE MANAGEMENT =====
GameState Game::getState() const { return currentState; }
void Game::setState(GameState newState) {
    if (newState != currentState) {
        currentState = newState;
        std::cout << "[Game] State changed to " << static_cast<int>(newState) << std::endl;
    }
}

// ===== CLEANUP =====
void Game::cleanup() {
    std::cout << "[Game] cleanup() called" << std::endl;

    if (player != nullptr) {
        delete player;
        player = nullptr;
    }

    for (auto mushroom : mushrooms) {
        if (mushroom != nullptr) delete mushroom;
    }
    mushrooms.clear();

    bulletObj.bullets.clear();

    // if (grid != nullptr) { delete grid; grid = nullptr; }

    std::cout << "[Game] Cleanup completed" << std::endl;
}

// ===== PRIVATE HELPER FUNCTIONS =====
bool Game::loadTextures() {
    if (!playerTexture.loadFromFile("assets/sprites/atlas.png")) {
        logError("Game", "Failed to load player texture");
        return false;
    }

    mushroomTexture = playerTexture;
    bulletTexture = playerTexture;

    std::cout << "[Game] All textures loaded successfully" << std::endl;
    return true;
}


void Game::generateMushrooms() {
    if (grid == nullptr) {
        std::cerr << "[Game] ERROR: Grid not initialized for mushroom generation!" << std::endl;
        return;
    }
    int mushroomCount = 10 + (level * 2);
    for (int i = 0; i < mushroomCount; i++) {
        auto [gridX, gridY] = grid->getRandomEmptyCell();
        sf::Vector2f pixelPos = grid->gridToCenterPixel(gridX, gridY);
        Mushroom* mushroom = new Mushroom(mushroomTexture, sf::IntRect(64,64,32,32),
                                          sf::Vector2i(static_cast<int>(pixelPos.x), static_cast<int>(pixelPos.y)),
                                          4, false);
        grid->setOccupied(gridX, gridY, MUSHROOM);
        mushrooms.push_back(mushroom);
    }
}


// void Game::handleCollisions() { ... }

void Game::checkGameOver() {
    if (lives <= 0) {
        isGameOver = true;
        currentState = GameState::GAME_OVER;
        std::cout << "[Game] GAME OVER! Final score: " << score << std::endl;
    }
}

void Game::updateUI() {
    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(lives));
    levelText.setString("Level: " + std::to_string(level));
}

void Game::debugPrint() const {
    std::cout << "\n[Game] === DEBUG INFO ===" << std::endl;
    std::cout << " Score: " << score << std::endl;
    std::cout << " Lives: " << lives << std::endl;
    std::cout << " Level: " << level << std::endl;
    std::cout << " Bullets: " << bulletObj.bullets.size() << std::endl;
    std::cout << " Mushrooms: " << mushrooms.size() << std::endl;
    if (player) {
        std::cout << " Player pos: (" << player->getPosition().x << ", "
                  << player->getPosition().y << ")" << std::endl;
    }
    std::cout << std::endl;
}
