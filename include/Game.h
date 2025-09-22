#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "Ground.h"
#include "Background.h"
#include "Coin.h"
#include "Obstacle.h"

class Game
{
private:
    enum class GameState { Playing, GameOver };
    GameState gameState;

    sf::RenderWindow window;
    sf::Clock clock;

    sf::Music mainMusic;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Font font;

    sf::SoundBuffer coinSoundBuffer;
    sf::Sound coinSound;

    float deltaTime;
    float baseScrollSpeed;
    int score;

    std::vector<Background> backgrounds;
    Player player;
    Ground ground;

    std::vector<std::unique_ptr<Coin>> coins;
    sf::Clock coinSpawnClock;
    float coinSpawnInterval = 2.f;

    std::vector<std::unique_ptr<Obstacle>> obstacles;
    sf::Clock obstacleSpawnClock;
    float obstacleSpawnInterval = 3.f;

    void PlayCoinSound();
    void Restart();

public:
    Game();
    void Update();
    void HandleEvent();
    void Render();
    void Run();
};
