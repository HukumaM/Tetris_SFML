#include <algorithm>

#include "Field.hpp"

Field::Field(int16_t number_player)
    : m_field(std::vector<std::vector<int16_t>>(20, std::vector<int16_t>(10, 0))),
      m_number_player(number_player)
{
}
Field::~Field()
{
}

void Field::Init(const sf::Texture &texture)
{
    this->m_sprite.setTexture(texture);
    this->m_sprite.setScale(2.f, 2.f);
}

bool Field::PermissibilityMovement(const std::vector<Point> &figure,
                                   int16_t x, int16_t y) const
{
    for (const auto &point : figure)
    {
        if (point.x + x < 0 || point.x + x >= WIDTH_FIELD)
        {
            return GOING_OUT_OF_BOUNDS;
        }
        if (point.y + y < 0 || point.y + y >= HEIGHT_FIELD)
        {
            return GOING_OUT_OF_BOUNDS;
        }
        if (this->m_field.at(point.y + y).at(point.x + x))
        {
            return COLLISION_WITH_CELLS;
        }
    }
    return MOVEMENT_ALLOWED;
}

std::pair<int16_t, int16_t> 
Field::ReturnToField(const std::vector<Point> &figure)
{
    int16_t x{0}, y{0};

    for (const auto &point : figure)
    {
        if (point.x < 0)
        {
            x = 1;
        }
        else if (point.x >= 10)
        {
            x = -1;
        }
        if (point.y < 0)
        {
            y = 1;
        }
        else if (point.y >= 20)
        {
            y = -1;
        }
    }
    return {x, y};
}

bool Field::FigureOnCells(const std::vector<Point> &figure)
{
    return std::any_of(figure.cbegin(), figure.cend(), [&](const auto point) {
        return m_field.at(point.y).at(point.x);
    });
}

void Field::PlaceFigureOnField(const std::vector<Point> &figure,
                               const int16_t color)
{
    for (const auto point : figure)
    {
        this->m_field.at(point.y).at(point.x) = color;
    }
}

bool Field::ClearLines(Score &score)
{
    auto remove_line = std::remove_if(std::rbegin(m_field), std::rend(m_field), [&](auto line) {
        return std::all_of(std::begin(line), std::end(line), [](auto cell) {
            return cell;
        });
    });
    auto flag_clear{std::distance(remove_line, std::rend(m_field))};
    score.UpdateScores(flag_clear);

    std::transform(remove_line, std::rend(m_field), remove_line, [&](auto &line) {
        return line = std::vector<int16_t>(WIDTH_FIELD, 0);
    });
    return flag_clear;
}

void Field::Draw(sf::RenderWindow &window)
{
    for (size_t i{0}; i < HEIGHT_FIELD; ++i)
    {
        for (size_t j{0}; j < WIDTH_FIELD; ++j)
        {
            this->m_sprite.setPosition(j * 36 + (m_number_player ? 540 : 0), i * 36);
            this->m_sprite.setTextureRect(sf::IntRect(
                this->m_field.at(i).at(j) * 18, 0, 18, 18));
            window.draw(this->m_sprite);
        }
    }
}