//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 02.04.2021
//  Description : Structure describing a point
//-----------------------------------------------------------------------

#pragma once

struct Point
{
    float x, y;
    //  Constructor
    //  @param  x0       x-axis coordinate
    //  @param  y0       y-axis coordinate
    Point(float x0 = 0.f, float y0 = 0.f)
        : x(x0), y(y0){};
};



