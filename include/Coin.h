#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"


class Coin
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;

	bool isCollected;

	Animation animation;
public:
	Coin(const Player& player);
	void Update(float deltaTime, float scrollSpeed);
	void Draw(sf::RenderWindow& window);
	sf::FloatRect GetBounds();
};