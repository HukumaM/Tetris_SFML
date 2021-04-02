#pragma once 

namespace Tetris
{
    template <typename T>
    struct Point
    {
        T x, y;
        Point(T x0 = 0.f, T y0 = 0.f)
            : x(x0), y(y0){};
    };
}