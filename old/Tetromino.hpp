#pragma once

#include "Point.hpp"
#include "Field.hpp"

#include <random>
#include <algorithm>

namespace Tetris
{

    static const std::vector<std::vector<Point<int16_t>>> shapes
    {
        {},                               // Empty
        {{3, 0}, {4, 0}, {5, 0}, {6, 0}}, // I
        {{4, 1}, {4, 0}, {5, 0}, {3, 1}}, // S
        {{4, 1}, {3, 0}, {4, 0}, {5, 1}}, // Z
        {{4, 1}, {5, 0}, {3, 1}, {5, 1}}, // L
        {{4, 1}, {3, 0}, {3, 1}, {5, 1}}, // J
        {{4, 1}, {4, 0}, {3, 1}, {5, 1}}, // T
        {{4, 1}, {4, 0}, {5, 0}, {5, 1}}  // O
    };

    class Tetromino
    {

    private:
        sf::Texture texture;
        sf::Sprite sprite;
        int16_t color;

    private:
        std::vector<Point<std::int16_t>> shape;

        Point<float> point_rotation;
        const Point<float> GetPointRotation() const;

        ShapesTypes shape_type;

    private:
        std::random_device random;
        std::uniform_int_distribution<int16_t> dist{1, INT16_MAX};

    public:
        Tetromino();
        ~Tetromino();
        
        const int16_t 
        GetColor() const;
        
        const std::vector<Point<int16_t>> &
        GetShape() const;
        
        bool 
        GenerateShape();
        
        void 
        Rotate();
        
        void
        MovementShape(int16_t x_offset, int16_t y_offset);
        
        void 
        DrawShape(sf::RenderWindow &window);
    };
}