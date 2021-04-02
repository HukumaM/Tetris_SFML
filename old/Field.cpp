#include "Field.hpp"

namespace Tetris
{
    std::vector<std::vector<std::int16_t>> Field::field{HEIGHT_FIELD_CELLS, std::vector<std::int16_t>(WIDTH_FIELD_CELLS)};
    Field::Field()
    {
        if (!this->texture.loadFromFile("img/tetromino.png"))
        {
            std::cerr << "Can't load the image tetromino" << std::endl;
        }
        this->sprite.setTexture(this->texture);
        this->sprite.setScale(CELL_SCALE, CELL_SCALE);
    }
    Field::~Field()
    {
    }

    bool
    Field::PermissibilityMovement(const std::vector<Point<std::int16_t>> &shape,
                                  std::int16_t x, std::int16_t y)
    {
        return std::none_of(shape.begin(), shape.end(), [&](const auto point) {
            return point.x + x < 0 || point.x + x >= WIDTH_FIELD_CELLS ||
                   point.y + y >= HEIGHT_FIELD_CELLS || field.at(point.y + y).at(point.x + x);
        });
    }

    bool
    Field::ShapeOnCellsField(const std::vector<Point<int16_t>> &shape)
    {
        return std::any_of(std::begin(shape), std::end(shape), [&](const auto point) {
            return point.y >= 0 && point.y < HEIGHT_FIELD_CELLS &&
                           point.x >= 0 && point.x < WIDTH_FIELD_CELLS
                       ? field.at(point.y).at(point.x)
                       : false;
        });
    }

    std::pair<int16_t, int16_t>
    Field::ReturnToField(const std::vector<Point<std::int16_t>> &shape)
    {
        using namespace Tetris::ReturnDirection;
        auto x{STAND}, y{STAND};
        for (const auto point : shape)
        {
            if (point.x >= WIDTH_FIELD_CELLS)
            {
                x = X_LEFT;
            }
            else if (point.x < 0)
            {
                x = X_RIGHT;
            }
            if (point.y >= HEIGHT_FIELD_CELLS)
            {
                y = Y_UP;
            }
            else if (point.y < 0)
            {
                y = Y_DOWN;
            }
        }
        if (ShapeOnCellsField(shape) && !x && !y)
        {
            if (PermissibilityMovement(shape, X_LEFT, Y_DOWN))
            {
                x = X_LEFT;
                y = Y_DOWN;
            }
            else if (PermissibilityMovement(shape, X_RIGHT, Y_DOWN))
            {
                x = X_RIGHT;
                y = Y_DOWN;
            }
            else if (PermissibilityMovement(shape, X_LEFT, STAND))
            {
                x = X_LEFT;
            }
            else if (PermissibilityMovement(shape, X_LEFT, Y_UP))
            {
                x = X_LEFT;
                y = Y_UP;
            }
            else if (PermissibilityMovement(shape, STAND, Y_UP))
            {
                y = Y_UP;
            }
            else if (PermissibilityMovement(shape, X_RIGHT, Y_UP))
            {
                x = X_RIGHT;
                y = Y_UP;
            }
            else if (PermissibilityMovement(shape, X_RIGHT, STAND))
            {
                x = X_RIGHT;
            }
            else
            {
                x = STAND;
                y = STAND;
            }
        }
        return std::make_pair(x, y);
    };

    void
    Field::ShapeToField(const std::vector<Point<std::int16_t>> &shape,
                        const int16_t color)
    {
        std::for_each(std::begin(shape), std::end(shape), [&](const auto &point) {
            this->field.at(point.y).at(point.x) = color;
        });
    }

    bool
    FilledLine(const std::vector<std::vector<int16_t>>::reverse_iterator line)
    {
        return std::all_of(std::cbegin(*line), std::cend(*line), [](const auto cell) {
            return cell;
        });
    }

    void Field::ClearingLines(Score &score)
    {
        auto remove_line = std::remove_if(std::rbegin(field), std::rend(field), [&](auto line) {
            return std::all_of(std::begin(line), std::end(line), [](auto cell) {
                return cell;
            });
        });
        score.IncreaseScore(std::distance(remove_line, std::rend(field)));

        std::transform(remove_line, std::rend(field), remove_line, [&](auto &line) {
            return line = std::vector<int16_t>(WIDTH_FIELD_CELLS, EMPTY_CELL);
        });
    }

    void Field::Draw(sf::RenderWindow &window)
    {
        std::for_each(std::cbegin(field), std::cend(field), [&, y = 0](const auto &line) mutable {
            std::for_each(std::cbegin(line), std::cend(line), [&, x = 0](const auto &cell) mutable {
                if (field.at(y).at(x))
                {
                    this->sprite.setTextureRect(sf::IntRect(field.at(y).at(x) * 18, 0, 18, 18));
                    this->sprite.setPosition(
                        x * CELL_SIZE,
                        y * CELL_SIZE);
                    window.draw(this->sprite);
                }
                x++;
            });
            y++;
        });
    }
}