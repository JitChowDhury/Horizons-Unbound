#include "Game.h"

Game::Game():window(sf::VideoMode(800, 600), "Horizons Unbound")
{
	window.setFramerateLimit(60);

    sf::Image icon;
    if (icon.loadFromFile("assets/textures/logo.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
}

void Game::Update()
{
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
