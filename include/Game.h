#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock clock;
public:
	Game();
	void Update();
	void HandleEvent();
	void Render();
	void Run();
};