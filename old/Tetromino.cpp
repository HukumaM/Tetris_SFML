#include "Tetromino.hpp"

namespace Tetris
{
    // Конструктор класса
    // Загружает текстуры и вызывает GenerateShape()
    Tetromino::Tetromino()
    {
        if (!this->texture.loadFromFile("img/tetromino.png"))
        {
            std::clog << "Can't load background_line.jpg" << std::endl;
        }
        this->sprite.setTexture(this->texture);
        this->sprite.setScale(CELL_SCALE, CELL_SCALE);

        this->GenerateShape();
    }

    // Генерирует фигуру и присваивает квадрат спрайту
    // Возвращает true, если создание фигуры невозможно
    bool
    Tetromino::GenerateShape()
    {
        int16_t generated_number{1 + this->dist(this->random) % 7};
        this->shape_type = static_cast<ShapesTypes>(generated_number);
        this->color = generated_number;

        this->sprite.setTextureRect(
            sf::IntRect(this->color * 18, 0, 18, 18));
        this->shape = shapes.at(static_cast<int16_t>(shape_type));

        return Field::ShapeOnCellsField(this->shape);
    }

    Tetromino::~Tetromino()
    {
    }

    const Point<float>
    Tetromino::GetPointRotation() const
    {
        switch (this->shape_type)
        {
        case ShapesTypes::I:
            return {
                this->shape.at(1).x + 0.5f,
                this->shape.at(1).y + 0.5f};
            break;
        case ShapesTypes::O:
            return {
                static_cast<float>(this->shape.at(0).x + this->shape.at(2).x) / 2,
                static_cast<float>(this->shape.at(0).y + this->shape.at(2).y) / 2};
            break;
        default:
            return {
                this->shape.at(0).x,
                this->shape.at(0).y};
            break;
        }
    }

    void
    Tetromino::Rotate()
    {
        this->point_rotation = this->GetPointRotation();

        const auto shape_state = this->shape;

        for (auto &point : this->shape)
        {
            auto x = point.x - this->point_rotation.x;
            auto y = point.y - this->point_rotation.y;
            point.x = std::ceil(this->point_rotation.x - y);
            point.y = std::ceil(this->point_rotation.y + x);
        }

        auto direction = Field::ReturnToField(shape);
        do
        {
            MovementShape(direction.first, direction.second);
            direction = Field::ReturnToField(shape);
        } while (direction.first || direction.second);

        if (!direction.first && !direction.second)
        {
            shape = shape_state;
        }
    }

    void
    Tetromino::MovementShape(int16_t x_offset, int16_t y_offset)
    {
        std::transform(std::begin(this->shape), std::end(this->shape),
                       std::begin(this->shape), [&](auto &point) mutable {
                           return Point<int16_t>(point.x + x_offset,
                                                 point.y + y_offset);
                       });
    }

    void
    Tetromino::DrawShape(sf::RenderWindow &window)
    {
        std::for_each(std::begin(this->shape), std::end(this->shape), [&](const auto &point) {
            this->sprite.setPosition(
                point.x * CELL_SIZE,
                point.y * CELL_SIZE);
            window.draw(this->sprite);
        });
    }

    const std::vector<Point<int16_t>> &
    Tetromino::GetShape() const
    {
        return this->shape;
    }

    const int16_t
    Tetromino::GetColor() const
    {
        return this->color;
    }
}