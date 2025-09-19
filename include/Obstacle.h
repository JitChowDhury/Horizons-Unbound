#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Obstacle
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	Obstacle(const sf::Vector2f& position);
	void Update(float dt, float speed);
	void Draw(sf::RenderWindow& window);
	bool IsOffscreen() const;
	sf::FloatRect GetBounds() const;

};