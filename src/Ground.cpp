#include <iostream>
#include "Ground.h"

Ground::Ground()
{
	if (!groundTexture.loadFromFile("assets/textures/ground.png"))
	{
		std::cout << "Ground Texture Not Loaded" << std::endl;
	}

	groundSprite.setTexture(groundTexture);
    groundSprite.setColor(sf::Color(180, 200, 255));
	groundSprite.setTextureRect(sf::IntRect(0, 194, 927, 466));
    sf::FloatRect bounds = groundSprite.getLocalBounds();
    groundSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    groundSprite.setPosition(bounds.width / 2.f, 700.f);
}

void Ground::Draw(sf::RenderWindow& window)
{
   
    window.draw(groundSprite);

    
    sf::FloatRect bounds = groundSprite.getGlobalBounds();

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
    return groundSprite.getGlobalBounds().top;
}
