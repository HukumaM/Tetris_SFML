//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 31.03.2021
//  Description : Abstract base class for the state stack.
//-----------------------------------------------------------------------

#pragma once

#include <SFML/System/Time.hpp>

namespace Engine
{
    class State
    {
    public:
        State(){};
        virtual ~State(){};

    public:
        //  Virtual method for initializing class data
        virtual void Init() = 0;

        //  Virtual method for processing keystrokes and mouse clicks
        virtual void ProcessInput() = 0;

        //  Virtual method for updating the position of sprites, texts
        //  @param  delta_time - time elapsed since the last function call
        virtual void Update(sf::Time delta_time) = 0;

        //  Virtual method for drawing sprites and text
        virtual void Draw() = 0;

        //  Virtual method for pausing the state
        virtual void Pause(){};

        //  Virtual method for launching the state
        virtual void Launch(){};
    };

} // namespace Engine
