#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color clickColor;
    bool isHovered;

public:
    Button(std::string label, sf::Vector2f pos, sf::Vector2f size, sf::Font &font)
    {
        shape.setPosition(pos);
        shape.setSize(size);
        normalColor = sf::Color(70, 70, 70);
        hoverColor = sf::Color(100, 100, 100);
        clickColor = sf::Color(50, 50, 50);
        shape.setFillColor(normalColor);

        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::White);

        // Center text
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            pos.x + (size.x - textBounds.width) / 2.0f - textBounds.left,
            pos.y + (size.y - textBounds.height) / 2.0f - textBounds.top);

        isHovered = false;
    }

    void update(sf::Vector2i mousePos)
    {
        isHovered = shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
        shape.setFillColor(isHovered ? hoverColor : normalColor);
    }

    bool isClicked(sf::Vector2i mousePos)
    {
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
        window.draw(text);
    }
};