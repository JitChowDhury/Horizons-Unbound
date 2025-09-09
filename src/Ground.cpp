#include <iostream>
#include "Ground.h"

Ground::Ground()
{
	if (!groundTexture.loadFromFile("assets/textures/ground.png"))
	{
		std::cout << "Ground Texture Not Loaded" << std::endl;
	}

	groundSprite1.setTexture(groundTexture);
    groundSprite1.setColor(sf::Color(180, 200, 255));
	groundSprite1.setTextureRect(sf::IntRect(0, 194, 927, 466));
    sf::FloatRect bounds = groundSprite1.getLocalBounds();
    groundSprite1.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    groundSprite2 = groundSprite1;
    groundSprite1.setPosition(bounds.width / 2.f, 700.f);
    float width = groundSprite1.getGlobalBounds().width;
    groundSprite2.setPosition(groundSprite1.getPosition().x + width, 700.f);


}

void Ground::Update(float deltaTime, float scrollSpeed)
{
    float moveX = -scrollSpeed * deltaTime;
    groundSprite1.move(moveX, 0);
    groundSprite2.move(moveX, 0);

    float width = groundSprite1.getGlobalBounds().width;

    
    if (groundSprite1.getPosition().x + width / 2.f < 0)
    {
        groundSprite1.setPosition(groundSprite2.getPosition().x + width, groundSprite1.getPosition().y);
    }

  
    if (groundSprite2.getPosition().x + width / 2.f < 0)
    {
        groundSprite2.setPosition(groundSprite1.getPosition().x + width, groundSprite2.getPosition().y);
    }
}

void Ground::Draw(sf::RenderWindow& window)
{
   
    window.draw(groundSprite1);
    window.draw(groundSprite2);

    
    sf::FloatRect bounds = groundSprite1.getGlobalBounds();

    sf::RectangleShape border;
    border.setPosition(bounds.left, bounds.top);
    border.setSize(sf::Vector2f(bounds.width, bounds.height));


    border.setFillColor(sf::Color::Transparent);   
    border.setOutlineColor(sf::Color::Red);        
    border.setOutlineThickness(2.f);               

   
    //window.draw(border);
}


float Ground::spritePosition()
{
    return groundSprite1.getGlobalBounds().top;
}
