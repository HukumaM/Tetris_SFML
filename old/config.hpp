#pragma once

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Tetris
{
    constexpr int16_t   WIDTH_FIELD_CELLS       { 10 };
    constexpr int16_t   HEIGHT_FIELD_CELLS      { 20 };
    constexpr float     WIDTH_FIELD_PIXELS      { 360.f };
    constexpr float     HEIGHT_FIELD_PIXELS     { 720.f };
    constexpr float     CELL_SIZE               { WIDTH_FIELD_PIXELS / 10.f };
    constexpr float     CELL_SCALE              { CELL_SIZE / 18.f };
    constexpr float     TIME_FALL               { 0.5f };
    constexpr float     TIME_FALL_SPACE         { 0.0001f };
    constexpr float     TIME_TICK               { 0.7f };
    constexpr int16_t   EMPTY_CELL              { 0 };

    enum class ShapesTypes : int16_t
    {
        I = 1, S, Z, L, J, T, O
    };
    enum StateMovement
    {
        Move,
        Rotate
    };

    namespace ReturnDirection
    {
        constexpr int16_t STAND     {  0 };
        constexpr int16_t X_LEFT    { -1 };
        constexpr int16_t X_RIGHT   {  1 };
        constexpr int16_t Y_DOWN    {  1 };
        constexpr int16_t Y_UP      { -1 };
    };
}