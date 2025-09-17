#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "Ground.h"
#include "Background.h"
#include "Coin.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock clock;

	sf::Music mainMusic;

	float deltaTime;
	float baseScrollSpeed;
	std::vector<Background> backgrounds;
	Player player;
	Ground ground;


	std::vector<std::unique_ptr<Coin>> coins;
	sf::Clock coinSpawnClock;
	float coinSpawnInterval = 2.f; 
public:
	Game();
	void Update();
	void HandleEvent();
	void Render();
	void Run();
};