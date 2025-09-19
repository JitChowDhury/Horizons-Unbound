#include "Obstacle.h"

Obstacle::Obstacle(const sf::Vector2f& position) {
	texture.loadFromFile("assets/textures/fence.png");
	sprite.setTextureRect(sf::IntRect(349, 221, 51, 64));
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Obstacle::Update(float dt, float speed)
{
	sprite.move(-speed * dt, 0.f); // scroll left like coins
}

void Obstacle::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool Obstacle::IsOffscreen() const
{
	return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
}

sf::FloatRect Obstacle::GetBounds() const
{
	return sprite.getGlobalBounds();
}
