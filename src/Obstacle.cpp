#include "Obstacle.h"

Obstacle::Obstacle(const sf::Vector2f& position) {
	texture.loadFromFile("assets/textures/fence.png");
	sprite.setTextureRect(sf::IntRect(349, 221, 51, 64));
    sprite.setOrigin(0.f, sprite.getLocalBounds().height);
	sprite.setTexture(texture);
	sprite.setPosition(position.x,position.y+20.f);
}

void Obstacle::Update(float dt, float speed)
{
	sprite.move(-speed * dt, 0.f); // scroll left like coins
}

void Obstacle::Draw(sf::RenderWindow& window)
{
    // Draw the obstacle sprite
    window.draw(sprite);

    // Debug: Draw red bounding box
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::RectangleShape rect;
    rect.setPosition(bounds.left, bounds.top);
    rect.setSize(sf::Vector2f(bounds.width, bounds.height));
    rect.setFillColor(sf::Color::Transparent); // no fill
    rect.setOutlineColor(sf::Color::Red);      // red outline
    rect.setOutlineThickness(2.f);             // thickness of the line

    window.draw(rect);
}

bool Obstacle::IsOffscreen() const
{
	return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
}

sf::FloatRect Obstacle::GetBounds() const
{
	return sprite.getGlobalBounds();
}
