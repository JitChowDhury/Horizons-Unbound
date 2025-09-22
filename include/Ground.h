#pragma once
#include <SFML/Graphics.hpp>

class Ground
{
private:
	sf::Sprite groundSprite1;
	sf::Sprite groundSprite2;
	sf::Texture groundTexture;
public:
	Ground();
	void Update(float deltaTime, float scrollSpeed);
	void Draw(sf::RenderWindow& window);
	float spritePosition();  
	void Reset();
};