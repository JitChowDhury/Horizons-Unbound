#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Horizons Unbound"), deltaTime(0.f), baseScrollSpeed(200.f)
{
    backgrounds.reserve(10);
    window.setFramerateLimit(60);

    sf::Image icon;
    if (icon.loadFromFile("assets/textures/logo.png"))
    {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

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
        float x = 800 + (std::rand() % 200); // random ahead of screen
        float y = groundY - (40 + std::rand() % 70); // random above ground

        coins.emplace_back(std::make_unique<Coin>(sf::Vector2f(x, y)));
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
            it = coins.erase(it);
        }

        if ((*it)->IsOffscreen()) {
            it = coins.erase(it);
        }
        else {
            ++it;
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
    }
}

void Game::Render()
{
    window.clear(sf::Color(0, 0, 0, 0));
    for (auto it = backgrounds.begin(); it != backgrounds.end(); ++it) {
        it->Draw(window);
    }

    player.Draw(window);
    ground.Draw(window);
    for (auto& c : coins) {
        c->Draw(window);
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
