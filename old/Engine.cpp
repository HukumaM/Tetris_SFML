#include "Engine.hpp"

namespace Tetris
{

    Engine::Engine()
        : time_fall(TIME_FALL)
    {
        tetromino = new Tetromino;
    }
    Engine::~Engine()
    {
        delete tetromino;
    }

    void Engine::Input()
    {
    }

    void Engine::SetTimeFall(const float time)
    {
        this->time_fall = time;
    }

    void
    Engine::Update()
    {
        using namespace Tetris::ReturnDirection;

        const auto elapsed_time_fall = this->timer_fall.getElapsedTime().asSeconds();
        const auto elapsed_time_tick = this->timer_tick.getElapsedTime().asSeconds();

        if (elapsed_time_fall >= this->time_fall && elapsed_time_tick < TIME_TICK)
        {
            if (this->field.PermissibilityMovement(this->tetromino->GetShape(), STAND, Y_DOWN))
            {
                this->tetromino->MovementShape(STAND, Y_DOWN);
                this->timer_fall.restart();
            }
        }
        else if (elapsed_time_fall >= this->time_fall && elapsed_time_tick >= TIME_TICK)
        {
            if (!this->field.PermissibilityMovement(this->tetromino->GetShape(), STAND, Y_DOWN))
            {
                this->field.ShapeToField(this->tetromino->GetShape(), this->tetromino->GetColor());
                this->field.ClearingLines(this->score);
                this->score.InsertPlayer();

                if (this->tetromino->GenerateShape())
                {
                }
            }
            this->timer_fall.restart();
            this->timer_tick.restart();
        }
    }

    void
    Engine::Move(StateMovement state, int16_t x_offset, int16_t y_offset)
    {
        switch (state)
        {
        case StateMovement::Move:
            if (this->field.PermissibilityMovement(this->tetromino->GetShape(), x_offset, y_offset))
            {
                this->tetromino->MovementShape(x_offset, y_offset);
                this->timer_tick.restart();
            }
            break;
        case StateMovement::Rotate:
            if (this->field.PermissibilityMovement(this->tetromino->GetShape(), x_offset, y_offset))
            {
                this->tetromino->Rotate();
                this->timer_tick.restart();
            }
            break;
        }
    }

    void
    Engine::Render(sf::RenderWindow &window)
    {
        this->background.Draw(window);
        this->tetromino->DrawShape(window);
        this->field.Draw(window);
    }

    void
    Engine::UpdateMenu()
    {
    }

    void
    Engine::UpdatePause()
    {
    }

    void
    Engine::UpdatePhysics()
    {
    }

    void
    Engine::RenderMenu()
    {
    }

    void
    Engine::RenderPause()
    {
    }

    void
    Engine::RenderPhysics()
    {
    }
}