#pragma once

#include <config.hpp>

namespace Tetris
{
    class Background
    {
    private:
        sf::Texture texture;
        sf::Sprite sprite;

    public:
        Background();
        ~Background();

        void Draw(sf::RenderWindow &window);
    };
}