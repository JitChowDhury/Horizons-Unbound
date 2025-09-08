#include <iostream>
#include "Background.h"

Background::Background(const std::string& textureFile, float scrollSpeed):scrollSpeed(scrollSpeed),position(sf::Vector2f(0,0))
{
    if (!texture.loadFromFile(textureFile))
    {
       
        std::cerr << "Failed to load texture: " << textureFile << std::endl;
    }

    sprite.setTexture(texture);
    sprite2.setTexture(texture);


    // --- Scale to fit 800x600 ---
    float scaleX = 800.f / texture.getSize().x;
    float scaleY = 600.f / texture.getSize().y;

    sprite.setScale(scaleX, scaleY);
    sprite2.setScale(scaleX, scaleY);

    float scaledWidth = texture.getSize().x * scaleX;

    // --- Positioning the two sprites side by side ---
    sprite.setPosition(position);
    sprite2.setPosition(position.x + 800.f, position.y); 

    this->scaledWidth = scaledWidth;
}

void Background::Update(float deltaTime, float baseScrollSpeed)
{
    sprite.move(-baseScrollSpeed * scrollSpeed * deltaTime, 0);
    sprite2.move(-baseScrollSpeed * scrollSpeed * deltaTime, 0);

    if (sprite.getPosition().x + scaledWidth < 0)
    {
        sprite.setPosition(sprite2.getPosition().x + scaledWidth, 0);
    }
    else if (sprite2.getPosition().x + scaledWidth < 0)
    {
        sprite2.setPosition(sprite.getPosition().x + scaledWidth, 0);
    }
}  


void Background::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(sprite2);
}
