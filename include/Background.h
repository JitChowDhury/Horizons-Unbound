#include <SFML/Graphics.hpp>

class Background
{
private:
	sf::Sprite sprite;
	sf::Sprite sprite2;
	sf::Texture texture;
	float scrollSpeed;
	float scaledWidth;
	sf::Vector2f position;
public:
	Background(const std::string& textureFile,float scrollSpeed);
	void Update(float deltaTime, float baseScrollSpeed);
	void Draw(sf::RenderWindow& window);
};