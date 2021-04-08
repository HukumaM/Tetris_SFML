//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 02.04.2021
//  Description : A class describing a tetramino
//-----------------------------------------------------------------------

#pragma once

#include <vector>
#include <random>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Point.hpp"
#include "Field.hpp"

enum Direction
{
    LEFT = -1, 
    RIGTH = 1,
    DOWN = 1,
    UP = -1
};

struct Shape
{
    std::vector<Point> figure;
    Point rotation_point;
};

static const std::vector<std::pair<std::vector<Point>, Point>> shapes{
    {{}, {}},                                         // Empty
    {{{3, 0}, {4, 0}, {5, 0}, {6, 0}}, {4.5f, 0.5f}}, // I
    {{{3, 1}, {4, 1}, {4, 0}, {5, 0}}, {4.f, 1.f}},   // S
    {{{3, 0}, {4, 0}, {4, 1}, {5, 1}}, {4.f, 1.f}},   // Z
    {{{3, 0}, {3, 1}, {4, 1}, {5, 1}}, {4.f, 1.f}},   // L
    {{{3, 1}, {4, 1}, {5, 1}, {5, 0}}, {4.f, 1.f}},   // J
    {{{3, 1}, {4, 1}, {4, 0}, {5, 1}}, {4.f, 1.f}},   // T
    {{{4, 0}, {5, 0}, {4, 1}, {5, 1}}, {4.5f, 0.5f}}  // O
};

class Tetromino
{
private:
    sf::Sprite m_sprite;

private:
    std::vector<Point> m_figure;
    std::vector<Point> m_shadow;
    Point m_point_rotation;
    int16_t m_color;

private:
    std::random_device random;
    std::uniform_int_distribution<int16_t> dist{1, INT16_MAX};

private:
    void GetShadow();

public:
    Tetromino();
    ~Tetromino();

    void Create();
    void Init(const sf::Texture &texture);
    void Move(int16_t x_offset, int16_t y_offset);
    bool Rotate(Field& field);
    void ShadowDisplay(Field &field);
    void Draw(sf::RenderWindow &window);

    const std::vector<Point> &
    GetFigure() const;

    inline const int16_t
    GetColor() const
    {
        return this->m_color;
    }
};