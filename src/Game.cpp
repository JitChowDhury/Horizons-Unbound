#include "Game.h"
#include <iostream>

void Game::PlayCoinSound()
{
    float pitch = 0.8f + static_cast<float>(std::rand()) / RAND_MAX * 0.4f;
    coinSound.setPitch(pitch);

    coinSound.play();
}

Game::Game() : window(sf::VideoMode(800, 600), "Horizons Unbound"), deltaTime(0.f), baseScrollSpeed(200.f),score(0), gameState(GameState::Playing)
{
    backgrounds.reserve(10);
    window.setFramerateLimit(60);

    sf::Image icon;
    if (icon.loadFromFile("assets/textures/logo.png"))
    {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    if (!font.loadFromFile("assets/fonts/bubbleBobble.ttf"))
    {
        std::cerr << "Font not Found!" << std::endl;
    }

    if (!coinSoundBuffer.loadFromFile("assets/sounds/coin.mp3"))
    {
        std::cerr << "Sound not Found!" << std::endl;
    }
    coinSound.setBuffer(coinSoundBuffer);
    std::srand(static_cast<unsigned>(std::time(nullptr)));



    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    scoreText.setString("Score: 0");

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER!\nPress R to Restart\nPress Esc to Quit");
    gameOverText.setPosition(200.f, 200.f);

    backgrounds.emplace_back("assets/textures/backgrounds/1.png", 0.2f);
    backgrounds.emplace_back("assets/textures/backgrounds/2.png", 0.4f);
    backgrounds.emplace_back("assets/textures/backgrounds/3.png", 0.6f);
    backgrounds.emplace_back("assets/textures/backgrounds/4.png", 0.8f);
    backgrounds.emplace_back("assets/textures/backgrounds/5.png", 1.0f);
    backgrounds.emplace_back("assets/textures/backgrounds/6.png", 1.2f);
    backgrounds.emplace_back("assets/textures/backgrounds/7.png", 1.4f);
    backgrounds.emplace_back("assets/textures/backgrounds/8.png", 1.6f);
    //backgrounds.emplace_back("assets/textures/backgrounds/9.png", 1.8f);
    backgrounds.emplace_back("assets/textures/backgrounds/10.png", 1.8f);


    sf::ContextSettings settings = window.getSettings();

    if (!mainMusic.openFromFile("assets/sounds/mainMusic.mp3"))
    {
        std::cerr << "No Music Found" << std::endl;
    }

    mainMusic.setVolume(50.f);
    mainMusic.setLoop(true);
    mainMusic.play();


}

void Game::Update()
{
    if (gameState == GameState::GameOver) return;


    deltaTime = clock.restart().asSeconds();
    player.Update(deltaTime);
    ground.Update(deltaTime, baseScrollSpeed);
    for (auto& bg : backgrounds) {
        bg.Update(deltaTime, baseScrollSpeed);
    }
    if (coinSpawnClock.getElapsedTime().asSeconds() > coinSpawnInterval)
    {
        coinSpawnClock.restart();

        float groundY = ground.spritePosition();
        float baseX = 800 + (std::rand() % 200);
        float y = groundY - (30); // random above ground

        int groupSize = 1 + (std::rand() % 5);


        for (int i = 0; i < groupSize; i++)
        {
            coins.push_back(std::make_unique<Coin>(sf::Vector2f(baseX + i * 40.f, y)));
        }
    }

    for (auto it = coins.begin(); it != coins.end(); )
    {
        sf::FloatRect playerBounds = player.GetGlobalBounds();
        sf::Vector2f playerCenter(
            playerBounds.left + playerBounds.width / 2.f,
            playerBounds.top + playerBounds.height / 2.f
        );



        (*it)->Update(deltaTime, baseScrollSpeed);
        sf::FloatRect coinBounds = (*it)->GetBounds();
        sf::Vector2f coinCenter(
            coinBounds.left + coinBounds.width / 2.f,
            coinBounds.top + coinBounds.height / 2.f
        );

        float dx = playerCenter.x - coinCenter.x;
        float dy = playerCenter.y - coinCenter.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        float pickupRadius = 30.f;
        if (distance < pickupRadius)
        {

            score += 5;
            PlayCoinSound();
            scoreText.setString("Score: " + std::to_string(score));
            it = coins.erase(it);
        }

        if ((*it)->IsOffscreen()) {
            it = coins.erase(it);
        }
        else {
            ++it;
        }

    }


    if (obstacleSpawnClock.getElapsedTime().asSeconds() > obstacleSpawnInterval)
    {
        obstacleSpawnClock.restart();

        float groundY = ground.spritePosition();
        float x = 800 + (std::rand() % 200);
        float y = groundY; // sits on ground

        sf::FloatRect newObstacleRect(x, y, 400.f, 285.f);


        // Check overlap with coins
        bool overlapsCoin = false;
        for (auto& coin : coins) {
            if (coin->GetBounds().intersects(newObstacleRect)) {
                overlapsCoin = true;
                break;
            }
        }

        if (!overlapsCoin) {
            obstacles.push_back(std::make_unique<Obstacle>(sf::Vector2f(x, y)));
        }
    }
    for (auto it = obstacles.begin(); it != obstacles.end(); )
    {
        (*it)->Update(deltaTime, baseScrollSpeed);
        if ((*it)->IsOffscreen()) {
            it = obstacles.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto& obs : obstacles) {
        if (player.GetCollisionBounds().intersects(obs->GetBounds())) {
            gameState = GameState::GameOver;
        }
    }
}

void Game::HandleEvent()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (gameState == GameState::GameOver && event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::R)
                Restart();
            else if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }
    }
}


void Game::Render()
{
    window.clear(sf::Color(0, 0, 0, 0));

    for (auto& bg : backgrounds)
        bg.Draw(window);

    if (gameState == GameState::Playing)
    {
        player.Draw(window);
        for (auto& obs : obstacles)
            obs->Draw(window);
        ground.Draw(window);
        for (auto& c : coins)
            c->Draw(window);

        window.draw(scoreText);
    }
    else if (gameState == GameState::GameOver)
    {
        window.draw(gameOverText);
        window.draw(scoreText); 
    }

    window.display();
}


void Game::Run()
{
    while (window.isOpen())
    {

        Update();
        HandleEvent();
        Render();
    }
}
void Game::Restart()
{
    score = 0;
    scoreText.setString("Score: 0");

    coins.clear();
    obstacles.clear();

    coinSpawnClock.restart();
    obstacleSpawnClock.restart();

    player.Reset();
    ground.Reset();

    gameState = GameState::Playing;
}
