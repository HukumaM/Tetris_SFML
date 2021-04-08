#include "Support.hpp"

void EditTextContent(sf::Text &text, const sf::String &string, unsigned int size,
                     const sf::Color &color)
{
    text.setString(string);
    text.setCharacterSize(size);
    text.setColor(color);
}

void EditTextPosition(sf::Text &text, float x, float y)
{
    text.setOrigin(text.getLocalBounds().width / 2,
                   text.getLocalBounds().height / 2);
    text.setPosition(x, y);
}