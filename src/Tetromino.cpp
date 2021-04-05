#include "Tetromino.hpp"

#include <cmath>

Tetromino::Tetromino()
{
}
Tetromino::~Tetromino()
{
}

bool Tetromino::Create()
{
    this->m_color = 1 + this->dist(this->random) % 7;
    this->m_sprite.setTextureRect(
        sf::IntRect(this->m_color * 18, 0, 18, 18));

    this->m_figure = shapes.at(this->m_color).first;
    this->m_point_rotation = shapes.at(this->m_color).second;

    this->m_sprite.setScale(2.f, 2.f);
    return true;
}

void Tetromino::Init(const sf::Texture &texture)
{
    this->m_sprite.setTexture(texture);
    this->Create();
}

void Tetromino::Move(int16_t x_offset, int16_t y_offset)
{
    for (auto &point : this->m_figure)
    {
        point.x += x_offset;
        point.y += y_offset;
    }
    this->m_point_rotation.x += x_offset;
    this->m_point_rotation.y += y_offset;
}

bool Tetromino::Rotate(Field &field)
{
    const auto figure_state = m_figure;
    const auto rotation_state = m_point_rotation;

    for (auto &point : m_figure)
    {
        auto x = point.x - m_point_rotation.x;
        auto y = point.y - m_point_rotation.y;
        point.x = std::ceil(m_point_rotation.x - y);
        point.y = std::ceil(m_point_rotation.y + x);
    }

    auto xy = field.ReturnToField(m_figure);
    do
    {
        this->Move(xy.first, xy.second);
        m_point_rotation.x += xy.first;
        m_point_rotation.y += xy.second;
        xy = field.ReturnToField(m_figure);
    } while (xy.first || xy.second);

    if (field.FigureOnCells(m_figure))
    {
        for (int16_t y{1}; y >= -1; --y)
        {
            if (field.PermissibilityMovement(m_figure, LEFT, y))
            {
                this->Move(LEFT, y);
                break;
            }
            if (field.PermissibilityMovement(m_figure, RIGTH, y))
            {
                this->Move(RIGTH, y);
                break;
            }
        }
    }

    if (field.FigureOnCells(m_figure))
    {
        this->m_figure = figure_state;
        this->m_point_rotation = rotation_state;
        return false;
    }
    else
    {
        return true;
    }
}

void Tetromino::ShadowDisplay(Field &field)
{
    m_shadow = this->m_figure;
    while (field.PermissibilityMovement(m_shadow, 0, DOWN))
    {
        for (auto &point : this->m_shadow)
        {
            point.y += DOWN;
        }
    }
}

void Tetromino::Draw(sf::RenderWindow &window)
{
    this->m_sprite.setTextureRect(sf::IntRect(m_color * 18, 0, 18, 18));
    for(const auto point : this->m_shadow)
    {
        this->m_sprite.setPosition(point.x * 36, point.y * 36);
        window.draw(this->m_sprite);
    }
    
    this->m_sprite.setTextureRect(sf::IntRect(2, 2, 15, 15));
    for (const auto point : this->m_shadow)
    {
        this->m_sprite.setPosition(point.x * 36 + 2, point.y * 36 + 2);
        window.draw(this->m_sprite);
    }
    
    this->m_sprite.setTextureRect(sf::IntRect(m_color * 18, 0, 18, 18));
    for (const auto point : this->m_figure)
    {
        this->m_sprite.setPosition(point.x * 36, point.y * 36);
        window.draw(this->m_sprite);
    }
}

const std::vector<Point> &
Tetromino::GetFigure() const
{
    return this->m_figure;
}