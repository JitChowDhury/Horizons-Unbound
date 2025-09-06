#include <iostream>
#include "Player.h"

Player::Player()
{
	if (texture.loadFromFile("assets/textures/player.png"))
	{
		std::cout << "Player Sprite failed to load" << std::endl;
	}
	sprite.setTexture(texture);

	int frameIndex = 0;
	int frameWidth = 51;
	int frameHeight = 45;

	sprite.setTextureRect(sf::IntRect(frameIndex * frameWidth, 0, frameWidth, frameHeight));

}

void Player::Update(float deltaTime)
{

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
