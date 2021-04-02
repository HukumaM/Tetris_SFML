#include "Background.hpp"

namespace Tetris
{
    Background::Background()
    {
        if (!this->texture.loadFromFile("img/background_line.jpg"))
        {
            std::clog << "Can't load background_line.jpg" << std::endl;
        }
        this->texture.setRepeated(true);
        this->sprite.setTexture(this->texture);
        this->sprite.setTextureRect(sf::IntRect(0, 0, 2200, 4400));
        this->sprite.setScale(
            WIDTH_FIELD_PIXELS / 2200,
            HEIGHT_FIELD_PIXELS / 4400); 
    }

    Background::~Background()
    {
    }

    void Background::Draw(sf::RenderWindow &window)
    {
        window.draw(this->sprite);
    }
}