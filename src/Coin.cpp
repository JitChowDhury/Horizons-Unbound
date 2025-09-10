#include "Coin.h"


Coin::Coin(const Player& player):animation(sprite,0.15f),isCollected(false)
{

	if (texture.loadFromFile("assets/textures/coin.png"))
	{

	}
	sprite.setTexture(texture);
	sprite.setPosition(
		player.GetGlobalBounds().left + player.GetGlobalBounds().width / 2.f - sprite.getGlobalBounds().width / 2.f,
		player.GetGlobalBounds().top - sprite.getGlobalBounds().height - 10.f
	);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	for (int i = 0; i < 5; i++)
	{
		animation.AddFrame(sf::IntRect(i * 16, 0, 16, 16));
	}

}

void Coin::Update(float deltaTime, float scrollSpeed)
{
	animation.Update(deltaTime);
}

void Coin::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

sf::FloatRect Coin::GetBounds()
{
	return sf::FloatRect();
}
