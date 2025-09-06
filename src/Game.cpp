#include "Game.h"

Game::Game():window(sf::VideoMode(800, 600), "Horizons Unbound"),deltaTime(0.f)
{
	window.setFramerateLimit(60);

    sf::Image icon;
    if (icon.loadFromFile("assets/textures/logo.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
}

void Game::Update()
{
    deltaTime = clock.restart().asSeconds();
    player.Update(deltaTime);
}

void Game::HandleEvent()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::Render()
{
    window.clear(sf::Color::Black);
    player.Draw(window);
    window.display();
}

void Game::Run()
{
    while (window.isOpen()) {

        Update();
        HandleEvent();
        Render();
        
    }

}
