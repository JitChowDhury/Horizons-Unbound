#pragma once
#include <SFML/Graphics.hpp>

class Ground
{
private:
	sf::Sprite groundSprite;
	sf::Texture groundTexture;
public:
	Ground();
	void Draw(sf::RenderWindow& window);
	float spritePosition();
};