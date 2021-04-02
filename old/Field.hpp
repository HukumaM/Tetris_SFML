#pragma once

#include "Point.hpp"
#include "Score.hpp"
#include "config.hpp"

#include <algorithm>
#include <vector>
#include <cstdint>

namespace Tetris
{
    class Field
    {
    private:
        static std::vector<std::vector<std::int16_t>> field;

        sf::Texture texture;
        sf::Sprite sprite;

       
    public:
        Field();
        ~Field();

        static bool
        PermissibilityMovement(const std::vector<Point<std::int16_t>> &shape,
                               std::int16_t x, std::int16_t y);

        static std::pair<int16_t, int16_t>
        ReturnToField(const std::vector<Point<std::int16_t>> &shape);

        static bool 
        ShapeOnCellsField(const std::vector<Point<int16_t>> &shape);

        void 
        ShapeToField(const std::vector<Point<std::int16_t>> &shape,
                          const int16_t color);
        void
        ClearingLines(Score &score);

        void
        Draw(sf::RenderWindow &window);
    };
}