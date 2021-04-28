#include <cmath>

#include "Tetromino.hpp"

Tetromino::Tetromino(int16_t number_player)
    : m_number_player(number_player)
{
}

Tetromino::~Tetromino()
{
}

void Tetromino::Create()
{
    m_color = m_list_figures.front();

    m_sprite.setTextureRect(
        sf::IntRect(m_color * 18, 0, 18, 18));
    m_sprite_shadow.setTextureRect(
        sf::IntRect(m_color * 18, 0, 18, 18));

    m_figure = shapes.at(m_color).first;
    m_point_rotation = shapes.at(m_color).second;

    m_sprite.setScale(2.f, 2.f);
    m_sprite_shadow.setScale(2.f, 2.f);
}

void Tetromino::CreateNextFigure()
{
    m_list_figures.pop_front();
    m_list_figures.push_back(dist(random));
}

void Tetromino::Init(const sf::Texture &texture,
                     const sf::Texture &texture_shadow)
{
    m_sprite.setTexture(texture);
    m_sprite_shadow.setTexture(texture_shadow);

    m_list_figures.push_back(dist(random));
    m_list_figures.push_back(dist(random));

    Create();
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
    this->m_sprite_shadow.setTextureRect(sf::IntRect(m_color * 18, 0, 18, 18));
    for (const auto point : this->m_shadow)
    {
        this->m_sprite_shadow.setPosition(point.x * 36 + (m_number_player ? 540 : 0), point.y * 36);
        window.draw(this->m_sprite_shadow);
    }

    m_sprite.setScale(2.f, 2.f);
    this->m_sprite.setTextureRect(sf::IntRect(m_color * 18, 0, 18, 18));
    for (const auto point : this->m_figure)
    {
        this->m_sprite.setPosition(point.x * 36 + (m_number_player ? 540 : 0), point.y * 36);
        window.draw(this->m_sprite);
    }
    
    m_sprite.setScale(1.f, 1.f);
    m_sprite.setTextureRect(sf::IntRect(m_list_figures.back() * 18, 0, 18, 18));
    for (const auto point : shapes.at(m_list_figures.back()).first)
    {
        m_sprite.setPosition(414 + (point.x - 3) * 18 + (m_number_player ? 540 : 0), 155 + point.y * 18);
        window.draw(m_sprite);
    }
}