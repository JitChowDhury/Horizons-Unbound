#include <iostream>
#include "Player.h"


Player::Player():position(sf::Vector2f(400,300)),velocity(sf::Vector2f(0.f,0.f)), speed(200.f), jumpForce(500.0f)
, gravity(1000.0f),isGrounded(true),animation(sprite,0.1f)
{
	if (!texture.loadFromFile("assets/textures/player.png"))
	{
		std::cout << "Player Sprite failed to load" << std::endl;
	}
	sprite.setTexture(texture);

	
	int frameWidth = 51;
	int frameHeight = 45;
	sprite.setScale(2.f, 2.f);
	float groundTop = ground.spritePosition() + 12.f;
	float playerHeight = sprite.getGlobalBounds().height;
	sprite.setPosition(400 - sprite.getGlobalBounds().width / 2, groundTop - playerHeight);
	for (int i = 0; i < 8; i++)
	{
		animation.AddFrame(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
	}
	

	

}

void Player::Update(float deltaTime)
{
	animation.Update(deltaTime);
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

	sf::FloatRect bounds = sprite.getGlobalBounds();
	sf::RectangleShape rect;
	rect.setPosition(bounds.left, bounds.top);
	rect.setSize(sf::Vector2f(bounds.width, bounds.height));
	rect.setFillColor(sf::Color::Transparent); // no fill
	rect.setOutlineColor(sf::Color::Red);      // red outline
	rect.setOutlineThickness(2.f);             // thickness of the line

	window.draw(rect);
}

sf::FloatRect Player::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

sf::FloatRect Player::GetCollisionBounds() const
{
	sf::FloatRect global = sprite.getGlobalBounds();

	
	float shrinkX = global.width * 0.2f;   
	float shrinkY = global.height * 0.1f;

	return sf::FloatRect(
		global.left + shrinkX,
		global.top + shrinkY,
		global.width - 2 * shrinkX,
		global.height - 2 * shrinkY
	);
}


