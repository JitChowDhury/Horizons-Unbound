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
    sprite.move(-speed * dt, 0.f);
}

void Obstacle::Draw(sf::RenderWindow& window)
{
  
    window.draw(sprite);


    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::RectangleShape rect;
    rect.setPosition(bounds.left, bounds.top);
    rect.setSize(sf::Vector2f(bounds.width, bounds.height));
    rect.setFillColor(sf::Color::Transparent); 
    rect.setOutlineColor(sf::Color::Red);     
    rect.setOutlineThickness(2.f);           

}

bool Obstacle::IsOffscreen() const
{
	return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
}

sf::FloatRect Obstacle::GetBounds() const
{
	return sprite.getGlobalBounds();
}
