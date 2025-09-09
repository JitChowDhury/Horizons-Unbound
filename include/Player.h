#pragma once
#include <SFML/Graphics.hpp>
#include "Ground.h"
#include "Animation.h"


class Player
{
private:
	//will implement texture later
	sf::Sprite sprite;
	sf::Texture texture;

	Animation animation;

	sf::Vector2f position;
	sf::Vector2f velocity;

	float speed;
	float jumpForce;
	float gravity;
	bool isGrounded;

	Ground ground;

public:
	Player();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};