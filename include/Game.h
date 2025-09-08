#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Ground.h"
#include "Background.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock clock;

	float deltaTime;
	float baseScrollSpeed;
	std::vector<Background> backgrounds;
	Player player;
	Ground ground;
public:
	Game();
	void Update();
	void HandleEvent();
	void Render();
	void Run();
};