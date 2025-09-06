#include <SFML/Graphics.hpp>

class Player
{
private:
	//will implement texture later
	sf::Sprite sprite;
	sf::Texture texture;


	sf::Vector2f position;
	sf::Vector2f velocity;

public:
	Player();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};