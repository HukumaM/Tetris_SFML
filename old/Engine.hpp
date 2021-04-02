#pragma once

#include <memory>

#include "config.hpp"
#include "Tetromino.hpp"
#include "Field.hpp"
#include "Background.hpp"
#include "Score.hpp"



namespace Tetris
{
    class Engine
    {
    private:
        Tetromino *tetromino;
        Field field;
        Background background;
        Score score;

        float time_fall;

    private:
        sf::Window window;
        sf::Event event;

        sf::Clock timer_tick;
        sf::Clock timer_fall;

    public:
        Engine();
        ~Engine();
        void SetTimeFall(const float time);
        void Move(StateMovement state, int16_t x_offset, int16_t y_offset);
        void Input();
        void Update();
        void Render(sf::RenderWindow &window);

    private:
        void UpdateMenu();
        void UpdatePause();
        void UpdatePhysics();

    private:
        void RenderMenu();
        void RenderPause();
        void RenderPhysics();
    };
}