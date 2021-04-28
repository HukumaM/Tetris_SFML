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

void UpdateButton(Button &button, float x_pos, float y_pos)
{
    if (button.selected)
    {
        EditTextContent(button.text, button.text.getString(),
                        60, Color_Combination::button_pressed);
        EditTextPosition(button.text, x_pos, y_pos);
    }
    else
    {
        EditTextContent(button.text, button.text.getString(),
                        50, Color_Combination::button);
        EditTextPosition(button.text, x_pos, y_pos);
    }
}