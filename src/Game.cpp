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
