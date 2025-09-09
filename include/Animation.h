#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
private:
	sf::Sprite& sprite;
	std::vector<sf::IntRect> frames;
	float frameTime;
	float elapsedTime;
	unsigned int currentFrame;
public:
	Animation(sf::Sprite& targetSprite, float frameDuration = 0.1f);
	void AddFrame(const sf::IntRect& frame);
	void Update(float deltaTime);
};