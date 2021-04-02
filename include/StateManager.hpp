//-----------------------------------------------------------------------
//  Author      : Nikita Mashtalirov
//  Created     : 31.03.2021
//  Description : A class that controls application state management.
//-----------------------------------------------------------------------

#pragma once

#include <stack>
#include <memory>

#include "State.hpp"

namespace Engine
{
    class StateManager
    {
    private:
        //  Next state to put on the stack
        std::unique_ptr<State> m_next_state;

        //  Stack that stores states
        std::stack<std::unique_ptr<State>> m_state_stack;
    private:
        //  A flag variable that stores the need to insert a state
        bool m_push;
        //  A flag variable that stores the need to replace a state 
        bool m_replace;
        //  A flag variable that stores the need to remove a state
        bool m_remove;

    public:
        StateManager();
        ~StateManager();

    public:
        //  Adding a new state to the top of the state stack
        //  @param to_add   the state to be added to the state stack
        //  @param replace  a flag indicating whether we just want to add a new value - false,
        //                  or replace the current one with it - true
        void
        PushState(std::unique_ptr<State> to_add, bool replace = false);

        //  Popping the current state from the top of the state stack
        void
        PopState();

        //  Actual process state change
        void
        ProcessStateChange();

        //  Returns a pointer to the current state object by reference
        //  @return  a pointer to the current state object by reference
        std::unique_ptr<State> &
        GetState();
    };

} // namespace Engine