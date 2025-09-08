#include <iostream>
#include "Player.h"


Player::Player():position(sf::Vector2f(400,300)),velocity(sf::Vector2f(0.f,0.f)), speed(200.f), jumpForce(400.0f), gravity(1000.0f),isGrounded(true)
{
	if (!texture.loadFromFile("assets/textures/player.png"))
	{
		std::cout << "Player Sprite failed to load" << std::endl;
	}
	sprite.setTexture(texture);

	int frameIndex = 0;
	int frameWidth = 51;
	int frameHeight = 45;

	sprite.setTextureRect(sf::IntRect(frameIndex * frameWidth, 0, frameWidth, frameHeight));
	sprite.setScale(2.f, 2.f);
	sprite.setPosition(position);
	

}

void Player::Update(float deltaTime)
{

	velocity.x = 0;
	if (!isGrounded)
	{
	velocity.y += gravity * deltaTime;


	if (sprite.getPosition().y+sprite.getGlobalBounds().height >= ground.spritePosition()+10.f)
	{
		velocity.y = 0;                                  
		isGrounded = true;
	}
	}

		//velocity.x = +speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded)
	{
		velocity.y = -jumpForce;
		isGrounded = false;
	}

	sprite.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
