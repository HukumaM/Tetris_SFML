//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 02.04.2021
//  Description : A class describing a game field
//-----------------------------------------------------------------------

#pragma once

#include <vector>
#include <cinttypes>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Point.hpp"
#include "Score.hpp"

class Field
{
private:
    enum Warning
    {
        MOVEMENT_ALLOWED = 1,
        GOING_OUT_OF_BOUNDS = 0,
        COLLISION_WITH_CELLS = 0
    };

private:
    static const int16_t WIDTH_FIELD{10};
    static const int16_t HEIGHT_FIELD{20};

    std::vector<std::vector<int16_t>> m_field;

    int16_t m_number_player;

private:
    sf::Sprite m_sprite;

public:
    Field(int16_t number_player);
    ~Field();

    void Init(const sf::Texture &texture);

    //  Get the cell color
    //  @param  x       x-axis coordinate
    //  @param  y       y-axis coordinate
    //  @return         Cell color or zero if the cell is empty
    inline const int16_t
    GetCellColor(int16_t x, int16_t y) const
    {
        return this->m_field.at(y).at(x);
    }

    //  @param  x       x-axis coordinate
    //  @param  y       y-axis coordinate
    bool
    PermissibilityMovement(const std::vector<Point> &figure,
                           int16_t x, int16_t y) const;

    std::pair<int16_t, int16_t>
    ReturnToField(const std::vector<Point> &figure);

    bool
    FigureOnCells(const std::vector<Point> &shape);

    void
    PlaceFigureOnField(const std::vector<Point> &figure,
                       const int16_t color);

    bool ClearLines(Score& score);
    
    void Draw(sf::RenderWindow &window);
};