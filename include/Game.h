#include <SFML/Graphics.hpp>

#include "Player.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock clock;

	float deltaTime;

	Player player;
public:
	Game();
	void Update();
	void HandleEvent();
	void Render();
	void Run();
};