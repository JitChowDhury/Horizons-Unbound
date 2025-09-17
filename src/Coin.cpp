#include "Coin.h"

sf::Texture Coin::texture;

Coin::Coin(sf::Vector2f spawnPos):animation(sprite,0.15f),isCollected(false)
{

	if (texture.getSize().x == 0)  
	{
		if (!texture.loadFromFile("assets/textures/coin.png"))
		{
			throw std::runtime_error("Failed to load coin texture!");
		}
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	for (int i = 0; i < 5; i++)
	{
		animation.AddFrame(sf::IntRect(i * 16, 0, 16, 16));
	}

	sprite.setPosition(spawnPos);

}

void Coin::Update(float deltaTime, float scrollSpeed)
{
	animation.Update(deltaTime);
	sprite.move(-scrollSpeed * deltaTime, 0);
}

void Coin::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

sf::FloatRect Coin::GetBounds()
{
	return sprite.getGlobalBounds();
}


bool Coin::IsOffscreen()
{
	return (sprite.getPosition().x + sprite.getGlobalBounds().width < 0);
}
