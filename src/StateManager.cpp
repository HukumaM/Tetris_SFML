#include "StateManager.hpp"

namespace Engine
{
    StateManager::StateManager()
        : m_push(false), m_remove(false), m_replace(false)
    {
    }
    StateManager::~StateManager()
    {
    }

    void
    StateManager::PushState(std::unique_ptr<State> to_add, bool replace)
    {
        this->m_push = true;

        this->m_next_state = std::move(to_add);

        this->m_replace = replace;
    }

    void
    StateManager::PopState()
    {
        this->m_remove = true;
    }

    void
    StateManager::ProcessStateChange()
    {
        //  Checks if the extract flag is true and the state stack is not empty,
        //  then retrieves the state and runs the next one
        //  if the state stack is not empty
        if (this->m_remove && !this->m_state_stack.empty())
        {
            this->m_state_stack.pop();
            if (!this->m_state_stack.empty())
            {
                this->m_state_stack.top()->Launch();
            }
            this->m_remove = false;
        }

        //  Checks whether the add flag is true. If the replace flag is set 
        //  and the state stack is not empty, the element is removed from it 
        //  and the flag is reset. Then the state object at the top of the stack 
        //  is stopped and a new one is added
        if (this->m_push)
        {
            if (this->m_replace && !this->m_state_stack.empty())
            {
                this->m_state_stack.pop();
                this->m_replace = false;
            }

            if (!this->m_state_stack.empty())
            {
                this->m_state_stack.top()->Pause();
            }

            this->m_state_stack.push(std::move(this->m_next_state));
            this->m_state_stack.top()->Init();
            this->m_state_stack.top()->Launch();
            this->m_push = false;
        }
    }

    std::unique_ptr<State> &
    StateManager::GetState()
    {
        return this->m_state_stack.top();
    }

} //namespace Engine